#include <utility>

#include "receive_thread.h"

ReceiveThread::ReceiveThread(ClientProtocol& protocol, 
    Queue<std::shared_ptr<GameState>>& queue) : 
    protocol(protocol), game_states(queue), finished(false) {}  

void ReceiveThread::run() {
    while (!finished) {
        try {
            std::shared_ptr<GameState> game_state = protocol.receiveGameState();
            if ((!game_state && !finished)) {
                std::cout << "ERROR: Server was disconnected" << std::endl; //Como se lo paso a abril??????? 
                finished = true;
                break;
            }   
            if (game_state) {
                //game_state->print();
                game_states.push(std::move(game_state)); 
            }
        } catch(const LibError &e) {
            std::cerr << "Error: " << e.what() << std::endl;
            finished = true;
        } 
    }
}

void ReceiveThread::stop() {
    finished = true;
}
