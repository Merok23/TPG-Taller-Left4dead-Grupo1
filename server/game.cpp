#include "game.h"

Game::Game(int32_t width, int32_t height) : 
    entities(),
    gameMap(width,height),
    infected(),
    soldiers(),
    current_id(0) {}

void Game::addEntity(Entity* entity) {
    this->entities[entity->getId()] = entity;
    this->gameMap.addEntity(entity->getId(), entity->getDirectionOfMovement());
    if (entity->isInfected()) {
        this->infected[entity->getId()] = entity;
    } else {
        this->soldiers[entity->getId()] = entity;
    }
    this->current_id++;
}

uint32_t Game::getCurrentId() {
    return this->current_id;
}

void Game::setMoving(const uint32_t &id, const int32_t &x, const int32_t &y) {
    this->entities[id]->move(x,y);
}

void Game::setShooting(const uint32_t &id) {
    std::vector<VectorWrapper> entities_hit; //(id, distance)
    entities_hit = this->gameMap.shoot(id);
    //remueve los que no son infectados
    entities_hit.erase(std::remove_if(entities_hit.begin(), entities_hit.end(), [this](VectorWrapper& entity_hit) {
        return this->infected.find(entity_hit.getId()) == this->infected.end();
    }), entities_hit.end());

    std::vector<HitEntity> entities_hit_for_entity = setUpHitEntities(entities_hit);//(entity, distance)
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
    infectedCheckForSoldiersInRange();
    for (auto&& id_entity : this->entities) {
        id_entity.second->update(std::ref(this->gameMap));
    }
    std::shared_ptr<GameStateForClient> game_state = 
        std::make_shared<GameStateForClient>(this->entities, 
            this->gameMap.getWidth(), this->gameMap.getHeight());
    return game_state;
}

void Game::infectedCheckForSoldiersInRange() {
    for (auto& id_entity : this->infected) {
        if (id_entity.second->isInfected()) {
            Infected* infected = dynamic_cast<Infected*>(id_entity.second);
            infected->checkForSoldiersInRangeAndSetChase(this->soldiers);
        }
    }
}

Game::~Game() {
    for (auto& id_entity : this->entities) {
        delete id_entity.second;
    }
}
