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

void ClientProtocol::receiveGameState() {
    int32_t entities_len;
    socket.recvall(&entities_len, sizeof(int32_t), &was_closed);
    entities_len = ntohl(entities_len);
    std::cout << "Entities size " << entities_len << std::endl; 
    std::map<uint32_t, Entity*> entities;
    while(entities_len > 0) {
        uint32_t id;
        socket.recvall(&id, sizeof(uint32_t), &was_closed);
        id = ntohl(id);
        std::cout << "Entity id: " << id << std::endl; 

        uint32_t type_len; 
        socket.recvall(&type_len, sizeof(uint32_t), &was_closed); 
        type_len = ntohl(type_len); 

        char type[MAX_TYPE_LENGHT]; 
        socket.recvall(&type, type_len, &was_closed); 
        type[type_len] = '\0'; 
        std::cout << "Entity type: " << type << std::endl;
        
        int32_t hp;
        socket.recvall(&hp, sizeof(int32_t), &was_closed);
        hp = ntohl(hp);
        std::cout << "Entity hp: " << hp << std::endl; 

        int32_t position_x;
        int32_t position_y;
        socket.recvall(&position_x, sizeof(int32_t), &was_closed);
        socket.recvall(&position_y, sizeof(int32_t), &was_closed);
        position_x = ntohl(position_x); 
        position_y = ntohl(position_y); 
        std::cout << "Entity x: " << position_x << " y: " << position_y << std::endl; 

        Entity* entity = nullptr;
        if (strcmp(type, "player") == 0) {
            entity = new Player(id, position_x, position_y, hp);
        }
        entities[id] = entity;
        entities_len--; 
    }
    //std::unique_ptr<GameState> game_state(new GameState(entities));
    //return game_state;
}

/* std::string ClientProtocol::recievePlayerMovement() {
    int32_t len = 0;
    socket.recvall(&len, sizeof(int32_t), &was_closed);
    len = ntohl(len);
    std::string big_movement = "";
    while (len > 0) {
        uint32_t id;
        socket.recvall(&id, sizeof(uint32_t), &was_closed);
        id = ntohl(id);


        uint32_t position_x;
        uint32_t position_y;
        socket.recvall(&position_x, sizeof(uint32_t), &was_closed);
        socket.recvall(&position_y, sizeof(uint32_t), &was_closed);
        position_x = ntohl(position_x);
        position_y = ntohl(position_y);
        std::string player = "Entity: ";
        player += std::to_string(len);
        player += "\n";
        std::string movement = std::to_string(position_x) + " " + std::to_string(position_y) + "\n";
        big_movement += player;
        big_movement += movement;
        len--;
    }
    return big_movement;   
} */
 /*
    *len_entities
    *Entity_id
    *Entity_type //strlen -> string
    *Entity_hitpoints
    *Entity_position_x 
    *Entity_position_y
    */

bool ClientProtocol::isFinished() {
    return !was_closed;
}