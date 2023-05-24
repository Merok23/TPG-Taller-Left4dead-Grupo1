#include <string>

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

