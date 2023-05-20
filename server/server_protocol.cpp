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
#define CREATE_PLAYER 0x05

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
        std::cout << "position x: " << position[0] << std::endl;
        std::cout << "position y: " << position[1] << std::endl;
        std::shared_ptr<Action> movingAction = std::make_shared<Moving>(positionArray);
        return movingAction;
    }
    if (action == CREATE_PLAYER) {
        //Por que esto es shared? si se pushea a una cola sola
        //no es como en send que el game_loop le pushea a varias colas
        //no bastaria con que este en el stack? o con un std::move?
        //std::shared_ptr<Action> create_player_action = std::make_shared<CreatePlayer>(100); 
        //CreatePlayer newPlayer = CreatePlayer(100000);
        //Action *action = &newPlayer;
        //std::shared_ptr<Action> create_player_action(action);
        //return create_player_action;
    }
    return NULL;
}

void ServerProtocol::sendGameState(std::shared_ptr<GameStateForClient>& game_state) {
    std::map<uint32_t, Entity*> entities = game_state->getEntities();
    Movement *movement = entities[1]->getDirectionOfMovement();
    int32_t movement_x = movement->getX();
    int32_t movement_y = movement->getY();
    std::cout << "send_game_sate x: " << movement_x << std::endl; 
    std::cout << "send_game_sate y: " << movement_y << std::endl;
    movement_x = htonl(movement_x);
    movement_y = htonl(movement_y);
    socket.sendall(&movement_x, sizeof(int32_t), &connected);
    if (!connected) throw std::exception();
    socket.sendall(&movement_y, sizeof(int32_t), &connected);
    /*
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
    */
}

