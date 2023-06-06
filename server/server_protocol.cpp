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

ServerProtocol::ServerProtocol(Socket socket) : socket(std::move(socket)), was_closed(false) {
    return; 
}

// --------------------------------- FUNCIONES DE RECIBIR BYTES ---------------------------------//
int32_t ServerProtocol::receiveInteger() {
    int32_t number;
    socket.recvall(&number, sizeof(int32_t), &was_closed);
    number = ntohl(number);
    return number;
}


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
// --------------------------------- FUNCIONES DE RECIBIR ACCIONES ---------------------------------//
Action* ServerProtocol::receiveAction() {
    uint8_t command;
    socket.recvall(&command, sizeof(uint8_t), &was_closed);
    if (was_closed) return NULL; 
    Action* action = NULL;
    if (command == MOVE_PLAYER_COMMAND) {
        action = receiveMoving();
    } else if (command == ADD_PLAYER_COMMAND) {
        action = receiveAddPlayer();
    } else if (command == SHOOT_PLAYER_COMMAND) {
        action = receiveShooting();
    } else if (command == RELOAD_PLAYER_COMMAND) {
        action = receiveReloading();
    }
    return action;
}
Action *ServerProtocol::receiveMoving() {
    int8_t position_x, position_y;
    socket.recvall(&position_x, sizeof(uint8_t), &was_closed);
    if (was_closed) return NULL;
    socket.recvall(&position_y, sizeof(uint8_t), &was_closed);
    if (was_closed) return NULL;

    std::array<int8_t, 2> positionArray = {position_x, position_y};
    return new Moving(positionArray); 
}

Action* ServerProtocol::receiveAddPlayer() {
    std::string weapon = receiveString();
    if (was_closed) return NULL;
    if (weapon == "idf") return new CreateSoldierIdf();
    else if (weapon == "p90") return new CreateSoldierP90();
    return new CreateSoldierScout();
}

Action *ServerProtocol::receiveShooting() {
    uint8_t shooting;
    socket.recvall(&shooting, sizeof(uint8_t), &was_closed);
    if (was_closed) return NULL;
    return new Shooting((bool)shooting);
}

Action *ServerProtocol::receiveReloading() {
    uint8_t reloading;
    socket.recvall(&reloading, sizeof(uint8_t), &was_closed);
    if (was_closed) return NULL;
    return new Reloading((bool)reloading);
}
command_t ServerProtocol::receiveCommand() {
    uint8_t command;
    socket.recvall(&command, sizeof(uint8_t), &was_closed);
    command_t return_command = command_t(); 
    if (command == CREATE_ROOM_COMMAND) {
        return_command.type = CREATE_ROOM;
        return_command.room_name = receiveString();
        uint8_t game_mode;
        socket.recvall(&game_mode, sizeof(uint8_t), &was_closed);
        return_command.game_mode = intToGameMode(game_mode);
    } else if (command == JOIN_ROOM_COMMAND) {
        return_command.type = JOIN_ROOM;
        return_command.room_id = receieveUnsignedInteger();
    }
    return return_command;
}

GameMode ServerProtocol::intToGameMode(uint8_t game_mode) {
    if (game_mode == 1) return GameMode::SURVIVAL;
    return GameMode::CLEAR_THE_ZONE;
}

// --------------------------------- FUNCIONES DE ENVIAR ACCIONES ---------------------------------//

void ServerProtocol::sendGameState(std::shared_ptr<GameStateForClient> game_state) {
    std::map<uint32_t, Entity*> entities = game_state->getEntities();
    sendUnsignedInteger(entities.size());
    if (was_closed) return;
    for (auto entity : entities) {
        sendUnsignedInteger(entity.first); //id
        if (was_closed) return;

        sendString(entity.second->getState());
        if (was_closed) return;

        sendString(entity.second->getEntityType());
        if (was_closed) return;

        sendInteger(entity.second->getHitPoints());
        if (was_closed) return;

        sendInteger(entity.second->getDirectionOfMovement()->getX());
        if (was_closed) return;

        sendInteger(entity.second->getDirectionOfMovement()->getY());
        if (was_closed) return;

        uint8_t isFacingLeft = (entity.second->getDirectionOfMovement()->isFacingLeft());
        socket.sendall(&isFacingLeft, sizeof(uint8_t), &was_closed);
        if (was_closed) return;

        uint8_t isFacingUp = (entity.second->getDirectionOfMovement()->isMovingUp());
        socket.sendall(&isFacingUp, sizeof(uint8_t), &was_closed);
        if (was_closed) return;
        
        if (entity.second->getEntityType() == "player") {
            Player* player = dynamic_cast<Player*>(entity.second);
            sendString(player->getWeaponType());
            sendInteger(player->getAmmoLeft());
            uint8_t lives = player->getLives();
            socket.sendall(&lives, sizeof(uint8_t), &was_closed);
        }
        
    }
}


void ServerProtocol::sendRoomId(uint32_t room_id) {
    sendUnsignedInteger(room_id);
}

void ServerProtocol::sendJoinResponse(bool accepted) {
    uint8_t response = accepted;
    socket.sendall(&response, sizeof(uint8_t), &was_closed);
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
