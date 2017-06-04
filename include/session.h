#ifndef SOCKET_SERVER_SESSION_H
#define SOCKET_SERVER_SESSION_H

#include <sys/socket.h>
#include <arpa/inet.h> //for inet_addr
#include <iostream>
#include <list>
#include "connection.h"

#define MSG_SIZE 2048

// forward-define Connection
class Connection;

/**
 * manage single client session
 */
class Session {
public:
    Session(Connection* con, int sockfd);

    struct sockaddr socket_addr;
    int sockfd;

    static void * handler_routine(void *session);

    // client ip address, provided by get_client_addr
    char ip[INET6_ADDRSTRLEN];
    // client port, provided by get_client_addr
    int port;

    // thread id, see start
    pthread_t thread_id;

    // start new session - creates a session thread that calls the handler
    void start();

    Connection* con;
private:

  // get client ip and port from socket file descriptor sockfd
  // called by the constructor
  // based on https://stackoverflow.com/questions/2064636/
    void get_client_addr();
};

#endif
