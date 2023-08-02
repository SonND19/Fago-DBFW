//
// GreenSQL DB Proxy class implementation.
// This code has OS dependent code.
//
// Copyright (c) 2007 GreenSQL.NET <stremovsky@gmail.com>
// License: GPL v2 (http://www.gnu.org/licenses/gpl.html)
//

#ifdef WIN32
#include "compat.hpp"
#endif

#include "proxy.hpp"
// #include "config.hpp"
// #include "connection.hpp"
#include "proxymap.hpp"


#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <fcntl.h>

#ifdef WIN32 
#include <winsock2.h>
#else
#include <netinet/in.h>
#include <netinet/tcp.h>
#endif


#include <arpa/inet.h>
#include <errno.h>

static const int min_buf_size = 10240;
// void enable_event_writer(Connection * conn, bool proxy);
// void disable_event_writer(Connection * conn, bool proxy);
Proxy::Proxy()
{
    memset(&serverEvent, 0, sizeof(struct event));
    //v_conn.reserve(10);
}

Proxy::~Proxy(void)
{
    //logevent(DEBUG, "i am in GreenSQL destructor\n");
}

bool Proxy::PrepareNewConn(int fd, int & sfd, int & cfd)
{
    Socket socket;
    //logevent(NET_DEBUG, "server socket fired, fd=%d\n",fd);
    sfd = socket.socket_accept(fd);
    if (sfd == -1)
        return false;

    cfd = socket.client_socket(sBackendIP.empty() ? sBackendName : sBackendIP, iBackendPort);
    if (cfd == -1)
    {std::cout << "PrepareNewConn1\n";
        socket.socket_close(sfd);
        logevent(NET_DEBUG, "Failed to connect to backend db server (%s:%d)\n", sBackendName.c_str(), iBackendPort);
        return false;
    }
    std::cout << "PrepareNewConn2\n";
    //logevent(NET_DEBUG, "client (to mysql backend) connection established\n");
    return true;
}

void Proxy::Server_cb(int fd, short which, void * arg, 
     Connection * conn, int sfd, int cfd)
{
    struct sockaddr_storage ss;
    size_t len = sizeof(struct sockaddr_storage);
    std::cout << "len1\n";

#ifndef WIN32
    logevent(NET_DEBUG, "GreenSQL Server_cb(), sfd=%d, cfd=%d\n", sfd, cfd);

    event_set( &conn->proxy_event, sfd, EV_READ | EV_PERSIST, wrap_Proxy, (void *)conn);
    event_set( &conn->proxy_event_writer, sfd, EV_WRITE | EV_PERSIST, wrap_Proxy, (void *)conn);
    event_add( &conn->proxy_event, 0);

    event_set( &conn->backend_event, cfd, EV_READ | EV_PERSIST, wrap_Backend, (void *)conn);
    event_set( &conn->backend_event_writer, cfd, EV_WRITE | EV_PERSIST, wrap_Backend, (void *)conn);
    event_add( &conn->backend_event, 0);
 
    logevent(NET_DEBUG, "size of the connection queue: %d\n", v_conn.size());

    v_conn.push_front(conn);

    conn->connections = &v_conn;
    conn->location = v_conn.begin();

    // get db user ip address
    getpeername(sfd,(struct sockaddr*)&ss, (socklen_t*)&len);
    if (ss.ss_family == AF_INET)
    {std::cout << "Server_cb1\n";
        struct sockaddr_in *s = (struct sockaddr_in *)&ss;
        conn->db_user_ip = inet_ntoa(s->sin_addr);
    }
    else if (ss.ss_family == AF_INET6)
    {std::cout << "Server_cb2\n";
        struct sockaddr_in6 *s = (struct sockaddr_in6 *)&ss;
        char ipstr[INET6_ADDRSTRLEN*2];
        inet_ntop(AF_INET6, (void *)&s->sin6_addr, ipstr, sizeof(ipstr));
        conn->db_user_ip = ipstr;
    }
#endif
}

void enable_event_writer(Connection * conn, bool proxy)
{
  struct event *writer = proxy? &conn->proxy_event_writer : &conn->backend_event_writer;
  bool add_event = false;
  if (writer->ev_fd != 0 && writer->ev_fd != -1 )
  {
    add_event = writer->ev_fd != 0 && writer->ev_fd != -1 ;
    {
#ifndef WIN32
      event_add( writer, 0);    
#endif
      logevent(NET_DEBUG, "Try again add write event,active flag: fd: %d\n",writer->ev_fd);
  }
}
}

void disable_event_writer(Connection * conn, bool proxy)
{
  struct event *writer = proxy? &conn->proxy_event_writer : &conn->backend_event_writer;
  bool del_event = false;
  if (writer->ev_fd != 0 && writer->ev_fd != -1) 
    
  {
    del_event = writer->ev_fd != 0 && writer->ev_fd != -1 ;
    {
#ifndef WIN32
      event_del(writer);
#endif
      
      logevent(NET_DEBUG, "No data clear write event,active flag:  fd: %d\n",writer->ev_fd);
      
    }
  }
}

bool Proxy::ProxyInit(int proxyId, std::string & proxyIp, int proxyPort,
        std::string & backendName, std::string & backendIp, int backendPort, std::string & dbType)
{   
    Socket socket;
    iProxyId = proxyId;   
    sProxyIP = proxyIp;
    iProxyPort = proxyPort;
    sBackendName = backendName;
    sBackendIP = backendIp;
    iBackendPort = backendPort;
    iProxyId = proxyId;
    sDBType = dbType;
    if (strcasecmp(dbType.c_str(), "mysql") == 0)
    {
        DBType = DBTypeMySQL;
    } else if (strcasecmp(dbType.c_str(), "pgsql") == 0)
    {
        DBType = DBTypePGSQL;
    } 
	else
    {
        DBType = DBTypeMySQL;
    }
    int sfd = socket.server_socket(sProxyIP, iProxyPort);
    if (sfd == -1)
        return false;
#ifndef WIN32
    event_set(&serverEvent, sfd, EV_READ | EV_WRITE | EV_PERSIST,
              wrap_Server, (void *)iProxyId);

    event_add(&serverEvent, 0); 
#endif
    return true;
}

bool Proxy::ProxyReInit(int proxyId, std::string & proxyIp, int proxyPort,
        std::string & backendName, std::string & backendIp, int backendPort,
        std::string & dbType)
{
    Socket socket;
    if (ServerInitialized())
    {
#ifndef WIN32
        event_del(&serverEvent);
        std::cout << "ProxyReInit\n";
#endif
        socket.socket_close(serverEvent.ev_fd);
        serverEvent.ev_fd = 0;
        std::cout << "ProxyReInit1\n";
    }
    return ProxyInit(proxyId, proxyIp, proxyPort, backendName, backendIp, backendPort, dbType);
}

// this function returns true if server socket is established
bool Proxy::ServerInitialized()
{
    if (serverEvent.ev_fd != 0 && serverEvent.ev_fd != -1) 
        return true;
    return false;
}

// this function returns true of we have open active connections
bool Proxy::HasActiveConnections()
{
    return !v_conn.empty();
}

void clear_init_event(Connection * conn, int fd, short flags, pt2Func func,bool proxy)
{
  struct event *connection = proxy? &conn->proxy_event : &conn->backend_event;
#ifndef WIN32
  event_del( connection);
  event_set( connection, fd, flags, func, (void *)conn);
  event_add( connection, 0);
#endif
}




void Proxy_cb(int fd, short which, void * arg)
{
    Connection * conn = (Connection *) arg;
    char data[min_buf_size];
    int len = sizeof(data) - 1;

    if (which & EV_WRITE)
    {
      // trying to send data
      if (Proxy_write_cb(fd, conn) == false)
      {
        // failed to send data. close this socket.
        CloseConnection(conn);
        return;
      }
    }

    if (!(which & EV_READ))
        return;

    if (socket_read(fd, data, len) == false)
    {std::cout << "proxy_cb2\n";
        logevent(NET_DEBUG, "[%d] Failed to read socket, closing socket\n", fd);
        CloseConnection(conn);
        return;
    }
    logevent(NET_DEBUG, "[%d] proxy socket read %d bytes\n", fd,len);
    if ( len > 0 )
    {
        data[len] = '\0';
        //printf("received data\n");
        conn->request_in.append(data,len);
    
        //perform validation of the request
        if (ProxyValidateClientRequest(conn) == false)
        {std::cout << "proxy_cb3\n";
            CloseConnection(conn);
        }
    }
}
bool Proxy_write_cb(int fd, Connection * conn)
{
    int len = conn->response_out.size();
    logevent(NET_DEBUG, "[%d] proxy socket write %d bytes\n", fd,len);
    if (len == 0)
    {
        //we can clear the WRITE event flag
        disable_event_writer(conn,true);
        //clear_init_event(conn,fd,EV_READ | EV_PERSIST,wrap_Proxy,(void *)conn);
        return true;
    }

    const unsigned char * data = conn->response_out.raw();

    if (socket_write(fd, (const char * )data, len) == true)
    {std::cout << "Proxy_write_cb2\n";
        logevent(NET_DEBUG, "Send data to client, size: %d\n",len);
        conn->response_out.chop_back(len);
    } else {
        logevent(NET_DEBUG, "[%d] Failed to send, closing socket\n", fd);
        // no need to close socket object here
        // it will be done in the caller function
        return false;
    }
    if (conn->response_out.size() == 0 )
    {
        //we can clear the WRITE event flag
        query_check=" ";
        disable_event_writer(conn,true);
        //clear_init_event(conn,fd,EV_READ|EV_PERSIST,wrap_Proxy,(void *)conn);
    } else // if (conn->response_out.size() > 0 )
    {
        // we need to enable WRITE event flag
        query_check = " ";
	enable_event_writer(conn,true);
        //clear_init_event(conn,fd,EV_READ|EV_WRITE|EV_PERSIST,wrap_Proxy,(void *)conn);
    }
    return true;
}

bool ProxyValidateClientRequest(Connection * conn)
{
    std::string request = "";
    bool hasResponse = false;
    request.reserve(min_buf_size);
    int len = 0;

    // mysql_validate(request);
    if (conn->parseRequest(request, hasResponse) == false)
    {std::cout << "ProxyValidateClientRequest2\n";
        logevent(NET_DEBUG, "Failed to parse request, closing socket.\n");
        return false;
    }

    len = (int)request.size();
    std::cout << "len = " << len << "\n";
    if (hasResponse == true)
    {
        // we can push response to response_in or response_out queues
        if (conn->response_in.size() != 0)
        {
            if (ProxyValidateServerResponse(conn) == false)
            {
                return false;
            }
        } else if (conn->response_out.size() != 0)
        {
            Proxy_write_cb( conn->proxy_event.ev_fd, conn);
        }
    }
    if (len <= 0)
        return true;

    //push request
    conn->request_out.append(request.c_str(), (int)request.size());
    return Backend_write_cb(conn->backend_event.ev_fd, conn);
}

void Backend_cb(int fd, short which, void * arg)
{

    //we are real server client.
    Connection * conn = (Connection *) arg;
    char data[min_buf_size];
    int len = sizeof(data)-1;

    // check if we can write to this socket
    if ( which & EV_WRITE )
    {
        if ( Backend_write_cb(fd, conn) == false )
        {
            // failed to write, close this socket
            CloseConnection(conn);
            return;
        }
    }

    if (!(which & EV_READ))
        return;
    
    if (socket_read(fd, data, len) == false)
    {
        CloseConnection(conn);
        return;
    }
    if ( len > 0 )
    {
        data[len] = '\0';
        //printf("received data\n");
        conn->response_in.append(data,len);

        if (ProxyValidateServerResponse(conn) == false)
        {
            CloseConnection(conn);
        }
    }

    return;
}

bool Backend_write_cb(int fd, Connection * conn)
{
    //we are real server client.
    int len = conn->request_out.size();

     if (len == 0)
     {std::cout << "Backend_write_cb1\n";
        logevent(NET_DEBUG, "[%d] backend socket write %d bytes\n", fd,len);
	    disable_event_writer(conn,false);            
        //clear_init_event(conn,fd,EV_READ | EV_PERSIST,wrap_Backend,(void *)conn,false);
        return true;
     }
    const unsigned char * data = conn->request_out.raw();

    if (socket_write(fd, (const char *)data, len) == true)
    {std::cout << "Backend_write_cb2\n";
        logevent(NET_DEBUG, "sending data to backend server\n");
        conn->request_out.chop_back(len);
    } 
	else 
	{
		if(conn->first_response)
		{
			enable_event_writer(conn,false); 
			return true;
		}
        logevent(NET_DEBUG, "[%d] Failed to send data to client, closing socket\n", fd);
        // no need to close connection here
        return false;
    } 
    if (conn->request_out.size() == 0)
    {
        //we can clear the WRITE event flag
        disable_event_writer(conn,false); 
        //clear_init_event(conn,fd,EV_READ | EV_PERSIST,wrap_Backend,(void *)conn,false);
    } else //if (conn->request_out.size() > 0)
    {
        // we need to enable WRITE event flag
        enable_event_writer(conn,false);
        //clear_init_event(conn,fd,EV_READ | EV_WRITE | EV_PERSIST,wrap_Backend,(void *)conn,false);
    }
    return true;
}

bool ProxyValidateServerResponse( Connection * conn )
{
    std::string response;
    response.reserve(min_buf_size);
    std::cout << "ProxyValidateServerResponse1\n";
    conn->parseResponse(response);
    
    //push response
    if (response.size() == 0)
    {
        return true;
    }
    conn->response_out.append(response.c_str(), (int)response.size());
    std::cout << "ProxyValidateServerResponse2\n";
    // if an error occurred while sending data, this socket will be closed.
    return Proxy_write_cb( conn->proxy_event.ev_fd, conn);
}

void Proxy::Close()
{
    //check if we have initialized server socket
    proxymap_set_db_status(iProxyId,0);

    Connection * conn;
    while ( v_conn.size() != 0)
    {
        conn = v_conn.front();
        // we remove pointer to the conn object inside the close() function
        conn->close();
        delete conn;
    }
    v_conn.clear();

    CloseServer();
    //logevent(NET_DEBUG, "Closing proxy object\n");
}

void Proxy::CloseServer()
{
    Socket socket;
    if (ServerInitialized())
    {//std::cout << "closeserver\n";
        socket.socket_close(serverEvent.ev_fd);
#ifndef WIN32
        event_del(&serverEvent);
#endif
        serverEvent.ev_fd = 0;
    }
    return;
}

void CloseConnection(Connection * conn)
{std::cout << "CloseConnection\n";
    conn->close();
    delete conn;
}

