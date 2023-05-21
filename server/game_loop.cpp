#include "game_loop.h"
#include <chrono>
#include "config.h"

#define MAX_ELEMENTS_QUEUE 1000
GameLoop::GameLoop() : game_queue(MAX_ELEMENTS_QUEUE), game(CONFIG.scenario_width, CONFIG.scenario_height), finished(false) {
    return; 
}

void GameLoop::addPlayer(uint32_t id, Queue<std::shared_ptr<GameStateForClient>>& queue) {
    player_queues[id] = &queue;
    Player newPlayer = Player(id, 5, 5);
    Entity* player = &newPlayer;
    game.addEntity(player);
}

Queue<Action*>& GameLoop::getQueue() {
    return game_queue;
}

void GameLoop::addClientQueue(Queue<std::shared_ptr<GameStateForClient>>& queue) {
    player_queues[0] = &queue;
}
void GameLoop::run() {
    const int iterationsPerSecond = 20;
    Action* action = nullptr;
    while(!finished) {
        while(game_queue.try_pop(action)) {
            action->execute(game);
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

