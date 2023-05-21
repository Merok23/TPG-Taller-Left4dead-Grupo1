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
            Queue<Action*>& queue) : 
                protocol(protocol), game_queue(queue), finished(false) {
    return; 
}


void ReceiveThread::receiveCommands() {
    while (!finished) {
        try {
            Action* action = protocol.receiveAction();
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