#include <iostream>
#include "../client_accepter.h"
#include "../config.h"
#include "../server.h"
#include <yaml-cpp/yaml.h>


#define PORT argv[1]
#define CONFIG_FILE argv[2]

int main(int argc, char *argv[])  {
    if (argc > 3 || argc < 2) {
        std::cout << "Error: Invalid arguments" << std::endl; 
        return -1;  
    }
    try {
        if (argc == 3) {
            Config config(CONFIG_FILE);
        } 
        Server server = Server(PORT); 
        server.run();  
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl; 
    }
    return 0; 
}
