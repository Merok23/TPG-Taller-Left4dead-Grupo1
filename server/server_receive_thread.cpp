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
            GameHandler& game_handler, Queue<std::shared_ptr<GameStateForClient>>& client_queue) : 
                protocol(protocol),  
                    game_handler(game_handler),
                        client_queue(client_queue),
                            finished(false) {
    return; 
}


void ReceiveThread::receiveCommands() {
    std::string command = protocol.receiveCommand(); 
        uint32_t client_id = 0;
        uint32_t room_id = 0;
    if (command == "create room") {
        std::string room_name = protocol.receiveRoomName();
        room_id = game_handler.createRoom(room_name, client_queue, client_id);
        protocol.sendRoomId(room_id);
    } else if (command == "join") {
        room_id = protocol.receiveRoomId();
        bool ok = game_handler.joinRoom(room_id, client_queue, client_id);
        protocol.sendJoinResponse(ok);  
    } 
    Queue<Action*>& game_queue = game_handler.getQueue(room_id);
    while (!finished) {
        try {
            Action* action = protocol.receiveAction();
            if (action) action->setClientId(client_id); 
            if(protocol.isFinished()) {
                finished = true;
                break;
            } 
            if (action) game_queue.push(action);  
        } catch(std::runtime_error& e) {
            std::string message = e.what();
            if (message == "The queue is closed") {
                finished = true;
            } 
        }
    }  
} 

void ReceiveThread::stop() {
        finished = true;
} 

bool ReceiveThread::isFinished() {
    return finished;
}