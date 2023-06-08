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
    players_won(players_won) {}

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

bool GameStateForClient::isGameOver() {
    return this->game_over;
}

bool GameStateForClient::didPlayersWin() {
    return this->players_won;
}
