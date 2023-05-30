#ifndef SERVER_SEND_THREAD_H
#define SERVER_SEND_THREAD_H
#include <atomic>   
#include <memory>

#include "../common/thread.h"   
#include "server_protocol.h"
#include "../common/queue.h"


class SendThread : public Thread {
    private:
        ServerProtocol& protocol; 
        Queue<std::shared_ptr<GameStateForClient>>& client_queue; 
        std::atomic<bool> finished; 

    public:
        SendThread(ServerProtocol& protocol, 
            Queue<std::shared_ptr<GameStateForClient>>& client_queue);
        
        bool isFinished();
        void stop();
        virtual void run() override; 
};
#endif
