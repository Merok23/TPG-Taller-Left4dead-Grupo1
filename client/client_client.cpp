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
#include <thread>

#include "client_client.h"



Client::Client(const char* hostname, const char* servname) : 
    socket(hostname, servname), protocol(std::move(socket)) {
   return; 
}

void Client::run() {
        while (true) {
            std::string line;
            std::getline(std::cin, line);
            std::istringstream iss(line);
            std::string action; 
            iss >> action;
            if (action == "leave") {
                break; 
            } else if (action == "create") {
                this->protocol.sendAddPlayer(); 
                std::cout << this->protocol.recievePlayerMovement() << std::endl;
            } else if (action == "move") {
                int x;
                int y;
                iss >> x; 
                iss >> y; 
                this->protocol.sendMoving(x, y);
                //std::unique_ptr<GameState> game_state = this->protocol.receiveGameState(); 
                std::cout << this->protocol.recievePlayerMovement() << std::endl;
                continue; 
            } else { 
                std::cout << "Invalid command" << std::endl; 
            } 
    }
}