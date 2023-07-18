//
// GreenSQL DB Permission class implementation.
//
// Copyright (c) 2007 GreenSQL.NET <stremovsky@gmail.com>
// License: GPL v2 (http://www.gnu.org/licenses/gpl.html)
//
// #include <libpq-fe.h>
#include "config.hpp"
#include "dbpermobj.hpp"
#include "misc.hpp"
#include "log.hpp"
#include <stdio.h>
#include <iostream>
// #include <normalization.hpp>
// static const char * q_dbb = "SELECT * FROM info";
void DBPermObj::Init(std::string name, unsigned int id, long long p,
             long long perms2, unsigned int status)
{
    db_name = name;
    proxy_id = id;
    block_status = (DBBlockStatus) status;
    perms = p;

    if (perms == 0)
        return;
    if (perms & (int)CREATE_Q)
        create_perm = true;
    if (perms & (int)DROP_Q)
        drop_perm = true;
    if (perms & (int)ALTER_Q)
        alter_perm = true;
    if (perms & (int)INFO_Q)
        info_perm = true;
    if (perms & (int)BLOCK_Q)
        block_q_perm = true;
    if (perms & (int)BRUTEFORCE_Q)
        bruteforce_perm = true;
    if(perms & (int)GRANT_Q)
        grant_perm = true;
    if(perms & (int)REVOKE_Q)
        revoke_perm = true;
    return;
}

DBPermObj::~DBPermObj()
{
    exceptions.clear();
}

bool DBPermObj::LoadWhitelist()
{
    db_struct db;
    char q[1024];
    std::map<std::string, int, std::less<std::string> > q_list;

    snprintf(q, 1024, "SELECT query, perm FROM query "
              "WHERE proxyid = %d AND db_name='%s'",
              proxy_id, db_name.c_str());

    /* read new exceptions from the database */
    if (! db_query(&db,q,1024)) {
        logevent(STORAGE,"DB config erorr: %s\n",db_error());
        db_cleanup(&db);
        return false;
    } 

    int perm = 0;
    std::string q_ex = "";
        
    /* Get a row from the results */
    while (db_fetch_row(&db))
    {
        perm = db_col_int(&db,1);
        q_ex = (char *) db_col_text(&db,0);

        if (perm > 0 && q_ex.length() > 0)
        {
            //q_list[q_ex] = perm;        
            q_list.insert(std::pair<std::string, int>(q_ex, perm));
        }
    }
    // std::cout << "LoadWhitelist\n";
    /* Release memory used to store results. */
    db_cleanup(&db);

    exceptions.clear();
    exceptions = q_list;
    return true;
}

int DBPermObj::CheckWhitelist(std::string & q)
{
    std::map<std::string, int >::iterator itr;
    itr = exceptions.find(q);    
    if (itr == exceptions.end())
    {
        // std::cout << "CheckWhitelist\n";
        return 0;
    }
    return itr->second;
}

bool DBPermObj::AddToWhitelist(std::string & dbuser, std::string & pattern)
{
    char * q = new char [ pattern.length() + 1024 ];
    db_struct db;

    snprintf(q, pattern.length() + 1024,
        "SELECT queryid FROM query WHERE "
        "proxyid = %d and db_name = '%s' and query = '%s'",
        proxy_id, db_name.c_str(), pattern.c_str());

    /* read new queryid from the database */
    if (! db_query(&db, q ,pattern.length() + 1024)) {
        /* Failed */std::cout << "DB config erorr11\n";
        logevent(STORAGE,"DB config erorr: %s\n",db_error());
        delete [] q;
        db_cleanup(&db);
        return false;
    } 

    /* Download result from server */
    if (db_fetch_row(&db))
    {
        // nothing to do here, query is aready in whitelist
        delete [] q;
        db_cleanup(&db);
        return true;
    }

    // add pattern to the whitelist
    snprintf(q, pattern.length() + 1024,
       "INSERT into query "
       "(proxyid, perm, db_name, query) "
       "VALUES (%d,1,'%s','%s')",
       proxy_id, db_name.c_str(), pattern.c_str());

    /* read new urls from the database */
    if (! db_exec(q)) {
        /* Make query */std::cout << "DB config erorr12\n";
        logevent(STORAGE,"DB config erorr: %s\n",db_error());
        delete [] q;
        return false;
    }
    delete [] q;
    q = NULL;

    return true;
}
bool DBPermObj::check_user_permiss(std::string &db_user, std::string &query)
{
    char * tv = new char [query.length() +1024];
    snprintf(tv, query.length() +1024,"SELECT * FROM proxy");
    db_struct db; 
    if (! db_query(&db, tv ,query.length() + 1024)) {
        /* Failed */
        logevent(STORAGE,"DB config erorr: %s\n",db_error());
        delete [] tv;
        db_cleanup(&db); 
        return false;
    }
    std::string query_db = query;
    str_lowercase(query_db);
    std::string table_name = search_table(query_db);
    std::string permis = search_per(query_db);
   // SELECT * FROM information_schema.role_table_grants where grantee = 'green';
    std::string query_1 = "SELECT has_table_privilege('";
    query_1.append(db_user);
    query_1.append("', '");
    query_1.append(table_name);
    query_1.append("', '");
    query_1.append(permis);
    query_1.append("');");
    if(db_exec(query_1.c_str()) == 1) 
    {
        if(db_permiss(query_1.c_str()) == 1)  
        {
            return true; 
        }  
        else {
            return false; 
        }
    }         
}

// pg_dump -h host_name -p port_number db_name > path/to/backup.sql
bool DBPermObj::backup_sql(std::string &query, std::string &db_user)
{
    std::string path = " > /home/sonnd/greensql-fw/db_cp/pgsql1.sql";
    std::string query1 = "SELECT has_function_privilege('";
    // SELECT has_function_privilege('green', 'pg_catalog.set_config(text, text, boolean)', 'EXECUTE');
    query1.append(db_user);
    query1.append("', 'pg_catalog.set_config(text, text, boolean)', 'EXECUTE');");
    // if(db_exec(query.c_str()) == 1)
    // {
        if(db_backup(query1.c_str()) != 0)
            return true;
        return false;
    //}
}
// psql -h host_name -p port_number db_name < path/to/backup.sql
// bool DBPermObj::restore_sql(std::string &port, std::string &db_name, std::string &host_name, std::string &db_user)
// {
//     std::string path = " > /home/sonnd/greensql-fw/db_cp/pgsql.sql";
//     // std::string query= "psql -h 127.0.0.1 -p 5432 -U green greendb < /home/sonnd/greensql-fw/db_cp/pgsql.sql"; 
//     // SELECT pg_catalog.set_config('search_path', '', false);
//     if(db_exec(query.c_str()) == 1)
//     {
//         if(db_backup(query.c_str()) == 1)
//             return true;
//         return false;
//     }
// }
