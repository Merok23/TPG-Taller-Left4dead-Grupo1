#include "game_state_for_client.h"

GameStateForClient::GameStateForClient
    (const std::map<uint32_t, Entity*> &entities, 
    uint32_t width, 
    uint32_t height, 
    bool game_over, 
    bool players_won) :
    entities(entities),
    width(width),
    height(height),
    game_over(game_over),
    players_won(players_won), 
    ammo_used(0),
    infected_killed(0),
    game_loop_time(0) {}

GameStateForClient::GameStateForClient(GameStateForClient*& other) :
    entities(other->entities),
    width(other->width),
    height(other->height),
    game_over(other->game_over),
    players_won(other->players_won) {}
    
std::map<uint32_t, Entity*>& GameStateForClient::getEntities(){
    return this->entities;
}

uint32_t GameStateForClient::getWidth() {
    return this->width;
}

uint32_t GameStateForClient::getHeight() {
    return this->height;
}

bool& GameStateForClient::isGameOver() {
    return this->game_over;
}

bool& GameStateForClient::didPlayersWin() {
    return this->players_won;
}

uint32_t GameStateForClient::getInfectedKilled() {
    return this->infected_killed;
}

uint32_t GameStateForClient::getAmmoUsed() {
    return this->ammo_used;
}

uint32_t GameStateForClient::getGameLoopTime() {
    return this->game_loop_time;
}

void GameStateForClient::setGameLoopTime(uint32_t time) {
    this->game_loop_time = time;
}
#include <iostream>
void GameStateForClient::setInfectedKilled(uint32_t infected_killed) {
    std::cout << " Set Infected killed: " << infected_killed << std::endl;
    this->infected_killed = infected_killed;
}

void GameStateForClient::setAmmoUsed(uint32_t ammo_used) {
    this->ammo_used = ammo_used;
}

