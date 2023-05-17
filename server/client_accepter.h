#ifndef CLIENT_ACCEPTER_H
#define CLIENT_ACCEPTER_H

#include "../common/socket.h"
#include "../common/thread.h"
#include "game.h"
#include "../common/action.h"
#include "game_loop.h"

#include <atomic>
#include <vector>


class ClientAccepter : public Thread {
    private:
        Socket recieving_socket;
        std::atomic<bool> finished;

    public:
        explicit ClientAccepter(const char* port);
        virtual void run() override;
        void acceptClient(GameLoop* game_loop);
        void waitClients();
        void stop();
        ~ClientAccepter();
};
#endif
