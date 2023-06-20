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
                std::pair<uint8_t, uint32_t> infected_killed = game_state->getInfectedKilled();
                std::cout << infected_killed.second << " infected killed" << std::endl;
                std::cout << "Ranking: " << (int) infected_killed.first << std::endl;
                std::pair<uint8_t, uint32_t> ammo_used = game_state->getAmmoUsed();
                std::cout << ammo_used.second << " ammo used" << std::endl;
                std::cout << "Ranking: " << (int) ammo_used.first << std::endl;
                std::pair<uint8_t, uint32_t> game_time = game_state->getGameLoopTime();
                std::cout << game_time.second << " game loop time" << std::endl;
                std::cout << "Ranking: " << (int) game_time.first << std::endl;
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
