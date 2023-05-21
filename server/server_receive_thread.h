#ifndef SERVER_RECIEVE_THREAD_H
#define SERVER_RECIEVE_THREAD_H

#include <atomic>
#include "../common/thread.h"
#include "server_protocol.h"
#include "../common/queue.h"
#include "../server/game.h"
#include "action.h"


class ReceiveThread : public Thread {
    private:
        ServerProtocol& protocol; 
        Queue<Action*>& game_queue; 
        std::atomic<bool> finished; 

    public:
        ReceiveThread(ServerProtocol& protocol, 
            Queue<Action*>& queue);
        
        void receiveCommands(); 
        void stop();
        bool isFinished();
        virtual void run() override {
            receiveCommands();
        }
};
#endif