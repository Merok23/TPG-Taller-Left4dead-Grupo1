#ifndef CLIENT_PROTOCOL_H
#define CLIENT_PROTOCOL_H
#include <memory>
#include "../common/socket.h"
#include "game_state.h"
#include "player.h"

class ClientProtocol {
    private:
    Socket socket; 
    bool connected; 

    public:
    explicit ClientProtocol(Socket socket);
    void sendMoving(int x, int y);
    std::unique_ptr<GameState>  receiveGameState();
};
#endif