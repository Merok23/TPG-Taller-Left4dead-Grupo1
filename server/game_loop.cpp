#include "game_loop.h"
#include <algorithm>
#include <utility>
#include <chrono>
#include "config.h"

#define MAX_ELEMENTS_QUEUE 1000
GameLoop::GameLoop() : 
    game_queue(MAX_ELEMENTS_QUEUE), 
    game(CONFIG.scenario_width, CONFIG.scenario_height), 
    id_handler(game), 
    finished(false), 
    client_id(0), 
    mutex() {}

Queue<Action*>& GameLoop::getQueue() {
    return game_queue;
}

int GameLoop::addClientQueue(Queue<std::shared_ptr<GameStateForClient>>& queue) {
    std::unique_lock<std::mutex> lock(mutex);
    player_queues[client_id++] = &queue;
    return client_id;
}

void GameLoop::deleteClientQueue(Queue<std::shared_ptr<GameStateForClient>>& queue) {
    std::unique_lock<std::mutex> lock(mutex);
    auto it = std::find_if(player_queues.begin(), player_queues.end(),
        [&](const std::pair<uint32_t, Queue<std::shared_ptr<GameStateForClient>>*>& pair) {
            return pair.second == &queue;
        });
    if (it != player_queues.end()) player_queues.erase(it);
}


void GameLoop::run() {
    const int iterationsPerSecond = 20;
    Action* action = nullptr;
    while (!finished) {
        while (game_queue.try_pop(action)) {
            action->execute(id_handler);
            delete action;
        std::shared_ptr<GameStateForClient> game_state = game.update();
        for (auto& player_queue : player_queues) {
            player_queue.second->push(game_state);
        }
        } 
        std::this_thread::sleep_for(std::chrono::milliseconds(1000 / iterationsPerSecond));
    }
}


void GameLoop::stop() {
    finished = true;
    game_queue.close();
}

