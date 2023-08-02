#ifndef DDOS_HPP
#define DDOS_HPP

#include <string>
#include <list>
#include <event.h>
bool socket_read(int fd, char * data, int & size);
bool socket_write(int fd, const char* data, int & size);
class Socket
{
public:
    //init
    Socket(){};
    //destructor
    virtual ~Socket(void);
    //socket
    int server_socket(std::string & ip, int port);
    int client_socket(std::string & server, int port);
    int socket_accept(int serverfd);
    int static socket_close(int sfd);
    
    int new_socket();
private:
};

#endif
