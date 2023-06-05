#include "game.h"

Game::Game(int32_t width, int32_t height) : 
    entities(),
    gameMap(width,height),
    infected(),
    soldiers(),
    shooting_soldiers(),
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
    this->shooting_soldiers.remove(id);
}

void Game::shootingEntitiesShoot(const uint32_t &id) {
    std::vector<VectorWrapper> entities_hit; //(id, distance)
    entities_hit = this->gameMap.shoot(id);
    //remueve los que no son infectados
    entities_hit.erase
    (std::remove_if(entities_hit.begin(), entities_hit.end(), [this](VectorWrapper& entity_hit) {
        return this->infected.find(entity_hit.getId()) == this->infected.end();
    }), entities_hit.end());

    std::vector<HitEntity> entities_hit_for_entity = 
        setUpHitEntities(entities_hit);//(entity, distance)
    this->entities[id]->shoot(entities_hit_for_entity);
}

void Game::setShooting(const uint32_t &id) {
    this->shooting_soldiers.push_back(id);
}

void Game::setReloading(const uint32_t &id) {
    this->shooting_soldiers.remove(id);
    Player *player = dynamic_cast<Player*>(this->entities[id]);
    player->setReload();
}

void Game::stopShooting(const uint32_t &id) {
    this->shooting_soldiers.remove(id);
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
    this->checkForRevivingSoldiers();
    this->infectedCheckForSoldiersInRange();
    this->checkForShooting();
    this->checkForInfectedAttack();
    this->updateAllEntities();
    std::shared_ptr<GameStateForClient> game_state = 
        std::make_shared<GameStateForClient>(this->entities, 
            this->gameMap.getWidth(), this->gameMap.getHeight());
    return game_state;
}

void Game::checkForShooting() {
    if (this->shooting_soldiers.empty()) return;
    for (auto soldier : this->shooting_soldiers) {
        this->shootingEntitiesShoot(soldier);
    }
}

void Game::checkForInfectedAttack() {
    for (auto&& id_entity : this->infected) {
        Infected* infected = dynamic_cast<Infected*>(id_entity.second);
        infected->checkForSoldiersInRangeAndSetAttack(this->soldiers);
    }
}

void Game::updateAllEntities() {
    for (auto&& id_entity : this->entities) {
        id_entity.second->update(std::ref(this->gameMap));
        if (id_entity.second->isDead() && id_entity.second->isInfected()) {
            this->gameMap.removeEntity(id_entity.first);
            this->removeEntity(id_entity.first);
        }
    }
}

void Game::removeEntity(const uint32_t &id) {
    this->infected.erase(id);
    this->soldiers.erase(id);
}

void Game::infectedCheckForSoldiersInRange() {
    for (auto& id_entity : this->infected) {
        if (id_entity.second->isInfected()) {
            Infected* infected = dynamic_cast<Infected*>(id_entity.second);
            infected->checkForSoldiersInRangeAndSetChase(this->soldiers);
        }
    }
}

void Game::checkForRevivingSoldiers() {
    for (auto& id_entity : this->entities) {
        Player* down_soldier = dynamic_cast<Player*>(id_entity.second);
        if (down_soldier && down_soldier->isDown()) {
           Movement* soldier_down_mov = down_soldier->getDirectionOfMovement();
            for (auto& id_soldier : this->soldiers) {
                Player* close_soldier = dynamic_cast<Player*>(id_soldier.second);
                if (close_soldier && !close_soldier->isDead() && !close_soldier->isReviving() && !close_soldier->isDown()) {
                    Movement* close_soldier_mov = close_soldier->getDirectionOfMovement();
                    double distance = (double)soldier_down_mov->calculateDistance(*close_soldier_mov);
                    if (distance <= CONFIG.soldier_max_distance_to_revive * CONFIG.soldier_radius) {
                        down_soldier->setReviving();
                    }
                }
            }
        }
    }
}

Game::~Game() {
    for (auto& id_entity : this->entities) {
        delete id_entity.second;
    }
}
