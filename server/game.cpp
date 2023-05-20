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
    std::vector<VectorWrapper> entities_hit;
    entities_hit = this->gameMap.shoot(id);
    std::vector<HitEntity> entities_hit_for_entity = setUpHitEntities(entities_hit);
    this->entities[id]->shoot(entities_hit_for_entity);
}

std::vector<HitEntity> Game::setUpHitEntities(const std::vector<VectorWrapper>& entities_hit) {
    std::vector<HitEntity> entities_hit_for_entity;
    for (auto entity_hit : entities_hit) {
        Entity* entity = this->entities[entity_hit.getId()];
        int32_t distance = entity_hit.getDistance();
        HitEntity hit_entity(entity, distance);
        entities_hit_for_entity.push_back(hit_entity);
    }
    return entities_hit_for_entity;
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
