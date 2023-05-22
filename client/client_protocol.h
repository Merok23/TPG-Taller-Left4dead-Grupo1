#ifndef CLIENT_PROTOCOL_H
#define CLIENT_PROTOCOL_H
#include <memory>
#include <vector>
#include "../common/socket.h"
#include "game_state.h"

class ClientProtocol {
    private:
    Socket socket; 
    bool was_closed; 

    uint32_t receieveUnsignedInteger();
    std::string receiveString();
    int32_t receiveInteger();
    void sendInteger(int32_t number);

    public:
    explicit ClientProtocol(Socket socket);
    void sendMoving(int x, int y);
    void sendAddPlayer();
    bool isFinished();
    void closeSocket();
    GameState* receiveGameState();
};
#endif