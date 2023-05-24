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

    int32_t receiveInteger();
    void sendInteger(int32_t number);
    void sendString(const std::string& string);
    uint32_t receieveUnsignedInteger();
    void sendUnsignedInteger(uint32_t number);
    std::string receiveString();

    public:
    explicit ServerProtocol(Socket socket);
    Action* receiveAction();
    std::string receiveCommand();
    std::string receiveRoomName();
    uint32_t receiveRoomId();
    void sendRoomId(uint32_t room_id);
    void sendJoinResponse(bool accepted);
    void sendGameState(std::shared_ptr<GameStateForClient> game_state);
    bool isFinished();
    void closeSocket();
};
#endif