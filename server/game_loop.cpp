#include "game_loop.h"
#include <algorithm>
#include <utility>
#include <chrono>
#include "config.h"

#define MAX_ELEMENTS_QUEUE 1000

GameLoop::GameLoop(GameMode gameMode) : 
    game_queue(MAX_ELEMENTS_QUEUE), 
    game_mode(gameMode),
    game(CONFIG.scenario_width, CONFIG.scenario_height, game_mode), 
    id_handler(game), 
    finished(false), 
    client_id(0), 
    mutex() {}

Queue<std::shared_ptr<Action>>& GameLoop::getQueue() {
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

bool GameLoop::isFinished() {
    return finished;
}

GameMode GameLoop::getGameMode() {
    return game_mode;
}

bool GameLoop::isRoomEmpty() {
    return player_queues.empty();
}

void GameLoop::run() {
    const int iterationsPerSecond = 20;
    int rate = 1000 / iterationsPerSecond;
    std::shared_ptr<Action> action = nullptr;
    auto t1 = std::chrono::high_resolution_clock::now();

    while (!finished) {
        try {
            while (game_queue.try_pop(action)) {
                action->execute(id_handler);
            } 
            std::shared_ptr<GameStateForClient> game_state = game.update();
            
            //we calculate how much time we spent in the loop
            auto t2 = std::chrono::high_resolution_clock::now();
            auto dt = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();//count casts to int
            int rest = rate - dt;
            // rest is the ammount of time we have to wait
            // if rest is negative, we are behind schedule
            if (rest > 0) std::this_thread::sleep_for(std::chrono::milliseconds(rest)); 
            //if it's negative we don't sleep, we just continue trying to catch up.

            for (auto& player_queue : player_queues) {
                player_queue.second->push(game_state);
            }
            if (game_state->isGameOver()) {
                finished = true;
            }
            //we reset the clock
            t1 = std::chrono::high_resolution_clock::now();
        } catch (const ClosedQueue& e) {
            if (finished) return;
            std::cerr << "Error: " << e.what() << std::endl;
            finished = true;
        } 
    }
}


void GameLoop::stop() {
    finished = true;
    game_queue.close();
}

