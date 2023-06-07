#include <memory>

#include "send_thread.h"

SendThread::SendThread(ServerProtocol& protocol, 
    Queue<std::shared_ptr<GameStateForClient>>& client_queue) : 
        protocol(protocol), client_queue(client_queue), finished(false) {}


void SendThread::run() {
    while (!finished && !protocol.isFinished()) {
        try {
            std::shared_ptr<GameStateForClient> game_state = client_queue.pop();
            if (protocol.isFinished()) {
                finished = true;
                break;
            }
            protocol.sendGameState(game_state); 
        } catch(const ClosedQueue &e) {
            if (finished) return; 
            std::cerr << "Error: " << e.what() << std::endl;
            finished = true;
        } catch(const LibError &e) {
            std::cerr << "Error: " << e.what() << std::endl;
            finished = true;
        }
    } 
}

void SendThread::stop() {
    finished = true;
}

bool SendThread::isFinished() {
    return finished;
}
