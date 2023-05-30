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
    while (!started_playing) { 
        std::getline(std::cin, line);
        std::istringstream iss(line);
        std::string word1, word2, word3;
        iss >> word1;
        if (word1 == "create") {
            iss >> word2; 
            if (word2 == "room") {
                iss >> word3;
                command_t command = command_t(); 
                command.type = CREATE_ROOM;
                protocol.sendCommand(command);
                std::cout << "Room id created: " << protocol.receiveRoomId() << std::endl;
            }
            started_playing = true;
        } else if (word1 == "join") {
            int code;
            iss >> code;
            command_t command = command_t(); 
            command.type = JOIN_ROOM;
            command.room_id = code;
            protocol.sendCommand(command); 
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
            std::cout << "Commands are: create room (name) or join room (id)" << std::endl;
        }
    }

    send_thread->start();
    receive_thread->start();


    graphics.run(NULL);
    while (!finished) { 
        std::getline(std::cin, line);
        if (line == "leave") {
            finished = true; 
            break; 
        } 
        //POR AHORA CORTO COMUNICACION CON EL CLIENTE
        // else if (line == "create_player") {
        //     int id = 0;
        //     std::cin >> id;
        //     std::cout << "Registre el id por consola" << std::endl;
        //     std::string room_name("nueva_sala");
        //     command_t command(ADD_PLAYER, room_name, id, 770, 700);
        //     std::cout << "Estoy por llamar a sendCommand" << std::endl;
        //     protocol.sendCommand(command);
        //     std::cout << "Volvi de sendCommand" << std::endl;
        //     GameState* gs = NULL;
        //     do { 
        //     std::cout << "Estoy por llamar a receiveGameState" << std::endl;
        //         gs = protocol.receiveGameState(); 
        //     std::cout << "Volvi de receiveGameState" << std::endl;
        //     } while (!gs);
            
        //     std::cout << "Estoy por llamar a graphics.run" << std::endl;
        //     
        //     //queue_comandos.push(line);
        // }
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
