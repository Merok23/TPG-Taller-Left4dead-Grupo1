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
                match_started(false) {
    send_thread = new SendThread(protocol, queue_comandos);
    receive_thread = new ReceiveThread(protocol, game_states);
}


void Client::run() {
    std::string line;

    COMMANDS commands;
    command_t create_or_join_command;
    command_t player_command;
    
    create_or_join_command = commands.cheatInfiniteHitpoints();
    player_command = commands.cheatInfiniteHitpoints();

    bool join_failed = true;
    while (join_failed) {
        join_failed = false;
        this->graphics_qt.run(&commands, &create_or_join_command, &player_command);
        if ((create_or_join_command.type != CREATE_ROOM && create_or_join_command.type != JOIN_ROOM) || 
            player_command.type != ADD_PLAYER) {
                std::cout << "The client doesnt want to start the game. Exiting..." << std::endl;
            return;
        }
    
        protocol.sendCommand(create_or_join_command);
        if (create_or_join_command.type == CREATE_ROOM)
            std::cout << "Room id created: " << protocol.receiveRoomId() << std::endl;
        else {
            int response = protocol.receiveJoinResponse();
            if (response == 1) {
                std::cout << "Joined room successfully"<< std::endl;
            }    
            if (response == 0) {
                std::cout << "Join room failed. Try again." << std::endl;
                create_or_join_command = commands.cheatInfiniteHitpoints();
                player_command = commands.cheatInfiniteHitpoints();
                join_failed = true;
            }
        } 
    }
    
    match_started = true;
    
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
    if (gs) 
        graphics.run(gs, queue_comandos, game_states);
    receive_thread->stop();
    send_thread->stop();
}
 
Client::~Client() {
    protocol.closeSocket();
    queue_comandos.close();
    game_states.close();
    send_thread->stop();
    receive_thread->stop();
    if (match_started) {
        send_thread->join();
        receive_thread->join();
        delete send_thread;
        delete receive_thread;   
    } 
}
