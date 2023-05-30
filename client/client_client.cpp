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
//#include  "common_protocol.h"


Client::Client(const char* hostname, const char* servname) : 
    socket(hostname, servname), protocol(std::move(socket)), connected(true) {
   return; 
}

void Client::run() {
    graphics.run();
    while (connected) {
        std::string line;
        std::getline(std::cin, line);
        std::istringstream iss(line);
        std::string action; 
        iss >> action;
        if (action == "leave") {
            break; 
        }
        if (action == "move") {
            int x;
            int y;
            iss >> x; 
            iss >> y; 
            this->protocol.sendMoving(x, y);
            continue; 
        } else { 
            std::cout << "Invalid command" << std::endl; 
        } 
    }
}