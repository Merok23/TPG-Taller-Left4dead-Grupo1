#include "send_thread.h"

SendThread::SendThread(ServerProtocol& protocol, 
    Queue<std::shared_ptr<GameStateForClient>>& client_queue) : 
        protocol(protocol), client_queue(client_queue), finished(false) {}


void SendThread::run() {
    while (!finished && !protocol.isFinished()) {
        try {
            std::shared_ptr<GameStateForClient> game_state = client_queue.pop();
            protocol.sendGameState(game_state); 
        } catch(std::runtime_error& e) {
            std::string message = e.what();
            if (message.compare("The queue is closed") == 0) {
                finished = true;
            } 
    }
} 
}

void SendThread::stop() {
    finished = true;
}

bool SendThread::isFinished() {
    return finished;
}