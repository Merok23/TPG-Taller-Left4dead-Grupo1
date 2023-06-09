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
#include "receive_thread.h"

ReceiveThread::ReceiveThread(ServerProtocol& protocol, 
            GameHandler& game_handler, Queue<std::shared_ptr<GameStateForClient>>& client_queue) : 
                protocol(protocol),  
                    game_handler(game_handler),
                        client_queue(client_queue),
                            finished(false), 
                                client_id(0), 
                                    room_id(0), 
                                        game_started(false) {}


void ReceiveThread::run() {
    receiveCommand();
    receiveGameActions();
}

void ReceiveThread::receiveCommand() {
    while (!finished && !this->game_started) {
        try {
            command_t command = protocol.receiveCommand();
            if (finished) break;
            if (protocol.isFinished() && command.type == COMMANDS_TYPE::DEFAULT) {
                std::cout << "Client was disconnected before the game started" << std::endl;
                finished = true;
                break;
            } 
            if (command.type == COMMANDS_TYPE::CREATE_ROOM) {
                room_id = game_handler.createRoom(command.room_name, client_queue, client_id, command.game_mode);
                protocol.sendRoomId(room_id);
                game_started = true;
            } else if (command.type == COMMANDS_TYPE::JOIN_ROOM) {
                GameMode game_mode;
                game_started = game_handler.joinRoom(command.room_id, client_queue, client_id, game_mode);
                protocol.sendJoinResponse(game_started);
                protocol.sendGameMode(game_mode);
                if (game_started) room_id = command.room_id;  
            }
        } catch(const LibError &e) {
            std::cerr << "Error: " << e.what() << std::endl;
            finished = true;
        }
    } 
}

void ReceiveThread::receiveGameActions() {
    if (!game_started) return;
    Queue<std::shared_ptr<Action>>& game_queue = game_handler.getQueue(room_id);
    while (!finished) {
        try {
            std::shared_ptr<Action> action = protocol.receiveAction();
            if (finished) break;
            if (protocol.isFinished()) {
                std::cout << "Client id: " << client_id << " was disconnected from room: " << room_id  << std::endl;
                stop();
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
        } catch(const LibError &e) {
            std::cerr << "Error: " << e.what() << std::endl;
            finished = true;
        }
    }
}


void ReceiveThread::stop() {
        finished = true;
        if (game_started) game_handler.leaveRoom(room_id, client_queue);
} 

bool ReceiveThread::isFinished() {
    return finished;
}
