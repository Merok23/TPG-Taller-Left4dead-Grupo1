#ifndef SERVER_SEND_THREAD_H
#define SERVER_SEND_THREAD_H
#include "../common/thread.h"   
#include "../common/server_protocol.h"  
#include "../common/queue.h"
#include <atomic>   

class SendThread : public Thread {
    private:
        ServerProtocol& protocol; 
        Queue<std::shared_ptr<GameStateForClient>>& game_queue; 
        std::atomic<bool> finished; 

    public:
        SendThread(ServerProtocol& protocol, 
            Queue<std::shared_ptr<GameStateForClient>>& queue);
        
        void stop();
        virtual void run() override; 
};

#endif