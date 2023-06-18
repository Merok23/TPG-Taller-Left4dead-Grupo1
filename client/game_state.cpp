#include "game_state.h"
#include <string>
#include <iostream>
#include <memory>

GameState::GameState() : 
    entities(),
    game_over(false), 
    players_won(false), 
    lost_connection(true),
    ammo_used(0), 
    infected_killed(0), 
    game_loop_time(0) {}

GameState::GameState(const std::map<uint32_t, Entity*>& entities,
    bool game_over,
    bool players_won) : 
    entities(entities), 
    game_over(game_over),
    players_won(players_won), 
    lost_connection(false), 
    ammo_used(0), 
    infected_killed(0), 
    game_loop_time(0) {}

GameState::GameState(const std::map<uint32_t, Entity*>& entities,
    bool game_over,
    bool players_won,
    uint32_t ammo_used,
    uint32_t infected_killed,
    uint32_t game_loop_time) : 
    entities(entities), 
    game_over(game_over),
    players_won(players_won), 
    lost_connection(false), 
    ammo_used(ammo_used), 
    infected_killed(infected_killed), 
    game_loop_time(game_loop_time) {}
    
void GameState::setLostConnection() {
    this->lost_connection = true;
}

GameState::~GameState() {
    for (auto&& id_entity : this->entities) {
        delete id_entity.second;
    }
}
