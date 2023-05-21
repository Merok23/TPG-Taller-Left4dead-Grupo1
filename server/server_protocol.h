#ifndef SERVER_PROTOCOL_H
#define SERVER_PROTOCOL_H

#include <array>
#include "../common/socket.h"
#include "action_moving.h"
#include "action_create_player.h"


class ServerProtocol {
    private:
    Socket socket; 
    bool was_closed; 

    public:
    explicit ServerProtocol(Socket socket);
    Action* receiveAction();
    void sendGameState(GameStateForClient* game_state);
    bool isFinished();
    void closeSocket();
};
#endif