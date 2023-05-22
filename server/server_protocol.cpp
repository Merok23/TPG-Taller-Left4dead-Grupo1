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

Action* ServerProtocol::receiveAction() {
    uint8_t command;
    socket.recvall(&command, sizeof(uint8_t), &was_closed);
    if (was_closed) {
        return NULL; 
    }
    Action* action = NULL;
    if (command == MOVE) {
        uint32_t position_x;
        uint32_t position_y;
        socket.recvall(&position_x, sizeof(uint32_t), &was_closed);
        socket.recvall(&position_y, sizeof(uint32_t), &was_closed);
        position_x = ntohl(position_x);
        position_y = ntohl(position_y);
        std::array<uint32_t, 2> positionArray = {position_x, position_y};
        Moving* moving_action = new Moving(positionArray); 
        action = moving_action;
        return action;
    }
    if (command == CREATE_PLAYER) {
        //Por que esto es shared? si se pushea a una cola sola
        //no es como en send que el game_loop le pushea a varias colas
        //no bastaria con que este en el stack? o con un std::move?
        //std::shared_ptr<Action> create_player_action = std::make_shared<CreatePlayer>(100); 
        /* CreatePlayer newPlayer = CreatePlayer(100000);
        Action *action = &newPlayer;
        std::shared_ptr<Action> create_player_action(action); */
        CreatePlayer* create_player_action =  new CreatePlayer();
        action = create_player_action;
        return action;
        
    }
    return NULL;
}

bool ServerProtocol::isFinished() {
    return was_closed;
}

void ServerProtocol::sendGameState(std::shared_ptr<GameStateForClient> game_state) {
    std::map<uint32_t, Entity*> entities = game_state->getEntities();
    int32_t entities_len = entities.size();
    entities_len = htonl(entities_len);
    socket.sendall(&entities_len, sizeof(int32_t), &was_closed);
    for (auto entity : entities) {
        uint32_t entity_id = entity.first;
        entity_id = htonl(entity_id);
        socket.sendall(&entity_id, sizeof(uint32_t), &was_closed);
        if (was_closed) throw std::exception();
        std::string entity_type = entity.second->getEntityType();
        uint32_t entity_type_len = entity_type.length();
        entity_type_len = htonl(entity_type_len);
        socket.sendall(&entity_type_len, sizeof(uint32_t), &was_closed);
        if (was_closed) throw std::exception();
        socket.sendall(entity_type.c_str(), entity_type.length(), &was_closed);
        if (was_closed) throw std::exception();
        int32_t hit_points = entity.second->getHitPoints();
        hit_points = htonl(hit_points);
        socket.sendall(&hit_points, sizeof(int32_t), &was_closed);
        if (was_closed) throw std::exception();
        Movement *movement = entity.second->getDirectionOfMovement();
        int32_t movement_x = movement->getX();
        int32_t movement_y = movement->getY();
        movement_x = htonl(movement_x);
        movement_y = htonl(movement_y);
        socket.sendall(&movement_x, sizeof(int32_t), &was_closed);
        if (was_closed) throw std::exception();
        socket.sendall(&movement_y, sizeof(int32_t), &was_closed);
        if (was_closed) throw std::exception();
    }
}

/*
void ServerProtocol::sendGameState(std::shared_ptr<GameStateForClient> game_state) {
    std::map<uint32_t, Entity*> entities = game_state->getEntities();
    int32_t entities_len = entities.size();
    entities_len = htonl(entities_len);
    socket.sendall(&entities_len, sizeof(int32_t), &was_closed);
    for (auto entity : entities) {
        Movement *movement = entity.second->getDirectionOfMovement();
        uint32_t movement_x = movement->getX();
        uint32_t movement_y = movement->getY();
        movement_x = htonl(movement_x);
        movement_y = htonl(movement_y);
        socket.sendall(&movement_x, sizeof(uint32_t), &was_closed);
        if (was_closed) throw std::exception();
        socket.sendall(&movement_y, sizeof(uint32_t), &was_closed);
    }*/
    /*
    *len_entities
    *Entity_id
    *Entity_type //strlen -> string
    *Entity_hitpoints
    *Entity_position_x 
    *Entity_position_y
    */
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


void ServerProtocol::closeSocket() {
    if (was_closed) return;
    socket.shutdown(2);
    socket.close();
}