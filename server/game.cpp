#include "game.h"

Game::Game(int32_t width, int32_t height) : 
    entities(),
    gameMap(width,height),
    infected(),
    soldiers(),
    shooting_soldiers(),
    survival_mode(false),
    survival_mode_counter(CONFIG.survival_mode_timer),
    survival_mode_multiplier(1),
    current_id(0) {}

void Game::addEntity(Entity* entity) {
    this->entities[entity->getId()] = entity;
    this->gameMap.addEntity(entity->getId(), entity->getDirectionOfMovement());
    if (entity->isInfected()) {
        this->infected[entity->getId()] = entity;
    } else if (entity->isSoldier()){
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
    if (this->survival_mode) survivalUpdate();
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

void Game::setSurvivalMode() {
    this->survival_mode = true;
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

void Game::survivalUpdate() {
    this->survival_mode_counter--;
    if (this->survival_mode_counter != 0) return;
    this->survival_mode_counter = CONFIG.survival_mode_timer;
    this->spawnInfected();
    this->makeInfectedStronger();
    survival_mode_multiplier *= CONFIG.survival_mode_accumulator;
}

void Game::spawnCommonInfected(int ammount) {
    for (int i = 0; i < ammount; i ++) {
        uint32_t x = 0;
        uint32_t y = 0;
        if (searchForPosition(CONFIG.common_infected_radius, x, y)) {
            //id is not a problem (race condition) since there is no 
            //other thread calling for addEntity in the game update
            Entity* infected = new CommonInfected(current_id, x, y);
            this->addEntity(infected);
        }
    }
}

bool Game::searchForPosition(const uint32_t &radius, uint32_t &x, uint32_t &y) {
        bool found = false;
        while(!found) {
            x = rand() % this->gameMap.getWidth() + radius;
            y = rand() % this->gameMap.getHeight() + radius;
            if (!this->gameMap.checkForCollisionInPosition(x, y, CONFIG.common_infected_radius)) found = true;
        }
        return found;
}

void Game::spawnInfected() {
    this->spawnCommonInfected(rand() % CONFIG.survival_mode_max_common_infected);
}

void Game::makeInfectedStronger() {
    for (auto& id_entity : this->infected) {
        Infected* infected = dynamic_cast<Infected*>(id_entity.second);
        infected->makeStronger(survival_mode_multiplier);
    }
}

Game::~Game() {
    for (auto& id_entity : this->entities) {
        delete id_entity.second;
    }
}
