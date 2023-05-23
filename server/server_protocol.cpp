#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <sstream>
#include <sys/types.h>
#include <netinet/in.h>
#include <iostream>
#include <fstream>
#include <array>
#include "server_protocol.h"


#define MOVE 0x02
#define GAMESTATE 0x03
#define CREATE_PLAYER 0x05

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
    } else if (command == CREATE_PLAYER) {
        //Por que esto es shared? si se pushea a una cola sola
        //no es como en send que el game_loop le pushea a varias colas
        //no bastaria con que este en el stack? o con un std::move?
        //std::shared_ptr<Action> create_player_action = std::make_shared<CreatePlayer>(100); 
        /* CreatePlayer newPlayer = CreatePlayer(100000);
        Action *action = &newPlayer;
        std::shared_ptr<Action> create_player_action(action); */
        action =  new CreatePlayer();
        
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

        sendString(entity.second->getEntityType());
        if (was_closed) return;

        sendInteger(entity.second->getHitPoints());
        if (was_closed) return;

        sendInteger(entity.second->getDirectionOfMovement()->getX());
        if (was_closed) return;

        sendInteger(entity.second->getDirectionOfMovement()->getY());
        if (was_closed) return;
    }
}


void ServerProtocol::closeSocket() {
    if (was_closed) return;
    socket.shutdown(SHUT_RDWR);
    socket.close();
}