//
// GreenSQL functions used to manage a number of proxy objects.
//
// Copyright (c) 2007 GreenSQL.NET <stremovsky@gmail.com>
// License: GPL v2 (http://www.gnu.org/licenses/gpl.html)
//

#include "greensql.hpp"
#include "proxymap.hpp"
#include "mysql/mysql_con.hpp"
#include "pgsql/pgsql_con.hpp"

#include <stdio.h>
#include<map>

static const char * const q_proxy = "SELECT proxyid, frontend_ip, frontend_port, backend_server, "
            "backend_ip, backend_port, dbtype FROM proxy WHERE status != 3";
        
static std::map<int, GreenSQL * > proxies;

void wrap_Server(int fd, short which, void * arg)
{
    long proxy_id;
    
    proxy_id = (long) arg;
    logevent(NET_DEBUG, "[%d]wrap_Server\n", proxy_id);
    GreenSQLConfig * conf = GreenSQLConfig::getInstance();
    
    GreenSQL * cls = proxies[proxy_id];
    Connection * conn = NULL;
    int sfd;
    int cfd;
 
    if(cls == NULL)
        return;

    if (conf->bRunning == false)
    {std::cout << "wrap_Server1\n";
        cls->Close();
    }
    else if(cls->PrepareNewConn(fd, sfd, cfd))
    {
        if (cls->DBType == DBTypeMySQL)
        {std::cout << "wrap_Server2\n";
            conn = new MySQLConnection(proxy_id);
        }
        else if (cls->DBType == DBTypePGSQL)
        {std::cout << "wrap_Server3\n";
            conn = new PgSQLConnection(proxy_id);
        }std::cout << "wrap_Server4\n";
        cls->Server_cb(fd, which, arg, conn, sfd, cfd);
    }
}

void wrap_Proxy(int fd, short which, void * arg)
{
    Connection * con = (Connection *) arg;
    int proxy_id = con->iProxyId;
    
    std::cout << "wrap_Proxy\n";
    logevent(NET_DEBUG, "[%d]frontend socket fired %d\n", proxy_id, fd);
    GreenSQLConfig * conf = GreenSQLConfig::getInstance();

    if (conf->bRunning == false)
    {
        GreenSQL * cls = proxies[proxy_id];
        if (cls){
            std::cout << "wrap_Proxy1\n";
            cls->Close();
        }       
    }
    else
    {std::cout << "wrap_Proxy2\n";
        Proxy_cb(fd, which, arg);
    }
}

void wrap_Backend(int fd, short which, void * arg)
{
    int proxy_id;
    Connection * con = (Connection *) arg;
    proxy_id = con->iProxyId;

    logevent(NET_DEBUG, "[%d]backend socket fired %d\n", proxy_id, fd);

    GreenSQLConfig * conf = GreenSQLConfig::getInstance();
    std::cout << "wrap_backend\n";
    if (conf->bRunning == false)
    {
        GreenSQL * cls = proxies[proxy_id];
        if (cls)
        {std::cout << "wrap_backend1\n";
            cls->Close();
        }
    }
    else
    {std::cout << "wrap_backend2\n";
        Backend_cb(fd, which, arg);
    }
}

bool proxymap_init()
{
    proxymap_reload();
    //*std::cout << "proxies_size: " << proxies.size() << "\n"; 
    if (proxies.size() == 0)
        return false;
    
    return true;
}

bool proxymap_close()
{
    std::map<int, GreenSQL * >::iterator iter;
    GreenSQL * cls = NULL;

    while (proxies.size() != 0)
    {
        iter = proxies.begin();
        cls = iter->second;
        cls->Close();
        delete cls;
        proxies.erase(iter);
        std::cout << "proxymapclose\n";
    }
    std::cout << "proxymapclose1\n";
    return true;
}

bool proxymap_reload()
{
    std::map<int, GreenSQL * > new_proxies;
    std::map<int, GreenSQL * >::iterator itr;

    db_struct db;
    GreenSQL * cls = NULL;
    bool ret;

    std::string backendIP;
    std::string backendName;
    int backendPort;
    std::string proxyIP;
    int proxyPort;
    int proxy_id = 2;
    std::string dbType = "pgsql";
    
    backendIP = "127.0.0.1";
    backendPort = 5432;

    proxyIP = "0.0.0.0";
    proxyPort = 5431;

    /* initalize new or alter existing connections */
    if (! db_query(&db,q_proxy,256)) {
        logevent(STORAGE,"DB config erorr: %s\n",db_error());
        db_cleanup(&db);
        return false;
    } 
    
    /* Get a row from the results */
    while (db_fetch_row(&db))
    {
        proxy_id = db_col_int(&db,0);
        // proxyIP = (char *) db_col_text(&db,1);
        proxyPort = db_col_int(&db,2);
        backendName = (char *) db_col_text(&db,3);
        backendIP = (char *) db_col_text(&db,4);
        backendPort = db_col_int(&db,5);
        dbType = (char *) db_col_text(&db,6);

        //new object

        itr = proxies.find(proxy_id);
        if (itr == proxies.end())
        {
            /** proxy doesnt exist in memory so create a new one **/
            cls = new GreenSQL();		
            bool ret = cls->ProxyInit(proxy_id, proxyIP, proxyPort, backendName, backendIP, backendPort, dbType);
            if (ret == false)
            {
                // failed to init proxy
                proxymap_set_db_status(proxy_id, 2);
                cls->Close();
                delete cls;
            } else { // init proxy thanh cong
                proxymap_set_db_status(proxy_id, 1);
                proxies[proxy_id] = cls;
                new_proxies[proxy_id] = cls;
            }
            continue;
        }

        // found proxy object
        cls = itr->second;
        new_proxies[proxy_id] = cls;

        // check whether the proxy details were altered
        if (cls->sProxyIP != proxyIP || cls->iProxyPort != proxyPort || cls->sDBType != dbType)
        {
            ret = cls->ProxyReInit(proxy_id, proxyIP, proxyPort, backendName, backendIP, backendPort, dbType);
            if (ret == false)
            {std::cout << "proxymap3.1\n";
                proxymap_set_db_status(proxy_id, 2);
            } else {std::cout << "proxymap3.1\n";
                proxymap_set_db_status(proxy_id, 1);
            }
            continue;
			
        } else if (cls->sBackendName != backendName ||
                   cls->sBackendIP != backendIP ||
                   cls->iBackendPort != backendPort)
        {std::cout << "proxymap4\n";
            /**
              check maybe only the proxy backend details were altered
              in that case only updating the data in memory is required for when someone tries to connect
            **/
            cls->sBackendName = backendName;
            cls->sBackendIP = backendIP;
            cls->iBackendPort = backendPort;  
        }

        // either the backend parameters were modified or no change was done at all, yet the status=0 due to management status
        proxymap_set_db_status(proxy_id, 1);
        //std::cout << "proxymap4";
    } /** EOF while **/

    

    /* Release memory used to store results. */
    db_cleanup(&db);  

    /* go over a list of proxies and check if it was deleted from db */
    if (new_proxies.size() == proxies.size())
    {std::cout << "proxymap5\n";    
        return true;
    }

    /* new_proxies.size() != proxies.size() */
    logevent(DEBUG, "We have deleted proxies\n");
    for (itr = proxies.begin(); itr != proxies.end() && new_proxies.size() != proxies.size(); itr++)
    {std::cout << "proxymap6\n";
        if (new_proxies[itr->first] == NULL)
        {
            // found proxy object to delete
            cls = itr->second;
            if (cls->HasActiveConnections() == true)
            {std::cout << "proxymap7\n";
                // close server listener socker only
                logevent(DEBUG, "Closing proxy socket\n");
                cls->CloseServer();
            } else {
                //  completly close this object
                logevent(DEBUG, "Removing proxy object\n");
                cls->Close();
                delete cls;
                proxies.erase(itr);
                std::cout << "proxymap8\n";
            }
        }
    }
    std::cout << "proxymap_end\n";
    return true;
}

/*
 *  proxy status
 *  0 - reload
 *  1 - good
 *  2 - failed to load
 *  3 - disabled
 *  4 - during proxymap_reload
 */

bool proxymap_set_db_status(unsigned int proxy_id, int status )
{
    char query[1024];

    snprintf(query, sizeof(query), 
            "UPDATE proxy set status=%d where proxyid=%d",
            status, proxy_id);

    if ( ! db_exec(query))
    {std::cout << "DB config erorr14\n";
        logevent(STORAGE,"DB config erorr: %s\n",db_error());
        /* Make query */
        return false;
    }
    //std::cout << "promap:::\n";
    return true;
}
// bool backup_sql(std::string &port, std::string &db_name, std::string &host_name, std::string &user)
// {
//     std::string path = " > /home/sonnd/greensql-fw/db_cp/pgsql1.sql";
//     // std::string query= "pg_dump -h 127.0.0.1 -p 5432 -U green greendb > /home/sonnd/greensql-fw/db_cp/pgsql.sql";
//     std::string query = "pg_dumpe -h ";
//     query.append(host_name);
//     query.append(" -p ");
//     query.append(port);
//     query.append(" -U ");
//     query.append(user);
//     query.append(db_name);
//     query.append(path);
//     if(db_exec(query.c_str()) == 1)
//     {
//         if(db_backup(query.c_str()) == 1)
//             return true;
//         return false;
//     }
// }