#ifndef SERVER_SERVER_H
#define SERVER_SERVER_H


#include "../common/server_protocol.h"
#include "client_accepter.h"
#include "server_server.h"
#include "server_partida.h"
#include "../common/queue.h"

class Server {
    private: 
    Socket socket;
    const char* port; 
    Partida* partida; 
    Queue<Action*>* game_queue;


    public:
    Server(const char* port);
    void run(); 
};

#endif
