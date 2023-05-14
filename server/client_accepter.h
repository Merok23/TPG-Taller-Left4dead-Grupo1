#include "../common/socket.h"
#include "../common/thread.h"
#include "game.h"
#include <atomic>
#include <vector>


class ClientAccepter : public Thread {
    private:
        Socket recieving_socket;
        Game game;
        std::atomic<bool> finished;

    public:
        explicit ClientAccepter(char* port);
        virtual void run() override;
        void acceptClient();
        void waitClients();
        void stop();
        ~ClientAccepter();
};