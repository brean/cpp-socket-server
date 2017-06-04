#ifndef SOCKET_SERVER_CONFIG_H
#define SOCKET_SERVER_CONFIG_H

#include <yaml-cpp/yaml.h>
#include <iostream> // for std::cout and and std::endl

/**
 * load configuration from file
 */
class Config {
    public:
        // port we listen on, between 1 and 65536.
        int port = 0;
        // adress we bind the server to. use "0.0.0.0" for any
        std::string host = "0.0.0.0";
        void load(const char* filename, const char* appname);
};

#endif
