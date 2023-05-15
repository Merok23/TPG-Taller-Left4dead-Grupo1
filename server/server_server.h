#ifndef SERVER_SERVER_H
#define SERVER_SERVER_H


#include "../common/server_protocol.h"
#include "client_accepter.h"
#include "server_server.h"

class Server {
    private: 
    Socket socket;
    const char* port; 

    public:
    Server(const char* port);
    void run(); 
};

#endif
