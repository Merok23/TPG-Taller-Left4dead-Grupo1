#include "game_loop.h"
#include <chrono>

#define MAX_ELEMENTS_QUEUE 1000
GameLoop::GameLoop() : game_queue(MAX_ELEMENTS_QUEUE), game(Game(1000,1000)), finished(false) {
    return; 
}

void GameLoop::addPlayer(uint32_t id, Queue<GameStateForClient*>& queue) {
    player_queues[id] = &queue;
    Player newPlayer = Player(id, 5, 5);
    Entity* player = &newPlayer;
    game.addEntity(player);
}

Queue<Action*>& GameLoop::getQueue() {
    return game_queue;
}

void GameLoop::addClientQueue(Queue<GameStateForClient*>& queue) {
    player_queues[0] = &queue;
}
void GameLoop::run() {
    const int iterationsPerSecond = 20;
    Action* action = nullptr;
    while(!finished) {
        while(game_queue.try_pop(action)) {
            action->execute(game);
            delete action;
            GameStateForClient* game_state = game.update();
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

