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

void Client::run() {
    std::string line;
    bool started_playing = false;
    COMMANDS command;
    while (!started_playing) { 
        std::getline(std::cin, line);
        std::istringstream iss(line);
        std::string word1, word2, word3, word4;
        iss >> word1;
        if (word1 == "create") {
            iss >> word2; 
            if (word2 == "room") {
                iss >> word3 >> word4;
                // if (word4 != "Survival") {
                //     std::cout << "No se ingreso el survival para el modo de juego. Empeza de nuevo" << std::endl;
                //     continue;
                // }
                    
                protocol.sendCommand(command.createRoom(word3, word4));
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

    while (!finished) { 
        std::getline(std::cin, line);
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
            queue_comandos.push(command.addPlayer(word2));
            GameState* gs = NULL;
            bool leave = false;
            while (!leave) {
                game_states.try_pop(gs);
                if (gs) {
                    if (!gs->entities.empty()) {
                        leave = true;
                    }
                }
            }
            graphics.run(gs, queue_comandos, game_states);
        } else {
            std::cout << "Commands are: create (weapon)" << std::endl;
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
