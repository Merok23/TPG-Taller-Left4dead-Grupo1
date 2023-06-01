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
                            finished(false), 
                                client_id(0), 
                                    room_id(0), 
                                        start_playing(false) {}


void ReceiveThread::run() {
    receiveCommand();
    receiveGameActions();
}

void ReceiveThread::receiveCommand() {
    while (!finished && !this->start_playing) {
        command_t command = protocol.receiveCommand();
        if (protocol.isFinished() || command.type == COMMANDS_TYPE::DEFAULT) {
            finished = true;
            break;
        }
        if (command.type == COMMANDS_TYPE::CREATE_ROOM) {
            room_id = game_handler.createRoom(command.room_name, client_queue, client_id);
            protocol.sendRoomId(room_id);
            start_playing = true;
        } else if (command.type == COMMANDS_TYPE::JOIN_ROOM) {
            start_playing = game_handler.joinRoom(command.room_id, client_queue, client_id);
            protocol.sendJoinResponse(start_playing);
            if (start_playing) room_id = command.room_id;  
        }
    } 
}

void ReceiveThread::receiveGameActions() {
    if (!start_playing) return;
    Queue<Action*>& game_queue = game_handler.getQueue(room_id);
    while (!finished) {
        try {
            Action* action = protocol.receiveAction();
            if (protocol.isFinished()) {
                finished = true;
                break;
            } 
            if (action) {
                action->setClientId(client_id);  
                game_queue.push(action);  
            }
        } catch(const ClosedQueue &e) {
            if (finished) return; 
            std::cerr << "Error: " << e.what() << std::endl;
            finished = true;
        } 
    }
}


void ReceiveThread::stop() {
        finished = true;
        if (start_playing) game_handler.leaveRoom(room_id, client_queue);
} 

bool ReceiveThread::isFinished() {
    return finished;
}
