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
    } catch (const LibError& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;    
}
