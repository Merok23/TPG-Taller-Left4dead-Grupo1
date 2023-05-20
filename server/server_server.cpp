#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <sstream>
#include <sys/types.h>
#include <netinet/in.h>
#include <iostream>
#include <fstream>

#include "server_server.h"
#define MAX_ELEMENTS_QUEUE 1000

Server::Server(const char* port) : port(port) {
    return;
}

void Server::run() {
    ClientAccepter acceptorThread(port); 
    acceptorThread.start();  
    std::string leave; 
    while (true) {
        std::cin >> leave; 
        if (leave == "q") {
            acceptorThread.stop(); 
            acceptorThread.join(); 
            break;
        }
    } 
}

