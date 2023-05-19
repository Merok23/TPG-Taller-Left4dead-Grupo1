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
#include "server_client.h"  

#define MAX_ELEMENTS_QUEUE 10000
ServerClient::ServerClient(Socket socket, Queue<std::shared_ptr<Action>>& game_queue) : 
    protocol(std::move(socket)), 
        client_queue(MAX_ELEMENTS_QUEUE),
            receive_thread(protocol, game_queue), 
                send_thread(protocol, client_queue) {
    receive_thread.start();
    send_thread.start();
}

ServerClient::~ServerClient() {
    receive_thread.stop();
    send_thread.stop();
    receive_thread.join();
    send_thread.join();
}

bool ServerClient::isFinished() {
    return receive_thread.isFinished() || send_thread.isFinished();
}