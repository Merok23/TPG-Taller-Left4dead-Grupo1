#include <vector>
#include <array>
#include <map>
#include <utility>

#include "server_protocol.h"


#define CREATE 0x01
#define JOIN 0x02
#define ADD_PLAYER 0x03
#define MOVE 0x04

ServerProtocol::ServerProtocol(Socket socket) : socket(std::move(socket)), was_closed(false) {
    return; 
}

int32_t ServerProtocol::receiveInteger() {
    int32_t number;
    socket.recvall(&number, sizeof(int32_t), &was_closed);
    number = ntohl(number);
    return number;
}
Action* ServerProtocol::receiveAction() {
    uint8_t command;
    socket.recvall(&command, sizeof(uint8_t), &was_closed);
    if (was_closed) return NULL; 
    Action* action = NULL;
    if (command == MOVE) {
        int32_t position_x = receiveInteger();
        if (was_closed) return NULL;
        int32_t position_y = receieveUnsignedInteger();
        if (was_closed) return NULL;

        std::array<int32_t, 2> positionArray = {position_x, position_y};
        action = new Moving(positionArray); 
    } else if (command == ADD_PLAYER) {
        //Por que esto es shared? si se pushea a una cola sola
        //no es como en send que el game_loop le pushea a varias colas
        //no bastaria con que este en el stack? o con un std::move?
        //std::shared_ptr<Action> create_player_action = std::make_shared<CreatePlayer>(100); 
        /* CreatePlayer newPlayer = CreatePlayer(100000);
        Action *action = &newPlayer;
        std::shared_ptr<Action> create_player_action(action); */
        action =  new CreateSoldierIdf();
    }
    return action;
}

bool ServerProtocol::isFinished() {
    return was_closed;
}

uint32_t ServerProtocol::receieveUnsignedInteger() {
    uint32_t number;
    socket.recvall(&number, sizeof(uint32_t), &was_closed);
    number = ntohl(number);
    return number;
}

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

        if (entity.second->getEntityType() == "player") {
            Player* player = dynamic_cast<Player*>(entity.second);
            sendString(player->getWeaponType());
            sendInteger(player->getAmmoLeft());
        }
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
    }
}
std::string ServerProtocol::receiveString() {
    uint32_t len; 
    socket.recvall(&len, sizeof(uint32_t), &was_closed); 
    len = ntohl(len); 

    std::vector<char> string(len, 0x00);
    socket.recvall(string.data(), len, &was_closed);
    return std::string(string.begin(), string.end());
}

command_t ServerProtocol::receiveCommand() {
    uint8_t command;
    socket.recvall(&command, sizeof(uint8_t), &was_closed);
    command_t return_command = command_t(); 
    if (command == CREATE) {
        return_command.type = CREATE_ROOM;
        return_command.room_name = receiveRoomName();
    } else if (command == JOIN) {
        return_command.type = JOIN_ROOM;
        return_command.room_id = receiveRoomId();
    }
    return return_command;
}

std::string ServerProtocol::receiveRoomName() {
    return receiveString();
}

uint32_t ServerProtocol::receiveRoomId() {
    return receieveUnsignedInteger();
}

void ServerProtocol::sendRoomId(uint32_t room_id) {
    sendUnsignedInteger(room_id);
}

void ServerProtocol::sendJoinResponse(bool accepted) {
    uint8_t response = accepted;
    socket.sendall(&response, sizeof(uint8_t), &was_closed);
}

void ServerProtocol::closeSocket() {
    if (was_closed) return;
    socket.shutdown(SHUT_RDWR);
    socket.close();
}
