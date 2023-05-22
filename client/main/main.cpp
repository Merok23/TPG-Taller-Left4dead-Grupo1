#include <stdio.h>
#include <iostream>
#include "../client_client.h"

#define HOST argv[1]
#define SERV argv[2] 


int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cout << "Error: Invalid arguments"; 
    }
    try {
        Client client(HOST, SERV); 
        client.run();  
    } catch (const std::runtime_error& e) {
        if (strcmp(e.what(), "send socket failed: Broken pipe") == 0) {
            std::cout << "Server disconnected" << std::endl;
        } else {
            std::cerr << "Error: " << e.what() << std::endl;
        } 
    }
    return 0;    
}