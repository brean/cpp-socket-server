#include "../include/connection.h"

Connection::Connection(Config cfg) {
    this->set_config(cfg);
    this->sessions = new std::list<Session>;
}

void Connection::set_config(Config cfg) {
    this->cfg = cfg;
};

void *Connection::com_routine(void *connection) {
    Connection * con = (Connection *)connection;
    std::list<Session>::iterator it;

    int sockaddr_in_size = sizeof(struct sockaddr_in);

    // data for new client connection, will be given to session
    int client_sockfd;
    struct sockaddr client_addr;

    // thread id for sub-thread that will be created for a new session
    pthread_t thread_id;

    con->sockfd = socket(AF_INET , SOCK_STREAM , 0);
    if (con->sockfd == -1) {
        std::cerr << "error creating socket" << std::endl;
        pthread_exit(NULL);
        return 0;
    }

    // TODO: move to config and add create server-Adress function?
    con->sock_addr.sin_family = AF_INET;
    //con->sock_addr.sin_addr.s_addr = INADDR_ANY;
    inet_pton(AF_INET, con->cfg.host.c_str(), &(con->sock_addr.sin_addr));
    con->sock_addr.sin_port = htons( con->cfg.port );

    if (bind(con->sockfd,
          (struct sockaddr *)&con->sock_addr,
          sizeof(con->sock_addr)) < 0) {
        std::cerr << "error - bind failed" << std::endl;
        pthread_exit(NULL);
        return 0;
    }

    if (listen(con->sockfd, LISTEN_BACKLOG) == -1) {
        std::cerr << "error - listen failed" << std::endl;
        pthread_exit(NULL);
        return 0;
    }
    std::cout << "Waiting for incoming connections..." << std::endl;

    while( (client_sockfd = accept(
              con->sockfd,
              (struct sockaddr *)&(client_addr),
              (socklen_t*)&sockaddr_in_size) ) )
    {
        Session session = Session(con, client_sockfd);
        con->sessions->push_back(session);
        session.socket_addr = client_addr;
        std::cout << "New connection from " << session.ip << ":" << session.port << std::endl;
        session.start();
    }

    // TODO: own function for ending the server, disconnect all clients, join&exit all threads etc.
    // Now join the thread, so that we dont terminate before the thread
    for (it=con->sessions->begin(); it != con->sessions->end(); ++it) {
       pthread_join( (*it).thread_id , NULL);
    }

    if (client_sockfd < 0)
    {
        std::cerr << "accept failed" << std::endl;
        return 0;
    }

    std::cout << "communcation thread ended" << std::endl;
    pthread_exit(NULL);
    return 0;
}

/**
 * create thread and start listening on given port
 */
void Connection::start() {
    std::cout << "Start server on " << this->cfg.host << ":" << this->cfg.port << std::endl;
    // thread for communication with external clients
    pthread_create(&this->com_thread, NULL, Connection::com_routine, (void *)this);
    pthread_exit(NULL);
};
