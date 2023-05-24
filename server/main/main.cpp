#include <iostream>
#include "../client_accepter.h"
#include "../config.h"
#include "../server_server.h"

#define PORT argv[1]

int main(int argc, char *argv[])  {
    if (argc != 2) {
        std::cout << "Error: Invalid arguments" << std::endl; 
        return -1;  
    }
    try {
        Server server = Server(PORT); 
        server.run();  
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl; 
    }
    return 0; 
}
