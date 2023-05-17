#ifndef SERVER_SERVER_H
#define SERVER_SERVER_H


#include "../common/server_protocol.h"
#include "client_accepter.h"
#include "server_partida.h"
#include "../common/queue.h"
#include "../common/thread.h"

class Server {
    private: 
    Socket socket;
    const char* port; 
    Queue<Action*>* game_queue;
    Partida* partida; 

    public:
    explicit Server(const char* port);
    void run(); 
};

#endif
