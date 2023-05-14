#include <iostream>
#include "client_accepter.h"

int main (int argc, char *argv[]) {

    if (argc != 2) {
        std::cout << "Usage: ./server <port>" << std::endl;
        return 1;
    }
    // Initialize the server
    //ClientAccepter server(argv[1]);
    

    return 0;
}