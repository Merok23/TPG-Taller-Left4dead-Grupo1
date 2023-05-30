#ifndef CLIENT_RECIEVE_THREAD_H
#define CLIENT_RECIEVE_THREAD_H

#include <atomic>
#include <memory>
#include "../common/thread.h"
#include "client_protocol.h"
#include "../common/queue.h"


class ReceiveThread : public Thread {
    private:
        ClientProtocol& protocol; 
        Queue<GameState *>& game_states; 
        std::atomic<bool> finished;

    public:
        ReceiveThread(ClientProtocol& protocol, 
            Queue<GameState *>& queue);
        
        void stop();
        bool isFinished();
        virtual void run() override; 
};
#endif
