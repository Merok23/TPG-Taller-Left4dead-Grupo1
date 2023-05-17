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
#include "../common/server_protocol.h"

#define MOVING 0x02

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
