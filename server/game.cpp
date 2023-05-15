#include "game.h"

Game::Game(int32_t width, int32_t height) : entities(), gameMap(width,height, std::ref(entities)) {}

void Game::addEntity(Entity* entity) {
    this->entities[entity->getId()] = entity;
    this->gameMap.addEntity(entity->getDirectionOfMovement());
}

void Game::setMoving(uint32_t id, int8_t x, int8_t y) {
    this->entities[id]->move(x,y);
}

GameStateForClient Game::update() {
    for (auto const& [key, val] : this->entities) {
        val.update(std::ref(this->gameMap));
    }
    return GameStateForClient(this->gameMap.getEntities(), this->gameMap.getWidth(), this->gameMap.getHeight());
}