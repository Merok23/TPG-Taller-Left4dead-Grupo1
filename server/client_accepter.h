#ifndef CLIENT_ACCEPTER_H
#define CLIENT_ACCEPTER_H

#include "../common/socket.h"
#include "../common/thread.h"
#include "game.h"
#include "action.h"
#include "game_loop.h"
#include "server_client.h"
#include <atomic>
#include <vector>
#include <list>


class ClientAccepter : public Thread {
    private:
        Socket recieving_socket;
        GameLoop game_loop; 
        std::list<ServerClient*> clients;
        std::atomic<bool> finished;

    public:
        explicit ClientAccepter(const char* port);
        virtual void run() override;
        void acceptClient(Queue<Action*>&  game_queue, GameLoop& game_loop);
        void removeDeadClients();
        void stop();
        ~ClientAccepter();
};
#endif

