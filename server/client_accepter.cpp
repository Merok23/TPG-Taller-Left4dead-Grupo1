#include "client_accepter.h"

ClientAccepter::ClientAccepter(const char* port) : recieving_socket(Socket(port)), finished(false){}

void ClientAccepter::run() {
    while (!finished) {
        acceptClient();
    }
}

void ClientAccepter::acceptClient() {
    try {
        Socket client = recieving_socket.accept();
        //game.addPlayer(client);
    } catch (LibError &e) {
        if (finished) return;
        std::cout << e.what() << std::endl;
    }
}

void ClientAccepter::stop() {
    finished = true;
    recieving_socket.close();
}

ClientAccepter::~ClientAccepter() {}
