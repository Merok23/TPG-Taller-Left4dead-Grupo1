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

GameMode GameLoop::getGameMode() {
    return game_mode;
}

bool GameLoop::isRoomEmpty() {
    return player_queues.empty();
}

void GameLoop::endGameLoopTime() {
    auto t2 = std::chrono::high_resolution_clock::now();
    auto total_loop_time_aux = std::chrono::duration_cast<std::chrono::seconds>(t2 - this->start_loop_time);
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
    if (game_mode == GameMode::CLEAR_THE_ZONE) {
        this->setStadisticsCTZ(game_state);
    } else {
       this->setStadisticsSurvival(game_state);
    }
}

void GameLoop::setStadisticsCTZ(std::shared_ptr<GameStateForClient>& game_state) {
    for (auto& player_queue : player_queues) {
            std::shared_ptr<GameStateForClient> game_state_for_each_client = std::make_shared<GameStateForClient>(game_state->getEntities(), game_state->isGameOver(), game_state->didPlayersWin());
            std::pair<uint8_t, uint32_t> infected_killed = std::make_pair(0, id_handler.getAmmountOfInfectedKilled(player_queue.first));
            std::pair<uint8_t, uint32_t> ammo_used = std::make_pair(0, id_handler.getAmmountOfAmmoUsed(player_queue.first));
            std::pair<uint8_t, uint32_t> game_time = std::make_pair(0, this->getTotalTimeOfGameLoop());
            game_state_for_each_client->setStadisticsCTZ(false, infected_killed, ammo_used, game_time);
            player_queue.second->push(game_state_for_each_client);
    }
}

void GameLoop::sortRankingStadistic(std::vector<std::pair<uint32_t, uint32_t>>& stadistic) {
    auto sorting_lambda = [](const auto& a, const auto& b) {
        return a.second > b.second;
    };
    std::sort(stadistic.begin(), stadistic.end(), sorting_lambda);
}


uint8_t GameLoop::getRanking(std::vector<std::pair<uint32_t, uint32_t>>& stadistic, uint32_t id) {
    auto getRankingPosition = [&](const auto& ranking) -> std::ptrdiff_t {
        auto it = std::find_if(ranking.begin(), ranking.end(), [&](const auto& player) {
            return player.first == id;
        });
        return std::distance(ranking.begin(), it) + 1;
    };
    return getRankingPosition(stadistic);
}

void GameLoop::setStadisticsSurvival(std::shared_ptr<GameStateForClient>& game_state) {
    std::vector<std::pair<uint32_t, uint32_t>> players_infected_killed;
    std::vector<std::pair<uint32_t, uint32_t>> players_ammo_used;
    std::vector<std::pair<uint32_t, uint32_t>> players_game_time;

    for (const auto& player_queue : player_queues) {
        uint32_t infected_kills = id_handler.getAmmountOfInfectedKilled(player_queue.first);
        players_infected_killed.emplace_back(player_queue.first, infected_kills);

        uint32_t ammo_used = id_handler.getAmmountOfAmmoUsed(player_queue.first);
        players_ammo_used.emplace_back(player_queue.first, ammo_used);


        uint32_t game_time = id_handler.getTimeOfDeath(player_queue.first);
        players_game_time.emplace_back(player_queue.first, game_time);

        statistics_handler.updateStatistics(infected_kills, ammo_used, game_time);
    }

    this->sortRankingStadistic(players_infected_killed);
    this->sortRankingStadistic(players_ammo_used);
    this->sortRankingStadistic(players_game_time);
    
    for (const auto& player_queue : player_queues) {
        std::shared_ptr<GameStateForClient> game_state_for_each_client = std::make_shared<GameStateForClient>(game_state->getEntities(), game_state->isGameOver(), game_state->didPlayersWin());
        std::pair<uint8_t, uint32_t> infected_killed = {this->getRanking(players_infected_killed, player_queue.first), id_handler.getAmmountOfInfectedKilled(player_queue.first)};
        std::pair<uint8_t, uint32_t> ammo_used = {this->getRanking(players_ammo_used, player_queue.first), id_handler.getAmmountOfAmmoUsed(player_queue.first)};
        std::pair<uint8_t, uint32_t> game_time = {this->getRanking(players_game_time, player_queue.first), id_handler.getTimeOfDeath(player_queue.first)};
        game_state_for_each_client->setStatisticsSurvival(true, infected_killed, ammo_used, game_time, statistics_handler.getTopInfectedKills(), statistics_handler.getTopAmmoUsed(), statistics_handler.getTopTimeAlive());
        player_queue.second->push(game_state_for_each_client);
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

