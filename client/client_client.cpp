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
#include <thread>

#include "client_client.h"
#define MAX_ELEMENTS 10000

Client::Client(const char* hostname, const char* servname) : 
    protocol(std::move(Socket(hostname, servname))), 
        queue_comandos(MAX_ELEMENTS), 
            game_states(MAX_ELEMENTS),
                finished(false) {
    send_thread = new SendThread(protocol, queue_comandos);
    receive_thread = new ReceiveThread(protocol, game_states);
}

void Client::run() {
    std::string line;
    while(true) { //ale ma va a matar por este while true
        std::getline(std::cin, line);
        std::istringstream iss(line);
        std::string word1, word2, word3;
        iss >> word1;
        if (word1 == "create") {
            iss >> word2; 
            if (word2 == "room") {
                iss >> word3;
                printf("Creating room %s\n", word3.c_str());
                command_t command; 
                command.type = CREATE_ROOM;
                command.room_id = 0;
                command.room_name = ""; 
                command.x_position = 0;
                command.y_position = 0;
                protocol.sendCommand(command);
                std::cout << "Room id: " << protocol.receiveRoomId() << std::endl;
            }
            break; 
        }
        else if (word1 == "join") {
            int code;
            iss >> code;
            command_t command; 
            command.type = JOIN_ROOM;
            command.room_id = code;
            command.room_name = "";
            command.x_position = 0;
            command.y_position = 0;
            protocol.sendCommand(command); 
            int response = protocol.receiveJoinResponse();
            if (response == 1) std::cout << "Joined room " << code  <<  " successfully"<< std::endl;
            if (response == 0) std::cout << "Join room " << code << " failed" << std::endl;
            break;
        } else if (word1 == "leave") {
            finished = true; 
            break;
        } else {
            std::cout << "Commands are: create room (name) or join room (id)" << std::endl;
        }
    }
    if (!finished) {
        send_thread->start();
        receive_thread->start();
    }

    while (!finished) { 
        std::getline(std::cin, line);
        if (line == "leave") {
            finished = true; 
            break; 
        } else  {
            queue_comandos.push(line);
        }  
    }
}
 
Client::~Client() {
    protocol.closeSocket();
    while (true) { //Abril liberaria la memoria
        GameState* state = NULL; 
        if (game_states.try_pop(state)) {
            delete state; 
        } else {
            break; 
        }
    }
    queue_comandos.close();
    game_states.close();
    send_thread->stop();
    receive_thread->stop();
    send_thread->join();
    receive_thread->join();
    delete send_thread;
    delete receive_thread;    
}

 