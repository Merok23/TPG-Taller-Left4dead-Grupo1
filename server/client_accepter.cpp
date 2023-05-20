#include "client_accepter.h"
#include "server_client.h"


#define MAX_ELEMENTS_QUEUE 10000

ClientAccepter::ClientAccepter(const char* port) : recieving_socket(Socket(port)), finished(false) {}

void ClientAccepter::run() {
    GameLoop* game_loop = new GameLoop(); // heap? (probablemente ta bien) perdemos memoria
    game_loop->start(); 
    while (!finished) {
        acceptClient(game_loop);
    }
    game_loop->stop(); 
    game_loop->join(); //mover despues al constructor
}

void ClientAccepter::acceptClient(GameLoop* game_loop) {
    try {
        Socket socket = recieving_socket.accept();
        ServerClient* client = new ServerClient(std::move(socket), game_loop->getQueue());
        clients.push_back(client);
        removeDeadClients();
    } catch (LibError &e) {
        if (finished) return;
        std::cout << e.what() << std::endl;
    }
}

void ClientAccepter::removeDeadClients() {
    auto it = clients.begin();
    while (it != clients.end()) {
        if ((*it)->isFinished()) {
            delete *it;
            it = clients.erase(it);
        } else {
            ++it;
        }
    }
}

void ClientAccepter::stop() {
    finished = true;
    while (!clients.empty()) {
        auto client = clients.front();
        clients.pop_front();
        delete client;
    }
    recieving_socket.shutdown(SHUT_RDWR); 
    recieving_socket.close();
}

ClientAccepter::~ClientAccepter() {}
