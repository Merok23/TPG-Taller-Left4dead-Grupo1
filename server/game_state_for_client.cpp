#include "game_state_for_client.h"

GameStateForClient::GameStateForClient
    (const std::map<uint32_t, Entity*> &entities, uint32_t width, uint32_t height) :
    entities(entities),
    width(width),
    height(height) {}

std::map<uint32_t, Entity*>& GameStateForClient::getEntities(){
    return this->entities;
}

uint32_t GameStateForClient::getWidth() {
    return this->width;
}

uint32_t GameStateForClient::getHeight() {
    return this->height;
}
