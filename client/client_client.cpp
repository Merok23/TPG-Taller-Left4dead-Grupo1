#include <string>
#include <sstream>
#include <iostream>
#include <utility>

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


//  std::string line;
//     COMMANDS commands;
//     command_t create_or_join_command;
//     command_t player_command;

//     //los inicializo con otro comando, para no leer basura
//     create_or_join_command = commands.cheatKillAllInfected();
//     player_command = commands.cheatKillAllInfected();

//     this->graphics_qt.run(&commands, &create_or_join_command, &player_command);

//     if ((create_or_join_command.type == CREATE_ROOM || create_or_join_command.type == JOIN_ROOM) && 
//         player_command.type == ADD_PLAYER) {
//         protocol.sendCommand(create_or_join_command);
//         std::cout << "Room id created: " << protocol.receiveRoomId() << std::endl;

//         send_thread->start();
//         receive_thread->start();

//         queue_comandos.push(player_command);
//         std::shared_ptr<GameState> gs = NULL;
//         bool leave = false;
//         while (!leave && !protocol.isFinished()) {
//             game_states.try_pop(gs);
//             if (gs) {
//                 if (!gs->entities.empty()) {
//                     leave = true;
//                 }
//             }
//         }
//         if (gs) 
//             graphics.run(gs, queue_comandos, game_states);
//     }

void Client::run() {
    std::string line;
    bool started_playing = false;
    COMMANDS command; //no se usa, ds hay que borrarlo
    COMMANDS commands;
    command_t create_or_join_command;
    command_t player_command;
    
    create_or_join_command = commands.cheatInfiniteHitpoints();
    player_command = commands.cheatInfiniteHitpoints();

    this->graphics_qt.run(&commands, &create_or_join_command, &player_command);


    if ((create_or_join_command.type != CREATE_ROOM && create_or_join_command.type != JOIN_ROOM) || 
        player_command.type != ADD_PLAYER) {
        finished = true;
        return;
    }
    
    protocol.sendCommand(create_or_join_command);
    std::cout << "Room id created: " << protocol.receiveRoomId() << std::endl;
    started_playing = true;

    while (!started_playing) { 
        std::getline(std::cin, line);
        std::istringstream iss(line);
        std::string word1, word2, word3, word4;
        iss >> word1;
        if (word1 == "create") {
            iss >> word2; 
            if (word2 == "room") {
                iss >> word3;
                iss >> word4;
                if (word4 == "survival")
                    protocol.sendCommand(command.createRoom(word3, GameMode::SURVIVAL));
                else
                    protocol.sendCommand(command.createRoom(word3, GameMode::TESTING));
                std::cout << "Room id created: " << protocol.receiveRoomId() << std::endl;
            }
            started_playing = true;
        } else if (word1 == "join") {
            int code;
            iss >> code;
            protocol.sendCommand(command.joinRoom(code)); 
            int response = protocol.receiveJoinResponse();
            if (response == 1) {
                std::cout << "Joined room " << code  <<  " successfully"<< std::endl;
                started_playing = true;
            }    
            if (response == 0) std::cout << "Join room " << code << " failed" << std::endl;
        } else if (word1 == "leave") {
            finished = true; 
            started_playing = true;
            break;
        } else {
            std::cout << "Commands are: create room (name) survival or join room (id)" << std::endl;
        }
    }

    send_thread->start();
    receive_thread->start();

    queue_comandos.push(player_command);
    std::shared_ptr<GameState> gs = NULL;
    bool leave = false;
    while (!leave && !protocol.isFinished()) {
        game_states.try_pop(gs);
        if (gs) {
            if (!gs->entities.empty()) {
                leave = true;
            }
        }
    }
    if (gs) graphics.run(gs, queue_comandos, game_states);

    finished = true;


    while (!finished) { 
        std::getline(std::cin, line);
        if (protocol.isFinished()) break;
        std::istringstream iss(line);
        std::string word1, word2; 
        iss >> word1;
        if (word1 == "leave") {
            finished = true; 
            break; 
        } 
        else if (word1 == "create") {
            iss >> word2;
            if (word2 != "idf" && word2 != "p90" && word2 != "scout") {
                std::cout << "Invalid weapon" << std::endl;
                continue;
            }
            
        } else {
            std::cout << "Commands are: create (weapon)" << std::endl;
        }
    }
}
 
Client::~Client() {
    protocol.closeSocket();
    queue_comandos.close();
    game_states.close();
    send_thread->stop();
    receive_thread->stop();
    send_thread->join();
    receive_thread->join();
    delete send_thread;
    delete receive_thread;    
}
