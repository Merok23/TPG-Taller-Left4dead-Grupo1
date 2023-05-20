#ifndef SERVER_SERVER_H
#define SERVER_SERVER_H


#include "server_protocol.h"
#include "client_accepter.h"
#include "game_loop.h"
#include "../common/queue.h"
#include "../common/thread.h"

class Server {
    private: 
    const char* port; 

    public:
    explicit Server(const char* port);
    void run(); 
};

#endif
