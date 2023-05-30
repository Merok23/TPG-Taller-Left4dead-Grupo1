#ifndef CLIENT_SEND_THREAD_H
#define CLIENT_SEND_THREAD_H

#include <atomic>   
#include <string>

#include "../common/thread.h"   
#include "client_protocol.h"
#include "../common/queue.h"


class SendThread : public Thread {
    private:
        ClientProtocol& protocol; 
        Queue<std::string>& queue_comandos;
        std::atomic<bool> finished; 

    public:
        SendThread(ClientProtocol& protocol, Queue<std::string>& queue_comandos);
        
        void stop();
        virtual void run() override; 
};

#endif
