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
    SHOOT_PLAYER,
    RELOAD_PLAYER,
    ADD_PLAYER
};

typedef struct command_t {
    COMMANDS_TYPE type;
    std::string room_name;
    std::string game_mode;
    std::string weapon;
    int8_t moving_x;
    int8_t moving_y;
    bool shooting;
    bool reloading;
    uint32_t room_id;
} command_t;

struct COMMANDS {
    command_t createRoom(const std::string& name, const std::string& game_mode) {
        command_t command;
        command.type = CREATE_ROOM;
        command.room_name = name;
        command.game_mode = game_mode;
        return command;
    }

    command_t joinRoom(uint32_t id) {
        command_t command;
        command.type = JOIN_ROOM;
        command.room_id = id;
        return command;
    }

    command_t addPlayer(const std::string& weapon) {
        command_t command;
        command.type = ADD_PLAYER;
        command.weapon = weapon;
        return command;
    }

    command_t setDirectionOfMovement(int8_t x, int8_t y) {
        command_t command;
        command.type = MOVE_PLAYER;
        command.moving_x = x;
        command.moving_y = y;
        return command;
    }

    command_t setShooting(bool shoot) {
        command_t command;
        command.type = SHOOT_PLAYER;
        command.shooting = shoot;
        return command;
    }

    command_t setReloading(bool reload) {
        command_t command;
        command.type = RELOAD_PLAYER;
        command.reloading = reload;
        return command;
    }
};

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
    void sendCreateRoom(const std::string& room_name, const std::string& game_mode);
    void sendJoinRoom(int room_id);
    void sendMoving(int8_t moving_x, int8_t moving_y);
    void sendAddPlayer(const std::string& weapon);
    void sendShooting(int shooting);
    void sendReloading(int reloading);
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