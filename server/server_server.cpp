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

Server::Server(const char* port) : socket(port), port(port) {
    return;
}

void Server::run() {
    ClientAccepter* acceptorThread = new ClientAccepter(port); 
    acceptorThread->start();  
    std::string leave; 
    while (true) {
        std::cin >> leave; 
        if (leave == "q") {
            acceptorThread->stop(); 
            acceptorThread->join(); 
            delete acceptorThread;
            break;
        }
    } 
}

