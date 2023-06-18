#include "game_loop.h"
#include <algorithm>
#include <utility>
#include <chrono>
#include "config.h"

#define MAX_ELEMENTS_QUEUE 1000

GameLoop::GameLoop(GameMode gameMode) : 
    game_queue(MAX_ELEMENTS_QUEUE), 
    game(CONFIG.scenario_width, CONFIG.scenario_height, gameMode), 
    id_handler(game), 
    finished(false), 
    client_id(0), 
    start_loop_time(std::chrono::high_resolution_clock::now()), 
    total_loop_time(0),
    mutex() {}

Queue<std::shared_ptr<Action>>& GameLoop::getQueue() {
    return game_queue;
}

int GameLoop::addClientQueue(Queue<std::shared_ptr<GameStateForClient>>& queue) {
    std::unique_lock<std::mutex> lock(mutex);
    client_id++;
    player_queues[client_id] = &queue;
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

bool GameLoop::isRoomEmpty() {
    return player_queues.empty();
}

void GameLoop::endGameLoopTime() {
    auto t2 = std::chrono::high_resolution_clock::now();
    auto total_loop_time_aux = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - this->start_loop_time);
    this->total_loop_time = total_loop_time_aux.count();
}

int GameLoop::getTotalTimeOfGameLoop() {
    return total_loop_time;
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
            auto dt = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);//count casts to int
            int rest = rate - dt.count();
            // rest is the ammount of time we have to wait
            // if rest is negative, we are behind schedule
            if (rest > 0) std::this_thread::sleep_for(std::chrono::milliseconds(rest)); 
            //if it's negative we don't sleep, we just continue trying to catch up.

            if (game_state->isGameOver()) {
                this->stop();
                setGameStadistics(game_state);   
                break;
            }
            for (auto& player_queue : player_queues) {
                player_queue.second->push(game_state);
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

void GameLoop::setGameStadistics(std::shared_ptr<GameStateForClient>& game_state) {
    for (auto& player_queue : player_queues) {
        game_state->setAmmoUsed(id_handler.getAmmountOfAmmoUsed(player_queue.first));
        game_state->setInfectedKilled(id_handler.getAmmountOfInfectedKilled(player_queue.first));
        game_state->setGameLoopTime(this->getTotalTimeOfGameLoop());
        std::cout << "Game state: " << game_state->isGameOver() << std::endl;
        std::cout << "Players won: " << game_state->didPlayersWin() << std::endl;
        std::cout << "Infected killed: " << game_state->getInfectedKilled() << std::endl;
        std::cout << "Ammo used: " << game_state->getAmmoUsed() << std::endl;
        std::cout << "Game loop time: " << game_state->getGameLoopTime() << std::endl;
        player_queue.second->push(game_state);
    }
}
void GameLoop::stop() {
    if (!finished) {
        this->endGameLoopTime();
        finished = true;
    }
}
GameLoop::~GameLoop() {
    game_queue.close();
}

