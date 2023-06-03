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

#include <map>
#include <utility>

#include "client_protocol.h"
#define MAX_TYPE_LENGHT 200

#define CREATE 0x01
#define JOIN 0x02
#define ADD 0x03
#define MOVE 0x04

ClientProtocol::ClientProtocol(Socket socket) : socket(std::move(socket)), was_closed(false) {
    return; 
}   

void ClientProtocol::sendInteger(int32_t number) {
    int32_t number_to_send = htonl(number);
    socket.sendall(&number_to_send, sizeof(int32_t), &was_closed);
}
void ClientProtocol::sendString(const std::string& string) {
    uint32_t len = string.length();
    len = htonl(len);
    socket.sendall(&len, sizeof(uint32_t), &was_closed);
    socket.sendall((char*)string.c_str(), string.length(), &was_closed);
}

void ClientProtocol::sendUnsignedInteger(uint32_t number) {
    uint32_t number_to_send = htonl(number);
    socket.sendall(&number_to_send, sizeof(uint32_t), &was_closed);
}

void ClientProtocol::sendJoinRoom(int room_id) {
    uint8_t action = JOIN;
    socket.sendall(&action, sizeof(uint8_t), &was_closed);
    if (was_closed) return; 

    sendUnsignedInteger(room_id);
    if (was_closed) return;
}
void ClientProtocol::sendCreateRoom(const std::string& room_name) {
    uint8_t action = CREATE;
    socket.sendall(&action, sizeof(uint8_t), &was_closed);
    if (was_closed) return; 

    sendString(room_name);
}
void ClientProtocol::sendCommand(command_t command) {
    if (command.type == COMMANDS_TYPE::CREATE_ROOM) 
        sendCreateRoom(command.room_name); 
    else if (command.type == COMMANDS_TYPE::JOIN_ROOM) 
        sendJoinRoom(command.room_id);
    else if (command.type == COMMANDS_TYPE::ADD_PLAYER) 
        sendAddPlayer(command.weapon);
    else if (command.type == COMMANDS_TYPE::MOVE_PLAYER) 
        sendMoving(command.x_position, command.y_position);
}
void ClientProtocol::sendMoving(int x, int y) {
    uint8_t action = MOVE;  
    socket.sendall(&action, sizeof(uint8_t), &was_closed);
    if (was_closed) return; 
     
    sendInteger(x);
    sendInteger(y);
}

uint32_t ClientProtocol::receiveRoomId() {
    uint32_t room_id = receieveUnsignedInteger();
    return room_id;
}

bool ClientProtocol::receiveJoinResponse() {
    uint8_t response;
    socket.recvall(&response, sizeof(uint8_t), &was_closed);
    if (was_closed) return false; 
    return (bool)response;
}

void ClientProtocol::sendAddPlayer(const std::string& weapon) {
    uint8_t action = ADD;
    socket.sendall(&action, sizeof(uint8_t), &was_closed);
    if (was_closed) return; 

    sendString(weapon);
    if (was_closed) return;
}

uint32_t ClientProtocol::receieveUnsignedInteger() {
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

int32_t ClientProtocol::receiveInteger() {
    int32_t  number;
    socket.recvall(&number, sizeof(uint32_t), &was_closed);
    number = ntohl(number);
    return number;
}

uint8_t ClientProtocol::receiveUnsignedSmallInteger() {
    uint8_t command;
    socket.recvall(&command, sizeof(uint8_t), &was_closed);
    return command;
}

State ClientProtocol::stringToState(const std::string& state) {
    if (state == "moving") {
        return RUN;
    } else if (state == "shooting") {
        return SHOOT;
    } else if (state == "reloading") {
        return RELOAD;
    } else if (state == "dead") {
        return DIE;
    }
    return IDLE;
}
GameState* ClientProtocol::receiveGameState() {
    std::map<uint32_t, Entity*> entities;
    uint32_t entities_len = receieveUnsignedInteger();
    if (was_closed) return NULL; 

    while (entities_len > 0) {
        uint32_t id = receieveUnsignedInteger();
        if (was_closed) return NULL;

        std::string state = receiveString();
        if (was_closed) return NULL;
        State state_enum = stringToState(state);

        std::string type = receiveString();
        if (was_closed) return NULL;

        std::string weapon_type = "none";
        int32_t ammo_left = -1; 

        if (type == "player") {
            weapon_type = receiveString();
            if (was_closed) return NULL;

            ammo_left = receiveInteger();
            if (was_closed) return NULL;
        }

        int32_t hit_point = receiveInteger();
        if (was_closed) return NULL;

        int32_t position_x = receiveInteger(); 
        int32_t position_y = receiveInteger(); 
        if (was_closed) return NULL; 

        bool is_facing_left = (bool)receiveUnsignedSmallInteger();
        if (was_closed) return NULL;

        bool is_moving_up = (bool)receiveUnsignedSmallInteger();

        Entity* entity  = new Entity(id, type, state_enum, weapon_type, ammo_left, hit_point,  
            position_x, position_y, is_facing_left, is_moving_up);
        
        entities[id] = entity;
        entities_len--; 
    }
    return (new GameState(entities));
}
bool ClientProtocol::isFinished() {
    return was_closed;
}

void ClientProtocol::closeSocket() {
    if (was_closed) return;
    socket.shutdown(SHUT_RDWR);
    socket.close();
}