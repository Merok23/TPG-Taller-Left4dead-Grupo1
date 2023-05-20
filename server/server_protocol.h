#ifndef SERVER_PROTOCOL_H
#define SERVER_PROTOCOL_H

#include <array>
#include "../common/socket.h"
#include "../common/action_moving.h"


class ServerProtocol {
    private:
    Socket socket; 
    bool connected; 

    public:
    explicit ServerProtocol(Socket socket);
    std::shared_ptr<Action> receiveAction();
    void sendGameState(std::shared_ptr<GameStateForClient>& game_state);
};
#endif