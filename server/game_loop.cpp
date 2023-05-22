#include "game_loop.h"
#include <chrono>
#include "config.h"

#define MAX_ELEMENTS_QUEUE 1000
GameLoop::GameLoop() : 
    game_queue(MAX_ELEMENTS_QUEUE), 
    game(CONFIG.scenario_width, CONFIG.scenario_height), 
    id_handler(game), 
    finished(false), 
    client_id(0) {
    return; 
}

Queue<Action*>& GameLoop::getQueue() {
    return game_queue;
}

int GameLoop::addClientQueue(Queue<std::shared_ptr<GameStateForClient>>& queue) {
    player_queues[client_id++] = &queue;
    return client_id;

}
void GameLoop::run() {
    const int iterationsPerSecond = 20;
    Action* action = nullptr;
    while(!finished) {
        while(game_queue.try_pop(action)) {
            action->execute(id_handler);
            delete action;
            std::shared_ptr<GameStateForClient> game_state = game.update();
            std::shared_ptr<GameStateForClient> shared_game_state(game_state);
            for (auto& player_queue : player_queues) {
                player_queue.second->push(shared_game_state);
            } 
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1000 / iterationsPerSecond));
    }
}


void GameLoop::stop() {
    finished = true;
    game_queue.close();
}

