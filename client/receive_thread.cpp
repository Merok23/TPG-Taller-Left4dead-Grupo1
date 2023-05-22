#include "receive_thread.h"

ReceiveThread::ReceiveThread(ClientProtocol& protocol, 
    Queue<GameState*>& queue) : 
    protocol(protocol), game_states(queue), finished(false) {}  

void ReceiveThread::run() {
    while (!finished) {
        GameState* game_state = protocol.receiveGameState();
        if(protocol.isFinished()) {
                finished = true;
                break;
        }   
        if (game_state) {
            game_state->print();
            game_states.push(std::move(game_state)); 
        }
    }
}

void ReceiveThread::stop() {
    finished = true;
}