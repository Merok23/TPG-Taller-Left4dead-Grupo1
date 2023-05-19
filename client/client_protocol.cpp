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

ClientProtocol::ClientProtocol(Socket socket) : socket(std::move(socket)), connected(true) {
    return; 
}   

void ClientProtocol::sendMoving(int x, int y) {
    int8_t action = MOVE;
    int8_t position_x = x; 
    int8_t position_y = y;
    socket.sendall(&action, sizeof(int8_t), &connected);
    if (!connected) return; 
    socket.sendall(&position_x, sizeof(int8_t), &connected); 
    socket.sendall(&position_y, sizeof(int8_t), &connected);
}

std::unique_ptr<GameState> ClientProtocol::receiveGameState() {
    int32_t entities_len;
    socket.recvall(&entities_len, sizeof(int32_t), &connected);
    entities_len = ntohl(entities_len);

    std::map<uint32_t, Entity*> entities;
    for (int i = 0; i < entities_len; i++) {
        int32_t id;
        socket.recvall(&id, sizeof(int32_t), &connected);
        id = ntohl(id);
       
        uint16_t type_len; 
        socket.recvall(&type_len, sizeof(uint16_t), &connected); 
        type_len = ntohs(type_len); 

        char type[MAX_TYPE_LENGHT]; 
        socket.recvall(&type, type_len, &connected); 
        type[type_len] = '\0'; 
    
        int32_t hp;
        socket.recvall(&hp, sizeof(int32_t), &connected);
        hp = ntohl(hp);
        
        int8_t position[2];
        socket.recvall(position, sizeof(int8_t) * 2, &connected);
        
        Entity* entity = nullptr;
        if (strcmp(type, "Player") == 0) {
            entity = new Player(id, position[0], position[1], hp);
        }
        entities.at(id) = entity;
    }
    std::unique_ptr<GameState> game_state(new GameState(entities));
    return game_state;
}