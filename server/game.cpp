#include "game.h"

Game::Game(int32_t width, int32_t height) : 
    entities(),
    gameMap(width,height),
    infected(),
    soldiers(),
    witches(),
    shooting_soldiers(),
    clear_the_zone(false),
    zone_is_set(false),
    clear_the_zone_max_infected(CONFIG.clear_the_zone_infected_total),
    survival_mode(false),
    survival_mode_counter(CONFIG.survival_mode_timer),
    max_common_infected_per_spawn(CONFIG.survival_mode_max_common_infected),
    max_spear_infected_per_spawn(CONFIG.survival_mode_max_spear_infected),
    max_witch_infected_per_spawn(CONFIG.survival_mode_max_witch_infected),
    survival_mode_multiplier(CONFIG.survival_mode_starting_multiplier),
    current_id(0),
    game_started(false),
    game_over(false),
    players_won(false),
    craters_have_spawned(false) {}

Game::Game(int32_t width, int32_t height, GameMode gameMode) : 
    entities(),
    gameMap(width,height),
    infected(),
    soldiers(),
    witches(),
    shooting_soldiers(),
    clear_the_zone(gameMode == GameMode::CLEAR_THE_ZONE),
    zone_is_set(false),
    clear_the_zone_max_infected(CONFIG.clear_the_zone_infected_total),
    survival_mode(gameMode == GameMode::SURVIVAL),
    survival_mode_counter(CONFIG.survival_mode_timer),
    max_common_infected_per_spawn(CONFIG.survival_mode_max_common_infected),
    max_spear_infected_per_spawn(CONFIG.survival_mode_max_spear_infected),
    max_witch_infected_per_spawn(CONFIG.survival_mode_max_witch_infected),
    survival_mode_multiplier(CONFIG.survival_mode_starting_multiplier),
    current_id(0),
    game_started(false),
    game_over(false),
    players_won(false),
    craters_have_spawned(false) {}

void Game::addEntity(Entity* entity) {
    //TODO: if ID already exists, throw exception
    this->entities[entity->getId()] = entity;
    this->gameMap.addEntity(entity->getId(), entity->getDirectionOfMovement());
    if (entity->isInfected()) {
        this->infected[entity->getId()] = entity;
        if (entity->getEntityType() == "witch") {
            this->witches[entity->getId()] = dynamic_cast<WitchInfected*>(entity);
        }
    } else if (entity->isSoldier()){
        this->soldiers[entity->getId()] = entity;
        this->gameMap.addSoldier(entity->getId(), entity->getDirectionOfMovement());
        this->game_started = true;
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
    if (this->entities[id]->isDead()) return; //optimization
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

void Game::setCheat(const uint32_t &id, const Cheat &cheat) {
    switch (cheat) {
        case Cheat::INFINITE_HITPOINTS:
            this->entities[id]->setHitPoints(CONFIG.cheat_infinite_hitpoints);
            break;
        case Cheat::SPAWN_COMMON_INFECTED:
            this->spawnInfectedCheat(id);
            break;
        case Cheat::KILL_ALL_INFECTED:
            this->killAllInfectedCheat();
            break;
    }
}

void Game::killAllInfectedCheat() {
    for (auto& infected : this->infected) {
        Infected* infected_entity = dynamic_cast<Infected*>(infected.second);
        infected_entity->killCheat();
    }
}

void Game::spawnInfectedCheat(const uint32_t &id) {
    Movement* soldier_mov = this->entities[id]->getDirectionOfMovement();
    uint32_t x = soldier_mov->getX();
    x += CONFIG.soldier_radius + CONFIG.common_infected_radius + 1;
    uint32_t y = soldier_mov->getY();
    uint32_t radius = CONFIG.common_infected_radius;
    if (gameMap.checkForCollisionInPosition(x, y, radius)) return;
    Entity* infected = new CommonInfected(this->current_id, x, y);
    this->addEntity(infected);
}

void Game::stopShooting(const uint32_t &id) {
    Player *player = dynamic_cast<Player*>(this->entities[id]);
    player->stopShooting();
    this->shooting_soldiers.remove(id);
}

std::vector<HitEntity> Game::setUpHitEntities(std::vector<VectorWrapper>& entities_hit) {
    std::vector<HitEntity> entities_hit_for_entity;
    for (auto& entity_hit : entities_hit) {
        Entity* entity = this->entities[entity_hit.getId()];
        int32_t distance = entity_hit.getDistance();
        HitEntity hit_entity(entity, distance);
        entities_hit_for_entity.push_back(hit_entity);
    }
    return entities_hit_for_entity;
}

/*
std::unique_ptr<std::vector<HitEntity>> Game::setUpHitEntities(std::vector<VectorWrapper>& entities_hit) {
    auto entities_hit_for_entity = std::make_unique<std::vector<HitEntity>>();
    for (auto& entity_hit : entities_hit) {
        Entity* entity = this->entities[entity_hit.getId()];
        int32_t distance = entity_hit.getDistance();
        HitEntity hit_entity(entity, distance);
        entities_hit_for_entity->push_back(hit_entity);
    }
    return entities_hit_for_entity;
}
*/
std::map<uint32_t, Entity*>& Game::getEntities() {
    return this->entities;
}

std::shared_ptr<GameStateForClient> Game::update() {
    //--------------------GAME OVER--------------------//
    if (this->game_over) return std::make_shared<GameStateForClient>(this->entities, 
        this->gameMap.getWidth(), 
        this->gameMap.getHeight(),
        this->game_over,
        this->players_won); 
    //-------------------------------------------------//
    
    if (!this->craters_have_spawned && (this->survival_mode || this->clear_the_zone)) spawnCraters(CONFIG.crater_ammount);
    if (this->survival_mode) survivalUpdate();
    if (this->clear_the_zone && !this->zone_is_set) setTheZone();
    this->checkForRevivingSoldiers();
    this->infectedCheckForSoldiersInRange();
    this->checkForShooting();
    this->checkForInfectedAttack();
    this->checkForScreamingWitches();
    this->updateAllEntities();
    this->checkForGameOver();
    std::shared_ptr<GameStateForClient> game_state = 
        std::make_shared<GameStateForClient>(this->entities, 
            this->gameMap.getWidth(), 
            this->gameMap.getHeight(),
            this->game_over,
            this->players_won);
    return game_state;
}

void Game::checkForGameOver() {
    if (!this->game_started) return;
    if (this->survival_mode) {
        this->game_over = this->checkForPartyWipe();
    } else if (this->clear_the_zone) {
        if (this->checkForPartyWipe()) this->game_over = true;
        if (this->infected.empty()) {
            this->players_won = true;
            this->game_over = true;
        }
    }
}

bool Game::checkForPartyWipe() {
    bool party_wipe = true;
    auto it = soldiers.begin();
    while (it != soldiers.end() && party_wipe) {
        if (!it->second->isDead()) party_wipe = false;
        it++;
    }
    return party_wipe;
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

void Game::spawnWitchInfectedFromScream(const uint32_t &id) {
    this->witches[id]->setSpawnedInfected();
    for (int i = 0; i < CONFIG.witch_infected_scream_spawn_ammount; i++) {
        uint32_t x = 0;
        uint32_t y = 0;
        if (searchForPosition(CONFIG.common_infected_radius, x, y)) {
            Entity* infected = new CommonInfected(current_id, x, y);
            this->addEntity(infected);
            CommonInfected* common = dynamic_cast<CommonInfected*>(infected);
            common->setFollowWitch(this->entities[id]);
        }
    }
    

}

void Game::checkForScreamingWitches() {
    for (auto&& witch : this->witches) {
        if (witch.second->isShouting() && !witch.second->hasSpawnedInfected()) this->spawnWitchInfectedFromScream(witch.first);
    }
}

void Game::updateAllEntities() {
    for (auto&& id_entity : this->entities) {
        id_entity.second->update(std::ref(this->gameMap));
        if (id_entity.second->isDead()) {
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
    //this->soldiers.erase(id);
}

void Game::infectedCheckForSoldiersInRange() {
    for (auto& id_entity : this->infected) {
        if (id_entity.second->isInfected()) {
            Infected* infected = dynamic_cast<Infected*>(id_entity.second);
            infected->checkForSoldiersInRangeAndSetChase(this->soldiers);
        }
    }
}

void Game::setTheZone() {
    this->zone_is_set = true;
    this->spawnCommonInfected(CONFIG.common_infected_zone_percentage * this->clear_the_zone_max_infected);
    this->spawnSpearInfected(CONFIG.spear_infected_zone_percentage * this->clear_the_zone_max_infected);
    this->spawnWitchInfected(CONFIG.witch_infected_zone_percentage * this->clear_the_zone_max_infected);
    //this->spawnJumperInfected(CONFIG.jumper_infected_zone_percentage * this->clear_the_zone_max_infected);
    //this->spawnVenomInfected(CONFIG.venom_infected_zone_percentage * this->clear_the_zone_max_infected);
}

void Game::survivalUpdate() {
    this->survival_mode_counter--;
    if (this->survival_mode_counter != 0) return;
    this->survival_mode_counter = CONFIG.survival_mode_timer;
    this->spawnInfected();
    this->makeInfectedStronger();
    survival_mode_multiplier *= CONFIG.survival_mode_accumulator;
    max_common_infected_per_spawn *= CONFIG.survival_mode_accumulator;
    max_spear_infected_per_spawn *= CONFIG.survival_mode_accumulator;
}

//Replace for factory design for uniting all of these.
void Game::spawnCraters(int ammount) {
    this->craters_have_spawned = true;
    for (int i = 0; i < ammount; i++) {
        uint32_t x = 0;
        uint32_t y = 0;
        if (searchForPosition(CONFIG.crater_radius, x, y)) {
            Entity* crater = new Crater(current_id, x, y);
            this->addEntity(crater);
        }
    }
}

void Game::spawnCommonInfected(int ammount) {
    for (int i = 0; i < ammount; i++) {
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

void Game::spawnSpearInfected(int ammount) {
    for (int i = 0; i < ammount; i++) {
        uint32_t x = 0;
        uint32_t y = 0;
        if (searchForPosition(CONFIG.spear_infected_radius, x, y)) {
            //id is not a problem (race condition) since there is no 
            //other thread calling for addEntity in the game update
            Entity* infected = new SpearInfected(current_id, x, y);
            this->addEntity(infected);
        }   
    }
}

void Game::spawnWitchInfected(int ammount) {
        for (int i = 0; i < ammount; i++) {
        uint32_t x = 0;
        uint32_t y = 0;
        if (searchForPosition(CONFIG.witch_infected_radius, x, y)) {
            //id is not a problem (race condition) since there is no 
            //other thread calling for addEntity in the game update
            Entity* infected = new WitchInfected(current_id, x, y);
            this->addEntity(infected);
        }   
    }
}

bool Game::searchForPosition(const uint32_t &radius, uint32_t &x, uint32_t &y) {
        bool found = false;
        int mod_x = this->gameMap.getWidth() - 2 * radius;
        int mod_y = this->gameMap.getHeight() - 2 * radius;
        while(!found) {
            x = rand() % mod_x;
            y = rand() % mod_y;
            x += radius;
            y += radius;
            if (!this->gameMap.checkForCollisionInPosition(x, y, radius)) found = true;
        }
        return found;
}

void Game::spawnInfected() {
    //this could be done with a factory pattern
    this->spawnCommonInfected(rand() % this->max_common_infected_per_spawn + 1);
    this->spawnSpearInfected(rand() % this->max_spear_infected_per_spawn + 1);
    this->spawnWitchInfected(rand() % this->max_witch_infected_per_spawn + 1);
}

void Game::makeInfectedStronger() {
    for (auto& id_entity : this->infected) {
        Infected* infected = dynamic_cast<Infected*>(id_entity.second);
        infected->makeStronger(survival_mode_multiplier);
    }
}

void Game::checkForRevivingSoldiers() {
    for (auto soldier : this->soldiers) {
        Player* player = dynamic_cast<Player*>(soldier.second);
        if (player->isDown()) {
            for (auto other_player : this->soldiers) {
                Player* close_soldier = dynamic_cast<Player*>(other_player.second);
                if (!close_soldier->isDead() && !close_soldier->isReviving() && !close_soldier->isDown()) {
                    int32_t radius = CONFIG.soldier_radius * CONFIG.soldier_max_distance_to_revive;
                    //soldier_revivie_radius_multiplier
                    if (this->gameMap.checkForReviving(soldier.first, other_player.first, radius)) {
                        player->setReviving();
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
