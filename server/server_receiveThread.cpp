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

#include "server_receiveThread.h"
ReceiveThread::ReceiveThread(ServerProtocol& protocol, 
            Queue<std::shared_ptr<Action>>& queue) : 
                protocol(protocol), game_queue(queue), finished(true) {
    return; 
}


void ReceiveThread::receiveCommands() {
    while (!finished) {
        try {
            std::shared_ptr<Action> action = protocol.receiveAction();
            game_queue.push(action);  
        } catch (const std::runtime_error& e) {
            std::cerr << "ERROR: " << e.what() << std::endl;
            break;            
        } 
    }  
} 

void ReceiveThread::stop() {
        finished = true;
        /* socket.shutdown(SHUT_RDWR);
        socket.close();*/
} 