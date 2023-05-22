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
    send_thread->start();
    receive_thread->start();
    std::string line;
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

 