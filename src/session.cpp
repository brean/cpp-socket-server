#include "../include/session.h"

void* Session::handler_routine(void *session) {
    Session* ses = (Session*) session;
    std::list<Session>::iterator it;
    std::list<Session> * sessions;
    Session* s;

    ssize_t read_size = 1;
    char client_message[MSG_SIZE];
    int flags = 0;
    while(read_size > 0) {
        read_size = recv(ses->sockfd, client_message, (ssize_t)MSG_SIZE, 0);
        if (read_size <= 0) {
            break;
        }
        client_message[read_size] = '\0';

        // forward message to all clients
        sessions = ses->con->sessions;
        std::cout << sessions->size() << std::endl;
        for (it=sessions->begin(); it != sessions->end(); ++it) {
            s = &(*it);
            send(s->sockfd, client_message, read_size, flags);
        }
        //std::cout << client_message << std::endl;

    }

    std::cout << "-- end of transmission --" << std::endl;
    pthread_exit(NULL);

    return 0;
};

Session::Session(Connection* con, int _sockfd) {
    this->con = con;
    this->sockfd = _sockfd;
    this->get_client_addr();
}

void Session::start() {
  if( pthread_create(&(this->thread_id), NULL,
      Session::handler_routine,
      (void*) this) < 0)
  {
      std::cerr << "could not create session thread" << std::endl;
      return;
  }
}

void Session::get_client_addr() {
    socklen_t len;
    struct sockaddr_storage addr;

    len = sizeof addr;
    getpeername(this->sockfd, (struct sockaddr*)&addr, &len);

    // deal with both IPv4 and IPv6:
    if (addr.ss_family == AF_INET) {
        struct sockaddr_in *s = (struct sockaddr_in *)&addr;
        this->port = ntohs(s->sin_port);
        inet_ntop(AF_INET, &s->sin_addr, this->ip, sizeof(this->ip));
    } else { // AF_INET6
        struct sockaddr_in6 *s = (struct sockaddr_in6 *)&addr;
        this->port = ntohs(s->sin6_port);
        inet_ntop(AF_INET6, &s->sin6_addr, this->ip, sizeof(this->ip));
    }

}
