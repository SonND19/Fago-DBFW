#ifdef WIN32
#include "compat.hpp"
#endif

#include "socket.hpp"
#include "log.hpp"
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

#include <iostream>
#include <arpa/inet.h>
#include <errno.h>

Socket::~Socket(void)
{
    //logevent(DEBUG, "i am in GreenSQL destructor\n");
}
int Socket::server_socket(std::string & ip, int port)
{
    int sfd;
    // std::cout << "server_soket\n";
    struct sockaddr_in addr;
#ifdef WIN32
	const char* flags,*ling;
#else
    int flags =1;
	struct linger ling = {0, 0};
    // std::cout << "server_soket1\n";
#endif
    if ((sfd = new_socket()) == -1) {
        std::cout << "server_soket2\n";
        return -1;
    }
#ifdef WIN32
	setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, flags, sizeof(flags));
	setsockopt(sfd, SOL_SOCKET, SO_KEEPALIVE, flags, sizeof(flags));
	setsockopt(sfd, SOL_SOCKET, SO_LINGER, ling, sizeof(ling));
	setsockopt(sfd, IPPROTO_TCP, TCP_NODELAY, flags, sizeof(flags));
#else
    setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, &flags, sizeof(flags));
    setsockopt(sfd, SOL_SOCKET, SO_KEEPALIVE, &flags, sizeof(flags));
    setsockopt(sfd, SOL_SOCKET, SO_LINGER, &ling, sizeof(ling));
    setsockopt(sfd, IPPROTO_TCP, TCP_NODELAY, &flags, sizeof(flags));
#endif
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    //addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_addr.s_addr = inet_addr(ip.c_str());
    std::cout << "server_soket3\n";
    if (bind(sfd, (struct sockaddr *) &addr, sizeof(addr)) == -1) {
        logevent(NET_DEBUG, "Failed to bind server socket on %s:%d\n", ip.c_str(), port);
        socket_close(sfd);
        return -1;
    }
    
    if (listen(sfd, 1024) == -1) {
        logevent(NET_DEBUG, "Failed to switch socket to listener mode\n");
        socket_close(sfd);
        return -1;
    }
    std::cout << "server_soket_end\n";
    return sfd;
}

int Socket::client_socket(std::string & server, int port)
{std::cout << "client_socket\n";
    int sfd;
    struct sockaddr_in addr;
#ifdef WIN32
	const char* flags,*ling;
#else
    int flags =1;
    struct linger ling = {0, 0};
#endif 
    if ((sfd = new_socket()) == -1) {
        return -1;
    }
#ifdef WIN32
	setsockopt(sfd, SOL_SOCKET, SO_LINGER, ling, sizeof(ling));
	setsockopt(sfd, SOL_SOCKET, SO_KEEPALIVE, flags, sizeof(flags));
#else
    setsockopt(sfd, SOL_SOCKET, SO_LINGER, &ling, sizeof(ling));
    setsockopt(sfd, SOL_SOCKET, SO_KEEPALIVE, &flags, sizeof(flags));
#endif
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(server.c_str());
      
    if (connect(sfd, (struct sockaddr *) &addr, sizeof(addr)) == -1)
    {
#ifndef WIN32
        if (errno == EAGAIN || errno == EWOULDBLOCK || errno == EINPROGRESS) {
            return sfd;
        } else if (errno == EMFILE) {
            logevent(NET_DEBUG, "[%d] Failed to connect to backend server, too many open sockets\n", sfd);
        } else {
            logevent(NET_DEBUG, "[%d] Failed to connect to backend server\n", sfd);
        }
#endif
        socket_close(sfd);
        return -1;
    }
    return sfd;
}

int Socket::socket_accept(int serverfd)
{
    socklen_t addrlen;
    struct sockaddr addr;
    int sfd;
#ifdef WIN32
	const char* flags,*ling;
#else
    int flags = 1;
    struct linger ling = {0, 0};
#endif   
    memset(&addr, 0, sizeof(addr));
    addrlen = sizeof(addr);

    if ((sfd = (int)accept(serverfd, &addr, &addrlen)) == -1) {
#ifndef WIN32
        if (errno == EAGAIN || errno == EWOULDBLOCK || errno == EINPROGRESS) {
            return sfd;
        } else if (errno == EMFILE) {
            logevent(NET_DEBUG, "[%d] Failed to accept client socket, too many open sockets\n", serverfd);
        } else {
            logevent(NET_DEBUG, "[%d] Failed to accept client socket\n", serverfd);
        }
#endif
        socket_close(sfd);
        return -1;
    }
#ifdef WIN32
	setsockopt(sfd, SOL_SOCKET, SO_KEEPALIVE, flags, sizeof(flags));
	setsockopt(sfd, SOL_SOCKET, SO_LINGER, ling, sizeof(ling));
#else
    setsockopt(sfd, SOL_SOCKET, SO_KEEPALIVE, &flags, sizeof(flags));
    setsockopt(sfd, SOL_SOCKET, SO_LINGER, &ling, sizeof(ling));
  
    if ((flags = fcntl(sfd, F_GETFL, 0)) < 0 ||
         fcntl(sfd, F_SETFL, flags | O_NONBLOCK) < 0) {
        logevent(NET_DEBUG, "[%d] Failed to swith socket to non-blocking mode\n", sfd);
        socket_close(sfd);
        return -1;
    }
#endif 
    return sfd;
}

int Socket::socket_close(int sfd)
{
#ifndef WIN32
    close(sfd);
#endif
    return 0;
}

bool socket_read(int fd, char * data, int & size)
{
    if ((size = recv(fd, data, size, 0)) < 0)
    {
        size = 0;
        logevent(NET_DEBUG, "[%d] Socket read error %d\n", fd, errno);
#ifndef WIN32
        if (errno == EAGAIN || errno == EWOULDBLOCK || errno == EINPROGRESS) {
           return true;
        }
#endif
        return false;
    }
    if (size == 0)
    {
       logevent(NET_DEBUG, "[%d] Socket read error %d\n", fd, errno);
       return false;
    }
                   
    return true; 
}

bool socket_write(int fd, const char* data, int & size)
{std::cout << "socket_write\n";
    logevent(NET_DEBUG, "Socket_write\n");
    if ((size = send(fd, data, size, 0))  <= 0)
    {
#ifdef WIN32
        int err = WSAGetLastError();
        logevent(NET_DEBUG, "[%d] Socket write error %d\n", fd, err);
        if (err == WSAEINTR || err == WSAEWOULDBLOCK || err == WSAEINPROGRESS ) {
            size = 0;
            return true;
        }
#else
        logevent(NET_DEBUG, "[%d] Socket write error %d\n", fd, errno);
        if (errno == EAGAIN || errno == EWOULDBLOCK || errno == EINPROGRESS) {
           size = 0;
           std::cout << "socket_write1\n";
           return true;
        }
#endif
        std::cout << "socket_write2\n";
        return false;
    }
    std::cout << "socket_write3\n";
    return true;
  
}

int Socket::new_socket() {
    int sfd;

#ifdef WIN32
    unsigned long nonblock  = 1;
    SOCKET sock;
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        logevent(NET_DEBUG, "Failed to create socket\n");
        return -1;
    }

    if (ioctlsocket(sock, FIONBIO, &nonblock) == SOCKET_ERROR)
    {
        logevent(NET_DEBUG, "[%d] Failed to swith socket to non-blocking mode\n", sock);
        socket_close((int)sock);
        return -1;
    }
    sfd = (int) sock;
#else

    if ((sfd = (int)socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        logevent(NET_DEBUG, "Failed to create socket\n");
        return -1;
    }

    int flags;
    if ((flags = fcntl(sfd, F_GETFL, 0)) < 0 || 
         fcntl(sfd, F_SETFL, flags | O_NONBLOCK) < 0)
    {
        logevent(NET_DEBUG, "[%d] Failed to swith socket to non-blocking mode\n", sfd);
        socket_close(sfd);
        return -1;
    }
#endif
    return sfd;
}



