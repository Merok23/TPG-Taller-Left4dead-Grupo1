#ifndef SERVER_EMISOR_THREAD_H
#define SERVER_EMISOR_THREAD_H

#include <atomic>
#include "../common/thread.h"
#include "../common/server_protocol.h"
#include "../common/queue.h"
#include "../server/game.h"
#include "../common/action.h"

class ReceiveThread : public Thread {
    private:
        ServerProtocol& protocol; 
        Queue<std::shared_ptr<Action>>& game_queue; 
        std::atomic<bool> finished; 

    public:
        ReceiveThread(ServerProtocol& protocol, 
            Queue<std::shared_ptr<Action>>& queue);
        
        void receiveCommands(); 
        void stop();
        virtual void run() override {
            receiveCommands();
        }
};
#endif