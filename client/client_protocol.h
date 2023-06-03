#ifndef CLIENT_PROTOCOL_H
#define CLIENT_PROTOCOL_H
#include <memory>
#include <string>
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
    std::string weapon;
    uint32_t room_id;
    int32_t x_position;
    int32_t y_position;

    COMMANDS() : 
        type(DEFAULT), room_name(""), weapon(""), room_id(0), x_position(0), y_position(0) {}

         COMMANDS(COMMANDS_TYPE _type, const std::string& _room_name, const std::string& _weapon, uint32_t _room_id, int32_t _x_position, int32_t _y_position) :
        type(_type), room_name(_room_name), weapon(_weapon), room_id(_room_id), x_position(_x_position), y_position(_y_position) {}
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
    void sendCreateRoom(const std::string& room_name);
    void sendJoinRoom(int room_id);
    void sendMoving(int x, int y);
    void sendAddPlayer(const std::string& weapon);
    State stringToState(const std::string& state);
    

    public:
    explicit ClientProtocol(Socket socket);
    void sendCommand(command_t command);
    bool isFinished();
    void closeSocket();
    uint32_t receiveRoomId();
    bool receiveJoinResponse();

    GameState* receiveGameState();
};
#endif