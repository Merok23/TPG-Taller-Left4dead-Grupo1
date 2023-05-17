#include "game_loop.h"
#include <chrono>

#define MAX_ELEMENTS_QUEUE 1000
GameLoop::GameLoop() : game_queue(MAX_ELEMENTS_QUEUE), game(1000,1000) {
    return; 
}

void GameLoop::addPlayer(uint32_t id, Queue<std::shared_ptr<GameStateForClient>>& queue) {
    player_queues[id] = &queue;
    Player newPlayer = Player(id);
    Entity* player = &newPlayer;
    game.addEntity(player);
}

Queue<std::shared_ptr<Action>>& GameLoop::getQueue() {
    return game_queue;
}

void GameLoop::run() {
    const int iterationsPerSecond = 20;
    std::shared_ptr<Action> action;

    while(!finished) {
        while(game_queue.try_pop(action)) {
            action->execute(game);
        }
        std::shared_ptr<GameStateForClient> game_state = game.update();
        sendState(game_state);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000 / iterationsPerSecond));
    }
}

void GameLoop::sendState(std::shared_ptr<GameStateForClient> game_state) {
    for (auto& player_queue : player_queues) {
        player_queue.second->push(game_state);
    }
}
