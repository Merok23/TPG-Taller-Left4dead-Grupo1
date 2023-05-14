#include "../common/socket.h"
#include "../common/thread.h"
#include <atomic>
#include <vector>


class ClientAccepter : public Thread {
    private:
        Socket recieving_socket;
        std::vector<ServerClient*> clients; //no usar un vec
        std::atomic<bool> finished;

    public:
        explicit ClientAccepter(char* port);
        virtual void run() override;
        void acceptClient(PartyHandlerMonitor &handler);
        void waitClients();
        void stop();
        ~ClientAccepter();
};