//
// This file is used to handle alerts generated by GreenSQL.
//
// Copyright (c) 2007 GreenSQL.NET <stremovsky@gmail.com>
// License: GPL v2 (http://www.gnu.org/licenses/gpl.html)
//

#include "config.hpp"
#include "log.hpp"
#include "alert.hpp"
#include <iostream>
#include <map>
#include <stdio.h>

static unsigned int agroup_get(int p_id, std::string & dbn, std::string & p);
static unsigned int agroup_add(int p_id, std::string & dbn, std::string & p);
static int alert_add(unsigned int agroupid, char * user, const char * userip, char * query, 
                     char * reason, int risk, int block);
static bool agroup_update(unsigned int agroupid);
static bool agroup_update_status(unsigned int agroupid);

static std::map<std::string, unsigned int > agroupmap;
static const char * const q_agroup = "SELECT agroupid, proxyid, db_name, pattern "
                                     "FROM alert_group";
static unsigned int agroupmap_get( int p_id, std::string & dbn,std::string & p);
 // for code optimization.
static const int alert_query_size = 1024*1024;
static char alert_query[alert_query_size]; // default size - 1MB.

bool logalert(int proxy_id, std::string & dbname,  std::string & dbuser, std::string & dbuserip,
        std::string & query, std::string & pattern, 
        std::string & reason, int risk, int block)
{

    // when mysql_real_escape_string function escapes binary zero it is changed to
    // \x00 . As a result, original string after escaping can grow up to 4 times.

    char * tmp_q = db_escape_string(query.c_str(), (unsigned long) query.length());
    char * tmp_r = db_escape_string(reason.c_str(), (unsigned long) reason.length()); 
    char * tmp_u = db_escape_string(dbuser.c_str(), (unsigned long) dbuser.length()); 

    unsigned int agroupid = agroupmap_get(proxy_id, dbname, pattern);
    
    if (agroupid == 0)
    {
        agroupid = agroup_get(proxy_id, dbname, pattern);
    }
    if (agroupid == 0)
    {
        agroupid = agroup_add(proxy_id, dbname, pattern);
    }
    //failed to add
    if (agroupid == 0)
    {
        logevent(ERR, "Failed to get group alert id\n");
        delete [] tmp_q;
        delete [] tmp_r;
    delete [] tmp_u;
        return false;
    }
    alert_add(agroupid, tmp_u, dbuserip.c_str(), tmp_q, tmp_r, risk, block);
    agroup_update(agroupid);
    delete [] tmp_q;
    delete [] tmp_r;
    delete [] tmp_u;
    return true;    
}

bool logwhitelist(int proxy_id, std::string & dbname, std::string & dbuser, std::string & dbuserip,
        std::string & query, std::string & pattern,
        std::string & reason, int risk, int block)
{
    GreenSQLConfig * conf = GreenSQLConfig::getInstance();

    // when mysql_real_escape_string function escapes binary zero it is changed to
    // \x00 . As a result, original string after escaping can grow up to 4 times.

    char * tmp_q = db_escape_string(query.c_str(), (unsigned long) query.length());
    char * tmp_r = db_escape_string(reason.c_str(), (unsigned long) reason.length());
    char * tmp_u = db_escape_string(dbuser.c_str(), (unsigned long) dbuser.length());

    unsigned int agroupid = agroupmap_get(proxy_id, dbname, pattern);
    if (agroupid == 0)
    {
        agroupid = agroup_get(proxy_id, dbname, pattern);
    }
    if (agroupid == 0)
    {
        agroupid = agroup_add(proxy_id, dbname, pattern);
    }
    //failed to add
    if (agroupid == 0)
    {
        logevent(ERR, "Failed to get group alert id\n");
        delete [] tmp_q;
        delete [] tmp_r;
        delete [] tmp_u;
        return false;
    }
    alert_add(agroupid, tmp_u, dbuserip.c_str(), tmp_q, tmp_r, risk, block);
    agroup_update_status(agroupid);
    delete [] tmp_q;
    delete [] tmp_r;
    delete [] tmp_u;
    return true;
}

bool agroupmap_init()
{
    return agroupmap_reload();
}

bool agroupmap_reload()
{//std::cout << "alert0\n";
    db_struct db;
    unsigned int proxy_id = 0;
    unsigned int agroupid = 0;
    std::string db_name = "";
    std::string pattern = "";
    std::string key = "";
    std::map<std::string, unsigned int > temp_agroupmap;
    //std::map<std::string, unsigned int >::iterator itr;

    /* read all alert groups from the database */
    if( !db_query(&db,q_agroup,256) )
    {std::cout << "DB config erorr1\n";
        /* Make query */
        logevent(STORAGE,"DB config erorr: %s\n",db_error());
        db_cleanup(&db);
        return false;
    }

    /* Get a row from the results */
    while (db_fetch_row(&db))
    {
        agroupid = db_col_int(&db,0);
        proxy_id = db_col_int(&db,1);
        db_name = db_col_text(&db,2);
        pattern = db_col_text(&db,3);
        // std::cout << "agroupid: " << agroupid << "\n";
        // std::cout << "proxy_id: " << proxy_id << "\n";
        // std::cout << "db_name: " << db_name << "\n";
        // std::cout << "pattern: " << pattern << "\n";
        key = proxy_id;
        key += ",";
        key += db_name;
        key += ",";
        key += pattern;

        temp_agroupmap[key] = agroupid;
    }

    agroupmap = temp_agroupmap;

    /* Release memory used to store results. */
    db_cleanup(&db);
    std::cout << "alert_end\n";
    return true;
}

static unsigned int
agroupmap_get( int proxy_id, std::string & db_name,std::string & pattern)
{
    std::string key;
    std::map<std::string, unsigned int >::iterator itr;

    key = proxy_id;
    key += ",";
    key += db_name;
    key += ",";
    key += pattern;

    itr = agroupmap.find(key);
    if (itr == agroupmap.end())
    {
        return 0;
    }
    return itr->second;
}

static unsigned int 
agroup_get(int proxy_id, std::string & dbname,std::string & pattern)
{std::cout << "agroup_get\n";
//    char q[pattern.length() + 1024];
    db_struct db;
    char * q;

    int requred_query_size = pattern.length() + dbname.length() + 1024;
    if (requred_query_size > alert_query_size)
    {
        q = new char[requred_query_size];
        if (q == NULL)
        {
            // no memory
            return 0;
        }
    } else {
        q = alert_query;
    }

    //first check if we have similar alert in the past
    snprintf(q, requred_query_size, 
        "SELECT agroupid FROM alert_group WHERE "
        "proxyid = %d and db_name = '%s' and pattern = '%s'",
        proxy_id, dbname.c_str(), pattern.c_str());

    /* read new urls from the database */
    if (! db_query(&db,q,pattern.length() + 1024))
    {
        if (q != alert_query)
        {
            // release allocated memory
            delete [] q;
        }std::cout << "DB config erorr2\n";
        logevent(STORAGE,"DB config erorr: %s\n",db_error());
        db_cleanup(&db);
        return 0;
    } 
    if (q != alert_query)
    {
        // release allocated memory
        delete [] q;
    }
    q = NULL;

    /* Get a row from the results */
    if (db_fetch_row(&db))
    {
        unsigned int i = db_col_int(&db,0);
        /* Release memory used to store results. */
        db_cleanup(&db);

        /* return the result */
        return i;
    }

    /* Release memory used to store results. */
    db_cleanup(&db);    
    return 0;
}

static unsigned int
agroup_add(int proxy_id, std::string & dbname, std::string & pattern)
{std::cout << "agroup_add\n";
    GreenSQLConfig * conf = GreenSQLConfig::getInstance();
    unsigned int agroupid;
    char * q;

    int requred_query_size = pattern.length() + dbname.length() + 1024;

    if (requred_query_size > alert_query_size)
    {
        q = new char[requred_query_size];
        if (q == NULL)
        {
            // no memory
            return 0;
        }
    } else {
        q = alert_query;
    }

    if (conf->sDbType == DB_MYSQL)
    {
        snprintf(q, requred_query_size, "INSERT into alert_group "
                "(proxyid, db_name, update_time, pattern) "
                "VALUES (%d,'%s',now(),'%s')",
                proxy_id, dbname.c_str(), pattern.c_str());
    }
    else if (conf->sDbType == DB_PGSQL)
    {
        snprintf(q, requred_query_size, "INSERT into alert_group "
            "(proxyid, db_name, update_time, pattern) "
            "VALUES (%d,'%s',now(),'%s')",
            proxy_id, dbname.c_str(), pattern.c_str());
    }

    /* add new alert to the database */
    if (! db_exec(q))
    {
        if (q != alert_query)
        {
            // release allocated memory
            delete [] q;
        }std::cout << "DB config erorr3\n";
        logevent(STORAGE,"DB config erorr: %s\n",db_error());
        return 0;
    }

    if (q != alert_query)
    {
        // release allocated memory
        delete [] q;
    }
    q = NULL;

    if (db_changes() == 0)
    {
        return 0;
    }

    agroupid = agroup_get(proxy_id, dbname, pattern);
    // add new key to adgroupmap
    std::string key;
    key = proxy_id;
    key += ",";
    key += dbname;
    key += ",";
    key += pattern;

    agroupmap[key] = agroupid;
    return agroupid; 
}

static int alert_add(unsigned int agroupid, char * user, const char * userip, char * query, 
                     char * reason, int risk, int block)
{std::cout << "alert_add\n";
    char * q;
    int requred_query_size = strlen(query) + strlen(reason) + 1024;

    if (requred_query_size > alert_query_size)
    {
        q = new char[requred_query_size];
        if (q == NULL)
        {
            // no memory
            return 0;
        }
    } else {
        q = alert_query;
    }

    GreenSQLConfig * conf = GreenSQLConfig::getInstance();

    if (conf->sDbType == DB_MYSQL)
    {
        snprintf(q, requred_query_size,
                "INSERT into alert "
                "(agroupid, event_time, risk, block, dbuser, userip, query, reason) "
                "VALUES (%u,now(),%d,%d,'%s','%s','%s','%s')",
                agroupid, risk, block, user, userip, query, reason);
    }
    else if (conf->sDbType == DB_PGSQL)
    {
        snprintf(q, requred_query_size,
            "INSERT into alert "
            "(agroupid, event_time, risk, block, dbuser, userip, query, reason) "
            "VALUES (%u,now(),%d,%d,'%s','%s','%s','%s')",
            agroupid, risk, block, user, query, reason);
    }

    /* read new urls from the database */
    if ( ! db_exec(q))
    {
        if (q != alert_query)
        {
            // release allocated memory
            delete [] q;
        }std::cout << "DB config erorr4\n";
        logevent(STORAGE,"DB config erorr: %s\n",db_error());
        return 0;
    }

    if (q != alert_query)
    {
        // release allocated memory
        delete [] q;
    }
    q = NULL;

    if (!db_changes())
    {
        return 0;
    }

    return 1; 
}

static bool
agroup_update(unsigned int agroupid)
{std::cout << "agroup_update\n";
    char q[1024];
    GreenSQLConfig * conf = GreenSQLConfig::getInstance();

    if (conf->sDbType == DB_MYSQL) {
        snprintf(q, sizeof(q), 
               "UPDATE alert_group SET update_time=now() WHERE agroupid = %u",
               agroupid);
    }
    else if (conf->sDbType == DB_PGSQL) {
        snprintf(q, sizeof(q), 
            "UPDATE alert_group SET update_time=now() WHERE agroupid = %u",
            agroupid);
    }

    /* read new urls from the database */
    if ( !db_exec(q))
    {std::cout << "DB config erorr5\n";
        logevent(STORAGE,"DB config erorr: %s\n",db_error());
        return false;
    }

    /* check changes */
    if (!db_changes())
    {
        return false;
    }

    return true;
}


static bool
agroup_update_status(unsigned int agroupid)
{std::cout << "agroup_update_status\n";
    char q[1024];
    GreenSQLConfig * conf = GreenSQLConfig::getInstance();

    if (conf->sDbType == DB_MYSQL) {
        //snprintf(q_mysql+90, 20, "%u", agroupid);
        snprintf(q, sizeof(q), "UPDATE alert_group SET update_time=now(), status=1 WHERE agroupid = %u", agroupid);
        //q = q_mysql;
    }
    else if (conf->sDbType == DB_PGSQL) {
        //snprintf(q_mysql+90, 20, "%u", agroupid);
        snprintf(q, sizeof(q), "UPDATE alert_group SET update_time=now(), status=1 WHERE agroupid = %u", agroupid);
        //q = q_mysql;
    }

    /* read new urls from the database */
    if ( ! db_exec(q))
    {std::cout << "DB config erorr6\n";
        logevent(STORAGE,"DB config erorr: %s\n",db_error());
        return false;
    }

    /* check changes */
    if (!db_changes())
    {
        return false;
    }

    return true;
}