#ifndef SERVER_RECIEVE_THREAD_H
#define SERVER_RECIEVE_THREAD_H

#include <atomic>
#include <memory>

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
        uint32_t client_id;
        uint32_t room_id;
        bool start_playing; 

    public:
        ReceiveThread(ServerProtocol& protocol, 
            GameHandler& game_handler, 
                Queue<std::shared_ptr<GameStateForClient>>& client_queue);
        
        void stop();
        void receiveGameActions();
        void receiveCommand();
        bool isFinished();
        virtual void run() override;
};
#endif
