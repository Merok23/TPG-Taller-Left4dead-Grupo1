#ifndef SERVER_PROTOCOL_H
#define SERVER_PROTOCOL_H

#include <array>
#include <string>
#include <memory>

#include "../common/socket.h"
#include "action_moving.h"
#include "action_shooting.h"
#include "action_reloading.h"
#include "action_create_soldier_idf.h"
#include "action_create_soldier_p90.h"
#include "action_create_soldier_scout.h"
#include "action_cheat_infinite_hp.h"
#include "action_cheat_spawn_common_infected.h"
#include "action_cheat_kill_all_infected.h"


enum COMMANDS_TYPE {
    DEFAULT,
    CREATE_ROOM,
    JOIN_ROOM
};

typedef struct COMMANDS {
    COMMANDS_TYPE type;
    std::string room_name;
    uint32_t room_id;
    GameMode game_mode;
    COMMANDS() : 
        type(DEFAULT), room_name(""), room_id(0), game_mode(GameMode::SURVIVAL) {}
} command_t;


class ServerProtocol {
    private:
    Socket socket; 
    bool was_closed; 

    void sendInteger(int32_t number);
    void sendString(const std::string& string);
    uint32_t receieveUnsignedInteger();
    void sendUnsignedInteger(uint32_t number);
    void sendBool(const bool& boolean);
    void sendFinishConditions(const bool &game_finished, const bool &game_won);
    std::string receiveString();
    std::shared_ptr<Action> receiveMoving();
    std::shared_ptr<Action> receiveShooting();
    std::shared_ptr<Action> receiveReloading();
    std::shared_ptr<Action> receiveAddPlayer();
    uint8_t receiveSmallUnsignedInt();
    int8_t receiveSmallInt();
    GameMode intToGameMode(uint8_t game_mode);


    public:
    explicit ServerProtocol(Socket socket);
    std::shared_ptr<Action> receiveAction();
    command_t receiveCommand();
    void sendRoomId(uint32_t room_id);
    void sendJoinResponse(bool accepted);
    void sendGameState(std::shared_ptr<GameStateForClient> game_state);
    bool isFinished();
    void closeSocket();
};
#endif
