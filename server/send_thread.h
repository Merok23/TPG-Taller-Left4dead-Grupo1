#ifndef SERVER_SEND_THREAD_H
#define SERVER_SEND_THREAD_H
#include "../common/thread.h"   
#include "server_protocol.h"
#include "../common/queue.h"
#include <atomic>   


class SendThread : public Thread {
    private:
        ServerProtocol& protocol; 
        Queue<GameStateForClient*>& client_queue; 
        std::atomic<bool> finished; 

    public:
        SendThread(ServerProtocol& protocol, 
            Queue<GameStateForClient*>& queue);
        
        bool isFinished();
        void stop();
        virtual void run() override; 
};

#endif