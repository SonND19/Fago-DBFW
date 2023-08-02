//
// GreenSQL DB Connection class implementation.
//
// Copyright (c) 2007 GreenSQL.NET <stremovsky@gmail.com>
// License: GPL v2 (http://www.gnu.org/licenses/gpl.html)
//

#include "connection.hpp"
#include "proxy.hpp"
#include "normalization.hpp"
#include "riskengine.hpp"
#include "misc.hpp"
#include "alert.hpp"
#include "parser/parser.hpp"     // for query_risk struct
#include "dbmap.hpp"
#include "config.hpp"

// #include "../include/curl/curl.h"
Connection::Connection(int proxy_id)
{
    iProxyId = proxy_id;
    logevent(NET_DEBUG, "connection init()\n");
    first_request = true;
    db = NULL;
    db_name = "";
    db_new_name = "";
    db_user = "";
    db_type = "";
    db_user_ip = "";
	SecondPacket = false;
	first_response = true;
}

bool Connection::close()
{
#ifndef WIN32
    logevent(NET_DEBUG, "connection close(), proxy socket %d, backend socket %d\n", 
              proxy_event.ev_fd, backend_event.ev_fd);
    Socket::socket_close(proxy_event.ev_fd);
    Socket::socket_close(backend_event.ev_fd);
    if (proxy_event.ev_fd != 0 && proxy_event.ev_fd != -1)
        event_del(&proxy_event);
    if (proxy_event_writer.ev_fd != 0 && proxy_event_writer.ev_fd != -1 )//&&
        event_del(&proxy_event_writer);

    if (backend_event.ev_fd != 0 && backend_event.ev_fd != -1)
        event_del(&backend_event);
    if (backend_event_writer.ev_fd != 0 && backend_event_writer.ev_fd != -1 )
        event_del(&backend_event_writer);
    connections->erase(location);
#endif
    return true;
}

/// @brief 
/// @param query 
/// @return 
bool Connection::check_query(std::string & query)
{
    
    GreenSQLConfig * conf = GreenSQLConfig::getInstance();
    std::string original_query = query;

    std::string reason = "";
    std::string reasons = "";
    std::string questions = question(original_query, reason);
    std::string block_reasons = block_reason(original_query, reasons);
    // convert query to lower case
    str_lowercase(query);
    // perform normalization - make a pattern of the query
    normalizeQuery( (DBProxyType) dbType, query);
    // we will make the reference out of query
    std::string & pattern = query;
    logevent(SQL_DEBUG, "AFTER NORM   : %s\n", pattern.c_str());

    bool ret = false;
    bool privileged_operation = false;
    int risk = 0;

    // Optimization Changes
    // In case we are in automatic block of the new commands
    // we do not need to calculate query risk if the query
    // pattern is known and it is in the whitelist.
    // This must be 99% of the cases (after learning mode is over).
    int in_whitelist = 0;

    in_whitelist = db->CheckWhitelist(pattern);
    if ( in_whitelist )
    {
        logevent(SQL_DEBUG, "Found in Exception List.\n");
        return true;
    }

    if ( (ret = checkBlacklist(pattern, reason)) == true)
    {
         privileged_operation = true;
	 logevent(SQL_DEBUG, "FORBIDEN     : %s\n", pattern.c_str());
    }
    // check if we find anything interesting
    risk = calculateRisk(original_query, reason);
    logevent(SQL_DEBUG, "RISK         : %d\n", risk);

    DBBlockStatus block_status = db->GetBlockStatus();

    if ( block_status == ALWAYS_BLOCK_NEW )
    {
        reason += "Query blocked because it is not in whitelist.\n";
        logevent(DEBUG, "Query blocked because it is not in whitelist.\n");
        logalert(iProxyId, db_name, db_user, db_user_ip, original_query, pattern, reason, risk, (int)BLOCKED);
                 status = BLOCKED;
        log_event("[User: %s]**[Query: %s]**[Questions: %s]**[Block reasons: %s]\n", db_user.c_str(), original_query.c_str(), questions.c_str(), "Query blocked because it is not in whitelist");
        log_event(db_user.c_str(), original_query.c_str(), questions.c_str(), "Query blocked because it is not in whitelist");
        // block this query
        return false;
    }

    if (block_status == LEARNING_MODE || block_status == LEARNING_MODE_3DAYS || block_status == LEARNING_MODE_7DAYS){
        db->AddToWhitelist(db_user, pattern);
        if (risk >= conf->re_block_level)
        {
            logwhitelist(iProxyId, db_name, db_user, db_user_ip, original_query, pattern, reason, risk, (int)HIGH_RISK);
            log_alert(db_user.c_str(), db_name.c_str(), original_query.c_str(), HIGH_RISK);
 
        } else if (risk >= conf->re_warn_level)
        {
            logwhitelist(iProxyId, db_name, db_user, db_user_ip, original_query, pattern, reason, risk, (int)WARN);
            log_alert(db_user.c_str(), db_name.c_str(), original_query.c_str(), WARN);
        } else {
            logwhitelist(iProxyId, db_name, db_user, db_user_ip, original_query, pattern, reason, risk, (int)LOW);
            log_alert(db_user.c_str(), db_name.c_str(), original_query.c_str(), LOW);
	    }
        return true;
    }

    DBBlockLevel risk_block_level = WARN;

    if (risk >= conf->re_block_level) 
    {
        logalert(iProxyId, db_name, db_user, db_user_ip, original_query, pattern, reason, risk, (int)risk_block_level);
        
        if (risk_block_level == BLOCKED){
            log_event("[User: %s]**[Query: %s]**[Questions: %s]**[Block reasons: %s]\n", db_user.c_str(), original_query.c_str(), questions.c_str(), block_reasons.c_str());
            log_alert(db_user.c_str(), db_name.c_str(), original_query.c_str(), status);
            return false;
        }
    } else if (risk >= conf->re_warn_level){
        //warn level
        risk_block_level = WARN;
        logalert(iProxyId, db_name, db_user, db_user_ip, original_query, pattern, reason, risk, (int)risk_block_level);

    }
    if(db->check_user_permiss(db_user, original_query) == true){

        log_event("[User: %s]**[Query: %s]**[Questions: %s]**[Block reasons: %s]\n", db_user.c_str(), original_query.c_str(), questions.c_str(), block_reasons.c_str());
        log_alert(db_user.c_str(), db_name.c_str(), original_query.c_str(), status);
    } 
    else
    {
        log_event("[User: %s]**[Query: %s]**[Questions: %s]**[Block reasons: %s]\n", db_user.c_str(), original_query.c_str(), questions.c_str(), block_reasons.c_str());
        if(check_token(original_query) == true)
        {  
            status = BLOCKED;
        }
        log_alert(db_user.c_str(), db_name.c_str(), original_query.c_str(), status);
        return false;
    } 
    return true;
}

unsigned int Connection::calculateRisk(std::string & query, std::string & reason)
{
    GreenSQLConfig * conf = GreenSQLConfig::getInstance();
    unsigned int ret = 0;

    struct query_risk risk;
    query_parse(&risk, getSQLPatterns(), query.c_str());

    if (conf->re_sql_comments > 0 &&
        risk.has_comment == 1)
    {
        reason += "Query has comments\n";
        logevent(DEBUG, "Query has comments\n");
        ret += conf->re_sql_comments;
    }

    if (conf->re_s_tables > 0 &&
        risk.has_s_table == 1)
    {
        reason += "Query uses sensitive tables\n";
        logevent(DEBUG, "Query uses sensitive tables\n");
        ret += conf->re_s_tables;
    }
    if (conf->re_multiple_queries > 0 &&
        risk.has_separator == 1)
    {
        reason += "Multiple queries found\n";
        logevent(DEBUG, "Multiple queries found\n");
        ret += conf->re_multiple_queries;
    }

    if (conf->re_or_token > 0 &&
        risk.has_or == 1)
    {
        reason += "Query has 'or' token\n";
        logevent(DEBUG, "Query has 'or' token\n");
        ret += conf->re_or_token;
    }
    if (conf->re_union_token > 0 &&
        risk.has_union == 1)
    {
        reason += "Query has 'union' token\n";
        logevent(DEBUG, "Query has 'union' token\n");
        ret += conf->re_union_token;
    }

    if (conf->re_var_cmp_var > 0 &&
        risk.has_tautology == 1)
    {
        reason += "True expression detected (SQL tautology)\n";
        logevent(DEBUG, "True expression detected (SQL tautology)\n");
        ret += conf->re_var_cmp_var;
    }
    if (conf->re_empty_password > 0 &&
        risk.has_empty_pwd == 1)
    {
        reason += "Query has empty password expression\n";
        logevent(DEBUG, "Query has empty password expression\n");
        ret += conf->re_empty_password;
    }
    if (conf->re_bruteforce > 0 &&
        risk.has_bruteforce_function == 1)
    {
        reason += "Query has SQL fuction that can be used to bruteforce db contents\n";
	logevent(DEBUG, "Query has SQL fuction that can be used to bruteforce db contents\n");
	ret += conf->re_bruteforce;
    }
    return ret;
}

std::string Connection::question(std::string &query, std::string &reason)
{
    if(check_or_token(query) == true){
        reason += "Query has 'or' token.";
    }
    else if(check_not_token(query) == true){
        reason += "Query has 'not' token.";
    }
    else if(check_true_token(query) == true){
        reason += "Query has 'true' token.";
    }
    else if(check_comments(query) == true){
        reason += "Query has comments.";
    }
    else if(check_union_token(query) == true){
        reason += "Query has 'union' token.";
    }
    else if(check_in_token(query) == true){
        reason += "Query has 'in' token.";
    }
    else if(check_and_token(query) == true){
        reason += "Query has 'and' token.";
    }
    else if(db->check_user_permiss(db_user, query) == true)
    {
        reason += "Checking query.";
    }
    else{
        reason += "Unknown query.";
    }
    return reason;
}
std::string Connection::block_reason(std::string &query, std::string &reason)
{
    if(db->check_user_permiss(db_user, query) == true){
        status = WARN;
        reason += "Co quyen truy cap.";
    }
    else{
        status = BLOCKED;
        reason += "Khong co quyen truy cap. ";
    }
    if(check_not_token(query) == true){
        status = BLOCKED;
        reason += "Chua bieu thuc dieu kien cu the la NOT. ";
    }
    if(check_true_token(query) == true){
        status = BLOCKED;
        reason += "Chua bieu thuc dieu kien cu the la TRUE. ";
    }
     if(check_or_token(query) == true){
        status = BLOCKED;
        reason += "Chua bieu thuc dieu kien cu the la OR. ";
    }
     if(check_union_token(query) == true){
        status = BLOCKED;
        reason += "Chua bieu thuc dieu kien cu the la UNION. ";
    }
     if(check_in_token(query) == true){
        status = BLOCKED;
        reason += "Chua bieu thuc dieu kien cu the la IN. ";
    }
     if(check_and_token(query) == true){
        status = BLOCKED;
        reason += "Chua bieu thuc dieu kien cu the la AND. ";
    }
     if(check_command(query) == false){
        status = SQL_ERROR;
        reason += "Loi do nhap sai cu phap. ";
    }
     if (check_white_space(query) == false){
        status = SQL_ERROR;
        reason += "Loi do thieu khoang trang giua cac lenh. ";
    }
     if(check_comments(query) == true){
        status = BLOCKED;
        reason += "Chua cac ki tu dac biet trong query. ";
    }
    
    return reason;
}
void Connection::copy_sql(std::string &query)
{
    std::string port = "5431";
    std::string local_host = "127.0.0.1";
    if(db->backup_sql(query, db_user) == true)
    {
        std::cout << "Sao luu thanh cong";
    }
    else {
        std::cout << "Sao luu that bai";
    }

}