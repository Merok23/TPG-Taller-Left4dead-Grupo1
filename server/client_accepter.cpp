#include "client_accepter.h"
#include "server_client.h"

#define MAX_ELEMENTS_QUEUE 10000

ClientAccepter::ClientAccepter(const char* port) : recieving_socket(Socket(port)), finished(false) {}

void ClientAccepter::run() {
    GameLoop* game_loop = new GameLoop();
    while (!finished) {
        acceptClient(game_loop);
    }
}

void ClientAccepter::acceptClient(GameLoop* game_loop) {
    try {
        Socket socket = recieving_socket.accept();
        ServerClient* client = new ServerClient(std::move(socket), game_loop->getQueue());
        std::cout << "El client es " << client << std::endl;
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
