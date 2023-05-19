#include <iostream>
#include "../client_accepter.h"
#include "../config_parser.h"
#include <string>


const config global_config = Parser(std::string("../game_config.yaml")).setSingletonStruct();

int main (int argc, char *argv[]) {

    if (argc != 2) {
        std::cout << "Usage: ./server <port>" << std::endl;
        return 1;
    }
   
   printf("global_config: soldier_health: %d\n", global_config.soldier_health);
    // Initialize the server
    //ClientAccepter server(argv[1]);
    

    return 0;
}