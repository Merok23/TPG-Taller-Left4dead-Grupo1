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

void ClientProtocol::send_int32_number(int32_t number) {
    int32_t number_to_send = htonl(number);
    socket.sendall(&number_to_send, sizeof(int32_t), &was_closed);
}


void ClientProtocol::sendMoving(int x, int y) {
    uint8_t action = MOVE;  
    socket.sendall(&action, sizeof(uint8_t), &was_closed);
    if (was_closed) return; 
     
    send_int32_number(x);
    send_int32_number(y);
}


void ClientProtocol::sendAddPlayer() {
    uint8_t action = ADD_PLAYER;
    socket.sendall(&action, sizeof(uint8_t), &was_closed);
}

uint32_t ClientProtocol::receieve_uint32_number() {
    uint32_t number;
    socket.recvall(&number, sizeof(uint32_t), &was_closed);
    number = ntohl(number);
    return number;
}

std::string ClientProtocol::receiveString() {
    uint32_t len; 
    socket.recvall(&len, sizeof(uint32_t), &was_closed); 
    len = ntohl(len); 

    std::vector<char> string(len, 0x00);
    socket.recvall(string.data(), len, &was_closed);
    return std::string(string.begin(), string.end());
}

int32_t ClientProtocol::receive_int32_number() {
    int32_t  number;
    socket.recvall(&number, sizeof(uint32_t), &was_closed);
    number = ntohl(number);
    return number;
}
void ClientProtocol::receiveGameState() {
    std::map<uint32_t, Entity*> entities;
    uint32_t entities_len = receieve_uint32_number();
    if (was_closed) return;
    while(entities_len > 0) {
        uint32_t id = receieve_uint32_number();
        std::cout << "Entity id: " << id << std::endl; 

        std::string type = receiveString();
        std::cout << "Entity type: " << type << std::endl;

        int32_t hit_point = receive_int32_number();
        std::cout << "Entity hp: " << hit_point << std::endl; 


        int32_t position_x = receive_int32_number(); 
        int32_t position_y = receive_int32_number(); 

        std::cout << "Entity x: " << position_x << " y: " << position_y << std::endl; 

        Entity* entity = nullptr;
        if (type == "player" ) {
            entity = new Player(id, position_x, position_y, hit_point);
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