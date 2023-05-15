#ifndef CLIENT_PROTOCOL_H
#define CLIENT_PROTOCOL_H

#include "../common/socket.h"

class ClientProtocol {
    private:
    Socket socket; 
    bool connected; 

    public:
    ClientProtocol(Socket socket);
    void sendMoving(int x, int y);
};
#endif