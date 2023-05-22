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
#include "server_receive_thread.h"

ReceiveThread::ReceiveThread(ServerProtocol& protocol, 
            Queue<Action*>& queue, int client_id) : 
                protocol(protocol), game_queue(queue), 
                    finished(false), 
                        client_id(client_id) {
    return; 
}


void ReceiveThread::receiveCommands() {
    while (!finished) {
        try {
            Action* action = protocol.receiveAction();
            if (action) action->setClientId(client_id); 
            if(protocol.isFinished()) {
                finished = true;
                break;
            }   
            if (action) game_queue.push(action);  
        } catch (const std::runtime_error& e) {
            std::cerr << "ERROR: " << e.what() << std::endl;
            break;            
        } 
    }  
} 

void ReceiveThread::stop() {
        finished = true;
        protocol.closeSocket();
} 

bool ReceiveThread::isFinished() {
    return finished;
}