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
    stadistics() {}

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

void GameStateForClient::setStadistics(bool ranking, std::pair<uint8_t, uint32_t> infected_killed_info, 
    std::pair<uint8_t, uint32_t> ammo_used_info, 
    std::pair<uint8_t, uint32_t> game_time_info) {
    this->stadistics.setStadistics(ranking, infected_killed_info, ammo_used_info, game_time_info);
}

std::pair<uint8_t, uint32_t> GameStateForClient::getInfectedKilled() {
    return this->stadistics.getInfectedKilledInfo();
}

std::pair<uint8_t, uint32_t> GameStateForClient::getAmmoUsed() {
    return this->stadistics.getAmmoUsedInfo();
}

std::pair<uint8_t, uint32_t> GameStateForClient::getGameLoopTime() {
    return this->stadistics.getGameTimeInfo();
}
