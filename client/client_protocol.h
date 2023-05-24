#ifndef CLIENT_PROTOCOL_H
#define CLIENT_PROTOCOL_H
#include <memory>
#include <vector>
#include "../common/socket.h"
#include "game_state.h"

enum COMMANDS_TYPE {
    DEFAULT,
    CREATE_ROOM,
    JOIN_ROOM,
    MOVE_PLAYER,
    ADD_PLAYER
};
typedef struct COMMANDS {
    COMMANDS_TYPE type;
    std::string room_name; 
    uint32_t room_id;
    int32_t x_position;
    int32_t y_position;

    COMMANDS() : 
        type(DEFAULT), room_name(""), room_id(0), x_position(0), y_position(0) {}
} command_t;


class ClientProtocol {
    private:
    Socket socket; 
    bool was_closed; 

    uint32_t receieveUnsignedInteger();
    std::string receiveString();
    int32_t receiveInteger();
    void sendInteger(int32_t number);
    void sendUnsignedInteger(uint32_t number);
    uint8_t receiveUnsignedSmallInteger();
    void sendString(const std::string& string);

    public:
    explicit ClientProtocol(Socket socket);
    void sendCommand(command_t command);
    void sendCreateRoom(const std::string& room_name);
    void sendJoinRoom(int room_id);
    void sendMoving(int x, int y);
    void sendAddPlayer();
    bool isFinished();
    void closeSocket();
    uint32_t receiveRoomId();
    bool receiveJoinResponse();

    GameState* receiveGameState();
};
#endif