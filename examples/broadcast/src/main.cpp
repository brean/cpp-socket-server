/**
 * example for a simple broadcast server
 * every time a client sends something it will be broadcasted to all connected
 * clients (including the client that sends the message)
 */
#include "../../../include/config.h"
#include "../../../include/connection.h"
#include <stdio.h>
#include <iostream> // for std::cout and and std::endl

int main (int argc, char *argv[]) {
    Config config;
    config.load("config.yml", "broadcast");

    Connection con(config);
    con.start();
}
