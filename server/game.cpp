#include "game.h"

Game::Game(int32_t width, int32_t height) : entities(), gameMap(width,height) {}

void Game::addEntity(Entity* entity) {
    this->entities[entity->getId()] = entity;
    this->gameMap.addEntity(entity->getId(), entity->getDirectionOfMovement());
}

void Game::setMoving(uint32_t id, int8_t x, int8_t y) {
    this->entities[id]->move(x,y);
}

std::map<uint32_t, Entity*>& Game::getEntities() {
    return this->entities;
}

std::shared_ptr<GameStateForClient> Game::update() {
    for (auto& id_entity : this->entities) {
        id_entity.second->update(std::ref(this->gameMap));
    }
    std::shared_ptr<GameStateForClient> game_state = std::make_shared<GameStateForClient>(
        this->getEntities(),
        this->gameMap.getWidth(),
        this->gameMap.getHeight()
    );
    return game_state;
}
