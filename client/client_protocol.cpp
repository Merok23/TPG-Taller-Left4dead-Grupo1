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

void ClientProtocol::sendInteger(int32_t number) {
    int32_t number_to_send = htonl(number);
    socket.sendall(&number_to_send, sizeof(int32_t), &was_closed);
}


void ClientProtocol::sendMoving(int x, int y) {
    uint8_t action = MOVE;  
    socket.sendall(&action, sizeof(uint8_t), &was_closed);
    if (was_closed) return; 
     
    sendInteger(x);
    sendInteger(y);
}


void ClientProtocol::sendAddPlayer() {
    uint8_t action = ADD_PLAYER;
    socket.sendall(&action, sizeof(uint8_t), &was_closed);
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
std::unique_ptr<GameState> ClientProtocol::receiveGameState() {
    std::map<uint32_t, Entity*> entities;
    uint32_t entities_len = receieveUnsignedInteger();
    if (was_closed) throw std::exception();

    while(entities_len > 0) {
        uint32_t id = receieveUnsignedInteger();
        if (was_closed) throw std::exception();

        std::string type = receiveString();
        if (was_closed) throw std::exception();

        int32_t hit_point = receiveInteger();
        if (was_closed) throw std::exception();

        int32_t position_x = receiveInteger(); 
        int32_t position_y = receiveInteger(); 
        if (was_closed) throw std::exception();


        Entity* entity  = new Entity(id, type, hit_point,  position_x, position_y);
        
        entities[id] = entity;
        entities_len--; 
    }
    std::unique_ptr<GameState> game_state(new GameState(entities));
    return game_state;
}

bool ClientProtocol::isFinished() {
    return !was_closed;
}