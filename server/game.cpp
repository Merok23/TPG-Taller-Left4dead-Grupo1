#include "game.h"

Game::Game(int32_t width, int32_t height) : entities(), gameMap(width,height) {}

void Game::addEntity(Entity* entity) {
    this->entities[entity->getId()] = entity;
    this->gameMap.addEntity(entity->getId(), entity->getDirectionOfMovement());
}

void Game::setMoving(const uint32_t &id, const int8_t &x, const int8_t &y) {
    this->entities[id]->move(x,y);
}

void Game::setShooting(const uint32_t &id) {
    std::vector<uint32_t[2]> entities_hit;
    entities_hit = this->gameMap.shoot(id);
    for (auto entity : entities_hit) {
        this->entities[entity[0]]->setDamage(this->entities[id]->getWeapon(), entity[1]);
    }
}

std::map<uint32_t, Entity*>& Game::getEntities() {
    return this->entities;
}

std::shared_ptr<GameStateForClient> Game::update() {
    for (auto id_entity : this->entities) {
        id_entity.second->update(std::ref(this->gameMap));
    }
    GameStateForClient* game_state = 
        new GameStateForClient(this->getEntities(), 
            this->gameMap.getWidth(), 
                this->gameMap.getHeight());
    return std::make_shared<GameStateForClient>(game_state);
}
