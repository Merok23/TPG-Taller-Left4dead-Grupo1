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

#define MOVING 0x02
#define GAMESTATE 0x03

ServerProtocol::ServerProtocol(Socket socket) : socket(std::move(socket)), connected(true) {
    return; 
}

std::shared_ptr<Action> ServerProtocol::receiveAction() {
    int8_t action;
    socket.recvall(&action, sizeof(int8_t), &connected);
    if (!connected) return NULL;
    if (action == MOVING) {
        int8_t position[2];
        socket.recvall(position, sizeof(int8_t) * 2, &connected);
        std::array<int8_t, 2> positionArray = {position[0], position[1]};
        std::shared_ptr<Action> movingAction = std::make_shared<Moving>(positionArray);
        return movingAction;
    }
    return NULL;
}

void ServerProtocol::sendGameState(std::shared_ptr<GameStateForClient>& game_state) {
    int8_t code = GAMESTATE;
    socket.sendall(&code, sizeof(int8_t), &connected);
    std::map<uint32_t, Entity*> entities = game_state->getEntities();
    int32_t entities_len = entities.size();
    entities_len = htonl(entities_len);
    socket.sendall(&entities_len, sizeof(int32_t), &connected);
    for (auto entity: entities) {
        int32_t id = htonl(entity.first);
        socket.sendall(&id, sizeof(int32_t), &connected);

        const std::string type = entity.second->getEntityType();
        uint16_t string_len = htons((uint16_t)type.length()); 
        socket.sendall(&string_len, sizeof(uint16_t), &connected); 
        socket.sendall((char*)type.c_str(), type.length(), &connected);

        int32_t hp = entity.second->getHitPoints();
        hp = htonl(hp);
        socket.sendall(&hp, sizeof(int32_t), &connected);
        
        int8_t position[2];
        position[0] = entity.second->getDirectionOfMovement()->getX();
        position[1] = entity.second->getDirectionOfMovement()->getY();
        socket.sendall(position, sizeof(int8_t) * 2, &connected);
    }
}

