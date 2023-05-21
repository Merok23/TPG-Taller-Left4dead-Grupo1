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

#include "client_protocol.h"
#define MOVE 0x02
#define MAX_TYPE_LENGHT 200
#define ADD_PLAYER 0x05

ClientProtocol::ClientProtocol(Socket socket) : socket(std::move(socket)), was_closed(false) {
    return; 
}   

void ClientProtocol::sendMoving(int x, int y) {
    uint8_t action = MOVE;  
    socket.sendall(&action, sizeof(uint8_t), &was_closed);
    if (was_closed) return; 
     
    uint32_t position_x =  htonl((uint32_t)x);
    uint32_t position_y = htonl((uint32_t)y);   
    
    socket.sendall(&position_x, sizeof(uint32_t), &was_closed); 
    socket.sendall(&position_y, sizeof(uint32_t), &was_closed);
}


void ClientProtocol::sendAddPlayer() {
    uint8_t action = ADD_PLAYER;
    socket.sendall(&action, sizeof(uint8_t), &was_closed);
}

std::unique_ptr<GameState> ClientProtocol::receiveGameState() {
    uint32_t entities_len;
    socket.recvall(&entities_len, sizeof(uint32_t), &was_closed);
    entities_len = ntohl(entities_len);

    std::map<uint32_t, Entity*> entities;
    for (uint32_t i = 0; i < entities_len; i++) {
        int32_t id;
        socket.recvall(&id, sizeof(uint32_t), &was_closed);
        id = ntohl(id);
       
        uint16_t type_len; 
        socket.recvall(&type_len, sizeof(uint16_t), &was_closed); 
        type_len = ntohs(type_len); 

        char type[MAX_TYPE_LENGHT]; 
        socket.recvall(&type, type_len, &was_closed); 
        type[type_len - 1] = '\0'; 
    
        int32_t hp;
        socket.recvall(&hp, sizeof(uint32_t), &was_closed);
        hp = ntohl(hp);
        
        int32_t position[2];
        socket.recvall(position, sizeof(uint32_t) * 2, &was_closed);
        
        Entity* entity = nullptr;
        if (strcmp(type, "Player") == 0) {
            entity = new Player(id, position[0], position[1], hp);
        }
        entities.at(id) = entity;
    }
    std::unique_ptr<GameState> game_state(new GameState(entities));
    return game_state;
}

std::string ClientProtocol::recievePlayerMovement() {
    uint32_t position_x;
    uint32_t position_y;
    socket.recvall(&position_x, sizeof(uint32_t), &was_closed);
    socket.recvall(&position_y, sizeof(uint32_t), &was_closed);
    position_x = ntohl(position_x);
    position_y = ntohl(position_y);
    std::string movement = std::to_string(position_x) + " " + std::to_string(position_y);
    return movement;   
}

bool ClientProtocol::isFinished() {
    return !was_closed;
}