#include "client_accepter.h"
#include "server_client.h"

ClientAccepter::ClientAccepter(const char* port, Queue<Action*>& game_queue) : recieving_socket(Socket(port)), game_queue(game_queue), finished(false){}

void ClientAccepter::run() {
    while (!finished) {
        acceptClient();
    }
}

void ClientAccepter::acceptClient() {
    try {
        Socket socket = recieving_socket.accept();
        ServerClient* client = new ServerClient(std::move(socket), game_queue);
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
