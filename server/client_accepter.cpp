#include <utility>

#include "client_accepter.h"
#include "server_client.h"


#define MAX_ELEMENTS_QUEUE 10000

ClientAccepter::ClientAccepter(const char* port) : recieving_socket(Socket(port)), game_handler(), finished(false) {}

void ClientAccepter::run() {
    acceptClient();
}

void ClientAccepter::acceptClient() {
    while (!finished){
        try {
        Socket socket = recieving_socket.accept();
        ServerClient* client = new ServerClient(std::move(socket), game_handler);
        clients.push_back(client);
    } catch (LibError &e) {
        if (finished) return;
        std::cout << e.what() << std::endl;
    }
    removeDeadClients(); 
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
}

ClientAccepter::~ClientAccepter() {
     while (!clients.empty()) {
        auto client = clients.front();
        clients.pop_front();
        delete client;
    }
    recieving_socket.shutdown(SHUT_RDWR); 
    recieving_socket.close();
}
