#ifndef SERVER_PROTOCOL_H
#define SERVER_PROTOCOL_H

#include <array>
#include "../common/socket.h"
#include "../common/moving.h"


class ServerProtocol {
    private:
    Socket socket; 
    bool connected; 

    public:
    ServerProtocol(Socket socket);
    Action* receiveAction();
};
#endif