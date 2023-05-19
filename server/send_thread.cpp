#include "send_thread.h"

SendThread::SendThread(ServerProtocol& protocol, 
    Queue<std::shared_ptr<GameStateForClient>>& game_queue) : 
        protocol(protocol), game_queue(game_queue) {}


void SendThread::run() {
    while (!finished) {
        std::shared_ptr<GameStateForClient> game_state = game_queue.pop();
        protocol.sendGameState(game_state); 
    }
}

void SendThread::stop() {
    finished = true;
}

bool SendThread::isFinished() {
    return finished;
}