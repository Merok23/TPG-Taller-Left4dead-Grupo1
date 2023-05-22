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

    int32_t receive_int32_number();
    void send_int32_number(int32_t number);
    std::string receiveString();
    void sendString(const std::string& string);
    uint32_t receieve_uint32_number();
    void send_uint32_number(uint32_t number);

    public:
    explicit ServerProtocol(Socket socket);
    Action* receiveAction();
    void sendGameState(std::shared_ptr<GameStateForClient> game_state);
    bool isFinished();
    void closeSocket();
};
#endif