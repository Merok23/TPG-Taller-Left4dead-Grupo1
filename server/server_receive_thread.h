#ifndef SERVER_RECIEVE_THREAD_H
#define SERVER_RECIEVE_THREAD_H

#include <atomic>
#include "../common/thread.h"
#include "server_protocol.h"
#include "../common/queue.h"
#include "../server/game.h"
#include "../server/game_handler.h"

class ReceiveThread : public Thread {
    private:
        ServerProtocol& protocol; 
        GameHandler& game_handler;
        Queue<std::shared_ptr<GameStateForClient>>& client_queue;
        std::atomic<bool> finished;

    public:
        ReceiveThread(ServerProtocol& protocol, 
            GameHandler& game_handler, 
                Queue<std::shared_ptr<GameStateForClient>>& client_queue);
        
        void receiveCommands(); 
        void stop();
        bool isFinished();
        virtual void run() override {
            receiveCommands();
        }
};
#endif