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
#include "../common/client_protocol.h"
#include "../common/socket.h"
#define MOVE 0x02

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