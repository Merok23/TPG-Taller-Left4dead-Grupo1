#include "game_state.h"
#include <string>
#include <iostream>
#include <memory>

GameState::GameState() : 
    entities(),
    game_over(false), 
    players_won(false), 
    lost_connection(true),
    statistics() {}

GameState::GameState(const std::map<uint32_t, Entity*>& entities,
    bool game_over,
    bool players_won) : 
    entities(entities), 
    game_over(game_over),
    players_won(players_won), 
    lost_connection(false), 
    statistics() {}

GameState::GameState(const std::map<uint32_t, Entity*>& entities,
    bool game_over,
    bool players_won,
    Statistics statistics) : 
    entities(entities), 
    game_over(game_over),
    players_won(players_won), 
    lost_connection(false), 
    statistics(statistics){}
    
void GameState::setLostConnection() {
    this->lost_connection = true;
}

std::pair<uint8_t, uint32_t> GameState::getInfectedKilled() {
    return this->statistics.getInfectedKilledInfo();
}

std::pair<uint8_t, uint32_t> GameState::getAmmoUsed() {
    return this->statistics.getAmmoUsedInfo();
}

std::pair<uint8_t, uint32_t> GameState::getGameLoopTime() {
    return this->statistics.getGameTimeInfo();
}

GameState::~GameState() {
    for (auto&& id_entity : this->entities) {
        delete id_entity.second;
    }
}


