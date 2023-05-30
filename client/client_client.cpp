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
//DONDE VA ESTE CODIGO

    // //necesito hablar con el server para que me pase la data del player
    // std::string room_name("nueva_sala");
    // command_t command(ADD_PLAYER, room_name, 0, 370, 700);
    // std::cout << "A punto de enviar el comando " << std::endl;
    // protocol.sendCommand(command);
    // //a ese entity que se recibe se lo mando a graphics
    // GameState* gs = NULL;
    // do {
    //     gs = protocol.receiveGameState();
    // } while (!gs);
     
    // graphics.run(gs);


    
    std::string line;
    while (connected) {
        std::getline(std::cin, line);
        std::istringstream iss(line);
        std::string action; 
        iss >> action;
        if (action == "leave") {
            break; 
        }
        if (action == "move") {
            int x;
            int y;
            iss >> x; 
            iss >> y; 
            this->protocol.sendMoving(x, y);
            continue; 
        } else { 
            std::cout << "Invalid command" << std::endl; 
        } 
    }

    send_thread->start();
    receive_thread->start();

    while (!finished) { 
        std::getline(std::cin, line);
        if (line == "leave") {
            finished = true; 
            break; 
        } else  {
            queue_comandos.push(line);
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
