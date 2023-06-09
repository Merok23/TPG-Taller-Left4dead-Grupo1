#include "game.h"

Game::Game(int32_t width, int32_t height) : 
    entities(),
    gameMap(width,height),
    infected(),
    soldiers(),
    witches(),
    venoms(),
    projectiles(),
    shooting_soldiers(),
    clear_the_zone(false),
    zone_is_set(false),
    clear_the_zone_max_infected(CONFIG.clear_the_zone_infected_total),
    survival_mode(false),
    survival_mode_counter(CONFIG.survival_mode_timer),
    max_common_infected_per_spawn(CONFIG.survival_mode_max_common_infected),
    max_spear_infected_per_spawn(CONFIG.survival_mode_max_spear_infected),
    max_witch_infected_per_spawn(CONFIG.survival_mode_max_witch_infected),
    max_venom_infected_per_spawn(CONFIG.survival_mode_max_venom_infected),
    max_jumper_infected_per_spawn(CONFIG.survival_mode_max_jumper_infected),
    survival_mode_multiplier(CONFIG.survival_mode_starting_multiplier),
    current_id(0),
    game_started(false),
    game_over(false),
    players_won(false),
    craters_have_spawned(false),
    rng(std::random_device()()),
    dist(0, 2147482600) {}

Game::Game(int32_t width, int32_t height, GameMode gameMode) : 
    entities(),
    gameMap(width,height),
    infected(),
    soldiers(),
    witches(),
    venoms(),
    projectiles(),
    shooting_soldiers(),
    clear_the_zone(gameMode == GameMode::CLEAR_THE_ZONE),
    zone_is_set(false),
    clear_the_zone_max_infected(CONFIG.clear_the_zone_infected_total),
    survival_mode(gameMode == GameMode::SURVIVAL),
    survival_mode_counter(CONFIG.survival_mode_timer),
    max_common_infected_per_spawn(CONFIG.survival_mode_max_common_infected),
    max_spear_infected_per_spawn(CONFIG.survival_mode_max_spear_infected),
    max_witch_infected_per_spawn(CONFIG.survival_mode_max_witch_infected),
    max_venom_infected_per_spawn(CONFIG.survival_mode_max_venom_infected),
    max_jumper_infected_per_spawn(CONFIG.survival_mode_max_jumper_infected),
    survival_mode_multiplier(CONFIG.survival_mode_starting_multiplier),
    current_id(0),
    game_started(false),
    game_over(false),
    players_won(false),
    craters_have_spawned(false),
    rng(std::random_device()()),
    dist(0, 2147482600) {}

void Game::addEntity(Entity* entity) {
    //TODO: if ID already exists, throw exception
    this->entities[entity->getId()] = entity;
    this->gameMap.addEntity(entity->getId(), entity->getDirectionOfMovement());
    if (entity->isInfected()) {
        this->infected[entity->getId()] = entity;
        if (entity->getEntityType() == "witch") {
            this->witches[entity->getId()] = dynamic_cast<WitchInfected*>(entity);
        }
        if (entity->getEntityType() == "venom" ) {
            this->venoms[entity->getId()] = dynamic_cast<VenomInfected*>(entity);
        }
    } else if (entity->isSoldier()){
        this->soldiers[entity->getId()] = entity;
        this->gameMap.addSoldier(entity->getId(), entity->getDirectionOfMovement());
        this->game_started = true;
    }
    this->current_id++;
}

uint32_t Game::addPlayer(Weapon* weapon) {
    std::tuple<int, int> spawn = this->getPlayerSpawnPoint();
    uint32_t player_id = this->getCurrentId();
    Player* player = new Player(player_id, std::get<0>(spawn), std::get<1>(spawn), weapon);
    this->addEntity(player);
    return player_id;
}

uint32_t Game::getCurrentId() {
    return this->current_id;
}

std::tuple<int, int> Game::getPlayerSpawnPoint() {
    if (this->clear_the_zone && !this->game_started) return this->gameMap.getClearTheZoneSpawnPoint(CONFIG.soldier_radius);
    //this->survival is removed so testing has the same spawn point
    //if I don't do this, when calculating the centre of mass soldiers.size() is 0
    //the fix is adding a this->testing_mode and checking for it here
    if (!this->game_started) return this->gameMap.getSurvivalModeSpawnPoint(CONFIG.soldier_radius);
    return this->gameMap.getCentreOfMassSpawnPoint(CONFIG.soldier_radius);
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
        case Cheat::INFINITE_HITPOINTS: {
            Player* soldier = dynamic_cast<Player*>(this->entities[id]);
            soldier->setInfiniteHitpoints();
            break;
        }
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

std::map<uint32_t, Entity*>& Game::getEntities() {
    return this->entities;
}

std::shared_ptr<GameStateForClient> Game::update() {
    //--------------------GAME OVER--------------------//
    if (this->game_over) return std::make_shared<GameStateForClient>(this->entities, 
        this->game_over,
        this->players_won); 
    //-------------------------------------------------//
    
    if (!this->craters_have_spawned && (this->survival_mode || this->clear_the_zone)) spawnCraters(CONFIG.crater_amount);
    if (this->survival_mode) survivalUpdate();
    if (this->clear_the_zone && !this->zone_is_set) setTheZone();
    this->checkForRevivingSoldiers();
    this->checkForShooting();
    this->infectedCheckForAttackAndChase();
    this->checkForScreamingWitches();
    this->checkForCollidingProjectiles(); //venom's projectiles
    this->checkForBlastingVenoms();
    this->checkForShootingVenoms();
    this->updateAllEntities();
    //this->removeDeadProjectiles();
    this->checkForGameOver();
    std::shared_ptr<GameStateForClient> game_state = 
        std::make_shared<GameStateForClient>(this->entities, 
            this->game_over,
            this->players_won);
    return game_state;
}

void Game::infectedCheckForAttackAndChase() {
    std::map<uint32_t, Entity*> alive_soldiers = this->getAliveSoldiers();
    this->infectedCheckForSoldiersInRange(alive_soldiers);
    this->checkForInfectedAttack(alive_soldiers);
}

std::map<uint32_t, Entity*> Game::getAliveSoldiers() {
    std::map<uint32_t, Entity*> alive_soldiers;
    for (auto& id_entity : this->soldiers) {
        if (!id_entity.second->isDead()) {
            alive_soldiers[id_entity.first] = id_entity.second;
        }
    }
    return alive_soldiers;
}

void Game::checkForInfectedAttack(std::map<uint32_t, Entity*> &alive_soldiers) {
    for (auto&& id_entity : this->infected) {
        Infected* infected = dynamic_cast<Infected*>(id_entity.second);
        infected->checkForSoldiersInRangeAndSetAttack(alive_soldiers);
    }
}


void Game::infectedCheckForSoldiersInRange(std::map<uint32_t, Entity*> &alive_soldiers) {
    for (auto& id_entity : this->infected) {
        if (id_entity.second->isInfected()) {
            Infected* infected = dynamic_cast<Infected*>(id_entity.second);
            infected->checkForSoldiersInRangeAndSetChase(alive_soldiers);
        }
    }
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

void Game::spawnWitchInfectedFromScream(const uint32_t &id) {
    this->witches[id]->setSpawnedInfected();
    for (int i = 0; i < CONFIG.witch_infected_scream_spawn_amount; i++) {
        uint32_t x = 0;
        uint32_t y = 0;
        if (searchForPositionCloseToCentreOfMass(CONFIG.common_infected_radius, x, y)) {
            Entity* infected = new CommonInfected(current_id, x, y);
            this->addEntity(infected);
            CommonInfected* common = dynamic_cast<CommonInfected*>(infected);
            common->setFollowWitch(this->entities[id]);
        }
    }
}

bool Game::searchForPositionCloseToCentreOfMass(const uint32_t &radius, uint32_t &x, uint32_t &y) {
    bool found = false;
    int32_t x_min = this->gameMap.getCentreOfMass() - (1.3 * CONFIG.soldier_max_distance_from_mass_centre);
    if (x_min < 0) x_min = CONFIG.spawn_point_start_x_infected;
    uint32_t x_max = this->gameMap.getCentreOfMass() + (1.3 * CONFIG.soldier_max_distance_from_mass_centre);
    if (x_max > this->gameMap.getWidth()) x_max =CONFIG.spawn_point_end_x_infected;
    int32_t mod_y = this->gameMap.getHeight() - 2 * radius;
    while (!found) {
        y = this->dist(rng) % mod_y;
        y += radius;
        if (this->dist(rng) % 2) {
            found = !this->gameMap.checkForCollisionInPosition(x_min, y, radius);
            x = x_min;
        } else {
            found = !this->gameMap.checkForCollisionInPosition(x_max, y, radius);
            x = x_max;
        } 
        if (!found) {
            x_min += radius;
            x_max -= radius;
        }
    }
    return found;
}

void Game::checkForScreamingWitches() {
    for (auto&& witch : this->witches) {
        if (witch.second->isShouting() && 
            !witch.second->hasSpawnedInfected() && 
            witch.second->isInDistanceForShouting(this->gameMap.getCentreOfMass())) {
                this->spawnWitchInfectedFromScream(witch.first);
        } 
    }
}

void Game::checkForCollidingProjectiles() {
    std::map<uint32_t, Entity*> alive_soldiers = this->getAliveSoldiers();
    for (auto&& projectile : this->projectiles) {
        for (auto&& soldier : alive_soldiers) {
            if (projectile.second->getDirectionOfMovement()->checkForCollision(*soldier.second->getDirectionOfMovement())) {
                projectile.second->setImpact(soldier.second);
            }
        }
    }
}

void Game::checkForBlastingVenoms() {
    for (auto&& venom : this->venoms) {
        if (venom.second->isTimeForBlasting()) this->setBlastVenom(venom.first);
    }
}

void Game::setBlastVenom(const uint32_t &id) {
    std::vector<Entity*> hit_soldiers;
    std::map<uint32_t, Entity*> alive_soldiers = this->getAliveSoldiers();

    Movement blast_mov = this->venoms[id]->getBlastPosition();
    for (auto&& soldier : alive_soldiers) {
        if (soldier.second->getDirectionOfMovement()->checkForCollision(blast_mov)) {
            hit_soldiers.push_back(soldier.second);
        }
    }

    this->venoms[id]->setBlastDamage(hit_soldiers);
}

void Game::checkForShootingVenoms () {
    for (auto&& venom : this->venoms) {
        std::map<uint32_t, Entity*> alive_soldiers = this->getAliveSoldiers();
        for (auto&& soldier : alive_soldiers) {
            if (this->gameMap.isEntityLookingAtAllignedAndInRange(venom.first, soldier.first, venom.second->getShootingRange())) {
                venom.second->setShooting();
            }
        }
    }

    for (auto&& venom : this->venoms) {
        if (venom.second->isTimeForShooting()) this->createVenomProjectile(venom.second);
    }
}

void Game::createVenomProjectile(VenomInfected* venom) {
    std::tuple<uint32_t, uint32_t> pos = venom->getProjectilePosition();
    Projectile* venom_projectile = new VenomProjectile(current_id, std::get<0>(pos), std::get<1>(pos));
    if (venom->getDirectionOfMovement()->isFacingLeft()) {
        venom_projectile->move(-1, 0);
    } else {
        venom_projectile->move(1, 0);
    }
    this->addProjectile(venom_projectile);
}

void Game::addProjectile(Projectile* entity) {
    this->entities[current_id] = entity;
    this->projectiles[current_id] = entity;
    this->current_id++;
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
    //no problem for these since no one is iterating them
    this->infected.erase(id);
    this->venoms.erase(id);
    this->witches.erase(id);
    //hack for now:
    this->projectiles.erase(id);
    //projectiles are removed after iterating everthing game.update
}
/*
void Game::removeDeadProjectiles() {
    std::vector<uint32_t> dead_projectiles;
    for (auto it = projectiles.begin(); it != projectiles.end(); ++it) {
        if (it->second->isDead()) {
            dead_projectiles.push_back(it->first);
        }
    }
    
    for (auto id : dead_projectiles) {
        delete entities[id];
        entities.erase(id);
        projectiles.erase(id);
    }
}
*/


void Game::setTheZone() {
    this->zone_is_set = true;
    this->spawnSpecificInfectedAtEnd(InfectedType::COMMON, CONFIG.common_infected_zone_percentage * this->clear_the_zone_max_infected);
    this->spawnSpecificInfectedAtEnd(InfectedType::SPEAR, CONFIG.spear_infected_zone_percentage * this->clear_the_zone_max_infected);
    this->spawnSpecificInfectedAtEnd(InfectedType::WITCH, CONFIG.witch_infected_zone_percentage * this->clear_the_zone_max_infected);
    //this->spawnSpecificInfected(InfectedType::JUMPER, CONFIG.jumper_infected_zone_percentage * this->clear_the_zone_max_infected);
    this->spawnSpecificInfectedAtEnd(InfectedType::VENOM, CONFIG.venom_infected_zone_percentage * this->clear_the_zone_max_infected);
}

void Game::spawnSpecificInfectedAtEnd(const InfectedType &type, const int &amount) {
    int32_t radius = typeToRadius(type);
    for (int i = 0; i < amount; i++) {
        uint32_t x = 0;
        uint32_t y = 0;
        if (searchForPositionAtEnd(radius, x, y)) {
            //id is not a problem (race condition) since there is no 
            //other thread calling for addEntity in the game update
            Entity* entity = createInfected(type, this->current_id, x, y);
            this->addEntity(entity);
            Infected* infected = dynamic_cast<Infected*>(entity);
            infected->moveToMiddle();
        }
    }
}

void Game::spawnSpecificInfected(const InfectedType &type,const int &amount) {
    int32_t radius = typeToRadius(type);
    for (int i = 0; i < amount; i++) {
        uint32_t x = 0;
        uint32_t y = 0;
        if (searchForPositionAtBorders(radius, x, y)) {
            //id is not a problem (race condition) since there is no 
            //other thread calling for addEntity in the game update
            Entity* entity = createInfected(type, this->current_id, x, y);
            this->addEntity(entity);
            Infected* infected = dynamic_cast<Infected*>(entity);
            infected->moveToMiddle();
        }
    }
}

Entity* Game::createInfected(
    const InfectedType &type, 
    const uint32_t &id, 
    const uint32_t &x, 
    const uint32_t &y) {
    switch(type) {
        case COMMON:
            return new CommonInfected(id, x, y);
        case SPEAR:
            return new SpearInfected(id, x, y);
        case WITCH:
            return new WitchInfected(id, x, y);
        /*
        case JUMPER:
            return new JumperInfected(id, x, y);
        */
        case VENOM:
            return new VenomInfected(id, x, y);
        default:
            throw std::runtime_error("Invalid infected type");
    }
}

int32_t Game::typeToRadius(const InfectedType &type) {
    switch(type) {
        case COMMON:
            return CONFIG.common_infected_radius;
        case SPEAR:
            return CONFIG.spear_infected_radius;
        case WITCH:
            return CONFIG.witch_infected_radius;
        /*
        case JUMPER:
            return CONFIG.jumper_infected_radius;
        */
        case VENOM:
            return CONFIG.venom_infected_radius;
        default:
            throw std::runtime_error("Invalid infected type");
    }
}

void Game::survivalUpdate() {
    this->survival_mode_counter--;
    if (this->survival_mode_counter != 0) return;
    this->survival_mode_counter = CONFIG.survival_mode_timer;
    this->spawnInfected();
    this->makeInfectedStronger();
    if (survival_mode_multiplier < 1.1) survival_mode_multiplier *= CONFIG.survival_mode_accumulator;
    max_common_infected_per_spawn *= CONFIG.survival_mode_accumulator;
    max_spear_infected_per_spawn *= CONFIG.survival_mode_accumulator;
}

//Replace for factory design for uniting all of these.
void Game::spawnCraters(int amount) {
    this->craters_have_spawned = true;
    for (int i = 0; i < amount; i++) {
        uint32_t x = 0;
        uint32_t y = 0;
        if (searchForPositionAnywhere(CONFIG.crater_radius, x, y)) {
            Entity* crater = new Crater(current_id, x, y);
            this->addEntity(crater);
        }
    }
    this->spawnCratersAtTheBorder();
}

bool Game::searchForPositionAnywhere(const uint32_t& radius, uint32_t& x, uint32_t& y) {
    bool found = false;
    int mod_y = this->gameMap.getHeight() - 2 * radius;
    while (!found) {
        x = this->dist(rng) % this->gameMap.getWidth();
        y = this->dist(rng) % mod_y;
        y += radius;
        found = !this->gameMap.checkForCollisionInPosition(x, y, radius);
    }
    return found;
}

void Game::spawnCratersAtTheBorder() {
    uint32_t y = CONFIG.crater_radius;
    while (y <= this->gameMap.getHeight()) {
        Entity* crater = new Crater(current_id, CONFIG.crater_radius, y);
        this->addEntity(crater);
        crater = new Crater(current_id, this->gameMap.getWidth() - CONFIG.crater_radius, y);
        this->addEntity(crater);
        y += CONFIG.crater_radius;
    }
}


bool Game::searchForPositionAtBorders(const uint32_t& radius, uint32_t& x, uint32_t& y) {
    bool found = false;
    int mod_y = this->gameMap.getHeight() - 2 * radius;
    //start and end it's for when the spawn point is full
    //so it doesn't loop infinitely when the border is full
    int start = CONFIG.spawn_point_start_x_infected;
    int end = CONFIG.spawn_point_end_x_infected;
    while (!found) {
        y = this->dist(rng) % mod_y;
        y += radius;
        //50% chance of spawning in the left or right side of the map
        if (this->dist(rng) % 2 || !this->clear_the_zone) {
            if (!this->gameMap.checkForCollisionInPosition(start, y, radius)) {
                found = true;
                x = start;
            }
            start += radius;
        } else {
            if (!this->gameMap.checkForCollisionInPosition(end, y, radius)) {
                found = true;
                x = end;
            }
            end-= radius;
        }
        if (this->clear_the_zone) {
            if (!this->gameMap.checkForCollisionInPosition(end, y, radius)) {
                found = true;
                x = end;
            }
            end-= radius;
        }
    }
    return found;
}

bool Game::searchForPositionAtEnd(const uint32_t& radius, uint32_t& x, uint32_t& y) {
    bool found = false;
    int mod_y = this->gameMap.getHeight() - 2 * radius;
    int end = CONFIG.spawn_point_end_x_infected;
    while (!found) {
        y = this->dist(rng) % mod_y;
        y += radius;
        if (!this->gameMap.checkForCollisionInPosition(end, y, radius)) {
            found = true;
            x = end;
        }
        end-= radius;
    }
    return found;
}


void Game::spawnInfected() {
    //this could be done with a factory pattern
    this->spawnSpecificInfected(InfectedType::COMMON, this->dist(rng) % this->max_common_infected_per_spawn + 1);
    this->spawnSpecificInfected(InfectedType::SPEAR, this->dist(rng) % this->max_spear_infected_per_spawn + 1);
    this->spawnSpecificInfected(InfectedType::WITCH, this->dist(rng) % this->max_witch_infected_per_spawn + 1);
    //this->spawnSpecificInfected(InfectedType::JUMPER, this->dist(rng) % this->max_jumper_infected_per_spawn + 1);
    this->spawnSpecificInfected(InfectedType::VENOM, this->dist(rng) % this->max_venom_infected_per_spawn + 1);
    
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

uint32_t Game::getAmountOfAmmoUsedBySoldier(const uint32_t &id) {
    Player* player = dynamic_cast<Player*>(this->entities[id]);
    return player->getAmmountOfAmmoUsed();
}

uint32_t Game::getAmountOfInfectedKilledBySoldier(const uint32_t &id) {
    Player* player = dynamic_cast<Player*>(this->entities[id]);
    return player->getAmmountOfInfectedKilled();
}

uint32_t Game::getTimeOfDeathOfSoldier(const uint32_t &id) {
    Player* player = dynamic_cast<Player*>(this->entities[id]);
    return player->getTimeOfDeath();
}

Game::~Game() {
    for (auto& id_entity : this->entities) {
        delete id_entity.second;
    }
}
