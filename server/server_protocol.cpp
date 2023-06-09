#include <vector>
#include <array>
#include <map>
#include <utility>

#include "server_protocol.h"


#define CREATE_ROOM_COMMAND 0x01
#define JOIN_ROOM_COMMAND 0x02
#define ADD_PLAYER_COMMAND 0x03
#define MOVE_PLAYER_COMMAND 0x04
#define SHOOT_PLAYER_COMMAND 0x05
#define RELOAD_PLAYER_COMMAND 0x06
#define CHEAT_INFINITE_HITPOINTS_COMMAND 0x07
#define CHEAT_SPAWN_COMMON_INFECTED_COMMAND 0x08
#define CHEAT_KILL_ALL_INFECTED_COMMAND 0x09

ServerProtocol::ServerProtocol(Socket socket) : socket(std::move(socket)), was_closed(false) {
    return; 
}

// --------------------------------- FUNCIONES DE RECIBIR BYTES ---------------------------------//

uint32_t ServerProtocol::receieveUnsignedInteger() {
    uint32_t number;
    socket.recvall(&number, sizeof(uint32_t), &was_closed);
    number = ntohl(number);
    return number;
}

std::string ServerProtocol::receiveString() {
    uint32_t len; 
    socket.recvall(&len, sizeof(uint32_t), &was_closed); 
    len = ntohl(len); 

    std::vector<char> string(len, 0x00);
    socket.recvall(string.data(), len, &was_closed);
    return std::string(string.begin(), string.end());
}

// --------------------------------- FUNCIONES DE ENVIAR BYTES ---------------------------------//

void ServerProtocol::sendUnsignedInteger(uint32_t number) {
    uint32_t number_to_send = htonl(number);
    socket.sendall(&number_to_send, sizeof(uint32_t), &was_closed);
}

void ServerProtocol::sendString(const std::string& string) {
    uint32_t len = string.length();
    len = htonl(len);
    socket.sendall(&len, sizeof(uint32_t), &was_closed);
    socket.sendall((char*)string.c_str(), string.length(), &was_closed);
}

void ServerProtocol::sendInteger(int32_t number) {
    int32_t number_to_send = htonl(number);
    socket.sendall(&number_to_send, sizeof(int32_t), &was_closed);
}

void ServerProtocol::sendBool(const bool &boolean) {
    socket.sendall(&boolean, sizeof(uint8_t), &was_closed);
}

// --------------------------------- FUNCIONES DE RECIBIR ACCIONES ---------------------------------//

std::shared_ptr<Action> ServerProtocol::receiveAction() {
    uint8_t command;
    int recv_bytes = socket.recvall(&command, sizeof(uint8_t), &was_closed);
    if (was_closed && recv_bytes == 0) return NULL; 
    if (was_closed && recv_bytes != 0) throw LibError(errno, "Socket was closed while receiving action. Errno:");
    std::shared_ptr<Action> action = NULL;
    switch (command) {
        case ADD_PLAYER_COMMAND:
            action = receiveAddPlayer();
            break;
        case MOVE_PLAYER_COMMAND:
            action = receiveMoving();
            break;
        case SHOOT_PLAYER_COMMAND:
            action = receiveShooting();
            break;
        case RELOAD_PLAYER_COMMAND:
            action = receiveReloading();
            break;
        case CHEAT_INFINITE_HITPOINTS_COMMAND:
            action = std::make_shared<SetInfiniteHitpointsCheat>();
            break;
        case CHEAT_SPAWN_COMMON_INFECTED_COMMAND:
            action = std::make_shared<SpawnCommonInfectedCheat>();
            break;
        case CHEAT_KILL_ALL_INFECTED_COMMAND:
            action = std::make_shared<KillAllInfectedCheat>();
            break;
        default:
            break;
    }
/*
    if (command == MOVE_PLAYER_COMMAND) {
        action = receiveMoving();
    } else if (command == ADD_PLAYER_COMMAND) {
        action = receiveAddPlayer();
    } else if (command == SHOOT_PLAYER_COMMAND) {
        action = receiveShooting();
    } else if (command == RELOAD_PLAYER_COMMAND) {
        action = receiveReloading();
    }
*/
    return action;
}
 std::shared_ptr<Action> ServerProtocol::receiveMoving() {
    int8_t position_x, position_y;
    socket.recvall(&position_x, sizeof(uint8_t), &was_closed);
    if (was_closed) throw LibError(errno, "Socket was closed while receiving position. Errno: ");
    socket.recvall(&position_y, sizeof(uint8_t), &was_closed);
    if (was_closed) throw LibError(errno, "Socket was closed while receiving position. Errno: ");;

    std::array<int8_t, 2> positionArray = {position_x, position_y};
    std::shared_ptr<Action> action = std::make_shared<Moving>(positionArray);
    return action;
}

std::shared_ptr<Action>  ServerProtocol::receiveAddPlayer() {
    std::string weapon = receiveString();
    std::shared_ptr<Action> action = nullptr; 
    if (was_closed) throw LibError(errno, "Socket was closed while receiving weapon. Errno: ");
    if (weapon == "idf") action = std::make_shared<CreateSoldierIdf>();
    else if (weapon == "scout") action = std::make_shared<CreateSoldierScout>();
    else if (weapon == "p90") action = std::make_shared<CreateSoldierP90>();
    return action;
}

std::shared_ptr<Action> ServerProtocol::receiveShooting() {
    uint8_t shooting;
    socket.recvall(&shooting, sizeof(uint8_t), &was_closed);
    if (was_closed) throw LibError(errno, "Socket was closed while receiving shooting. Errno: ");
    std::shared_ptr<Action> action = std::make_shared<Shooting>((bool)shooting);
    return action;
}

std::shared_ptr<Action> ServerProtocol::receiveReloading() {
    uint8_t reloading;
    socket.recvall(&reloading, sizeof(uint8_t), &was_closed);
    if (was_closed) throw LibError(errno, "Socket was closed while receiving reloading. Errno: ");
    std::shared_ptr<Action> action = std::make_shared<Reloading>((bool)reloading);
    return action; 
}

command_t ServerProtocol::receiveCommand() {
    uint8_t command;
    uint8_t bytes = socket.recvall(&command, sizeof(uint8_t), &was_closed);
    if (was_closed && bytes == 0) return command_t();
    if (was_closed && bytes != 0) throw LibError(errno, "Socket was closed while receiving command. Errno: ");
    command_t return_command = command_t(); 
    if (command == CREATE_ROOM_COMMAND) {
        return_command.type = CREATE_ROOM;
        return_command.room_name = receiveString();
        if (was_closed) throw LibError(errno, "Socket was closed while receiving room name. Errno: ");
        uint8_t game_mode;
        socket.recvall(&game_mode, sizeof(uint8_t), &was_closed);
        if (was_closed) throw LibError(errno, "Socket was closed while receiving game mode. Errno: ");
        return_command.game_mode = intToGameMode(game_mode);
    } else if (command == JOIN_ROOM_COMMAND) {
        return_command.type = JOIN_ROOM;
        return_command.room_id = receieveUnsignedInteger();
        if (was_closed) throw LibError(errno, "Socket was closed while receiving room id. Errno: ");
    }
    return return_command;
}

GameMode ServerProtocol::intToGameMode(uint8_t game_mode) {
    if (game_mode == 1) return GameMode::SURVIVAL;
    return GameMode::CLEAR_THE_ZONE;
}

// --------------------------------- FUNCIONES DE ENVIAR ACCIONES ---------------------------------//

void ServerProtocol::sendGameState(std::shared_ptr<GameStateForClient> game_state) {
    this->sendFinishConditions(game_state->isGameOver(), game_state->didPlayersWin());
    std::map<uint32_t, Entity*> entities = game_state->getEntities();
    sendUnsignedInteger(entities.size());
    if (was_closed) throw LibError(errno, "Socket was closed while sending entities size. Errno: ");
    for (auto entity : entities) {
        sendUnsignedInteger(entity.first); //id
        if (was_closed) throw LibError(errno, "Socket was closed while sending entity id. Errno: ");
        
        sendString(entity.second->getState());
        if (was_closed) throw LibError(errno, "Socket was closed while sending entity state. Errno: ");

        sendString(entity.second->getEntityType());
        if (was_closed) throw LibError(errno, "Socket was closed while sending entity type. Errno: ");

        sendInteger(entity.second->getHitPoints());
        if (was_closed) throw LibError(errno, "Socket was closed while sending entity hit points. Errno: ");

        int32_t interface_x = entity.second->getDirectionOfMovement()->getX() - 100;
        sendInteger(interface_x);
        if (was_closed) throw LibError(errno, "Socket was closed while sending entity direction of movement x. Errno: ");

        int32_t interface_y = CONFIG.scenario_height - entity.second->getDirectionOfMovement()->getY() + 450;
        sendInteger(interface_y);
        if (was_closed) throw LibError(errno, "Socket was closed while sending entity direction of movement y. Errno: ");

        this->sendBool(entity.second->getDirectionOfMovement()->isFacingLeft());
        if (was_closed) throw LibError(errno, "Socket was closed while sending entity direction of movement facing left. Errno: ");

        this->sendBool(entity.second->getDirectionOfMovement()->isMovingUp());
        if (was_closed) throw LibError(errno, "Socket was closed while sending entity direction of movement facing up. Errno: ");
        
        if (entity.second->getEntityType() == "player") {
            Player* player = dynamic_cast<Player*>(entity.second);
            sendString(player->getWeaponType());
            if (was_closed) throw LibError(errno, "Socket was closed while sending player weapon type. Errno: ");
            
            sendInteger(player->getAmmoLeft());
            if (was_closed) throw LibError(errno, "Socket was closed while sending player ammo left. Errno: ");
            uint8_t lives = player->getLives();
            socket.sendall(&lives, sizeof(uint8_t), &was_closed);
            if (was_closed) throw LibError(errno, "Socket was closed while sending player lives. Errno: ");
        }
        
    }
}

void ServerProtocol::sendFinishConditions(const bool &game_over, const bool &players_won) {
    this->sendBool(game_over);
    if (was_closed) throw LibError(errno, "Socket was closed while sending game over condition. Errno: ");
    this->sendBool(players_won);
    if (was_closed) throw LibError(errno, "Socket was closed while sending players won condition. Errno: ");
}

void ServerProtocol::sendRoomId(uint32_t room_id) {
    sendUnsignedInteger(room_id);
    if (was_closed) throw LibError(errno, "Socket was closed while sending room id. Errno: ");
}

void ServerProtocol::sendJoinResponse(bool accepted) {
    uint8_t response = accepted;
    socket.sendall(&response, sizeof(uint8_t), &was_closed);
    if (was_closed) throw LibError(errno, "Socket was closed while sending join response. Errno: ");
}

// --------------------------------- OTRAS FUNCIONES ---------------------------------//
bool ServerProtocol::isFinished() {
    return was_closed;
}

void ServerProtocol::closeSocket() {
    if (was_closed) return;
    socket.shutdown(SHUT_RDWR);
    socket.close();
}
