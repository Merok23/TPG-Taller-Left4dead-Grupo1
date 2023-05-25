#include <utility>

#include "server_client.h"  

#define MAX_ELEMENTS_QUEUE 10000
ServerClient::ServerClient(Socket socket, GameHandler& game_handler) : 
    protocol(std::move(socket)), 
        game_handler(game_handler),
            client_queue(MAX_ELEMENTS_QUEUE),
                    receive_thread(protocol, game_handler, client_queue),  
                        send_thread(protocol, client_queue) {
    receive_thread.start();
    send_thread.start();
}

ServerClient::~ServerClient() {
    protocol.closeSocket();
    client_queue.close();
    receive_thread.stop();
    send_thread.stop();
    receive_thread.join();
    send_thread.join();
}

bool ServerClient::isFinished() {
    return (receive_thread.isFinished() || send_thread.isFinished());
}
