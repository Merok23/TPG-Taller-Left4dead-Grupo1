#include <utility>

#include "receive_thread.h"

ReceiveThread::ReceiveThread(ClientProtocol& protocol, 
    Queue<std::shared_ptr<GameState>>& queue) : 
    protocol(protocol), game_states(queue), finished(false) {}  

void ReceiveThread::run() {
    while (!finished) {
        try {
            std::shared_ptr<GameState> game_state = protocol.receiveGameState();
            if (!game_state && !finished) {
                std::cout << "ERROR: Server was disconnected" << std::endl; //Como se lo paso a abril??????? 
                std::shared_ptr<GameState> game_state = std::make_shared<GameState>();
                game_state->setLostConnection();
                game_states.push(std::move(game_state)); 
                finished = true;
                break;
            }   
            if (game_state && game_state->game_over) {
                std::cout << "GAME OVER" << std::endl;
                std::cout << game_state->infected_killed << " infected killed" << std::endl;
                std::cout << game_state->ammo_used << " ammo used" << std::endl;
                std::cout << game_state->game_loop_time << " game loop time" << std::endl;
            }
            if (game_state) {
                //game_state->print();
                game_states.push(std::move(game_state)); 
            }
        } catch(const LibError &e) {
            std::cerr << "Error: " << e.what() << std::endl;
            finished = true;
        } catch(const ClosedQueue &e) {
            if (finished) return; 
            std::cerr << "Error: " << e.what() << std::endl;
            finished = true;
        } 
    }
}

void ReceiveThread::stop() {
    finished = true;
}
