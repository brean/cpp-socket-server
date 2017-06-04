#ifndef SOCKET_SERVER_CONNECTION_H
#define SOCKET_SERVER_CONNECTION_H

// use a list instead of a vector because connections can be removed at any time
#include <list> // std::list for sessions

#include <pthread.h> // for threading
#include <sys/socket.h>
#include <arpa/inet.h> //for inet_addr

#include "session.h"
#include "config.h"

#define LISTEN_BACKLOG 10

// forward-define Session
class Session;

/**
 * manage connections to clients - create client session
 */
class Connection {
public:
    Connection(Config cfg);

    void set_config(Config cfg);

    // thread for communication
    pthread_t com_thread;

    // start server thread
    void start();

    std::list<Session> *sessions;
private:
    Config cfg;

    // function running inside the communication thread
    // to open the socket - called by listen
    static void *com_routine(void *connection);

    // socket file descriptor
    int sockfd;

    // data for incoming socket
    struct sockaddr_in sock_addr;
};

#endif
