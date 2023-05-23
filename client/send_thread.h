#ifndef CLIENT_SEND_THREAD_H
#define CLIENT_SEND_THREAD_H

#include "../common/thread.h"   
#include "client_protocol.h"
#include "../common/queue.h"
#include <atomic>   


class SendThread : public Thread {
    private:
        ClientProtocol& protocol; 
        Queue<std::string>& queue_comandos;
        std::atomic<bool> finished; 

    public:
        SendThread(ClientProtocol& protocol, Queue<std::string>& queue_comandos);
        
        void stop();
        bool isFinished();
        virtual void run() override; 
};

#endif
