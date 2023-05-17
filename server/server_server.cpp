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

Server::Server(const char* port) : socket(port), port(port) {
    game_queue = new Queue<Action*>(MAX_ELEMENTS_QUEUE);
    partida = new Partida(game_queue);
    return;
}

void Server::run() {
    ClientAccepter acceptorThread(port, *game_queue); 
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

