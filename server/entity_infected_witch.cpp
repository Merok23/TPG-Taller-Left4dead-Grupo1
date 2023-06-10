#include "entity_infected_witch.h"

WitchInfected::WitchInfected(uint32_t id, uint32_t positionX, uint32_t positionY) : 
    Infected(id, positionX, positionY, CONFIG.witch_infected_health, CONFIG.witch_infected_radius),
    state(IDLE_WITCH_INFECTED),
    look_range(CONFIG.witch_infected_look_range),
    attack_range(CONFIG.witch_infected_attack_range), 
    attack_cooldown(CONFIG.witch_infected_attack_cooldown), 
    attack_damage(CONFIG.witch_infected_attack_damage),
    incapacitated(0),
    speed(CONFIG.witch_infected_speed),
    shout_cooldown(CONFIG.witch_infected_shout_cooldown),
    shout_probability(CONFIG.witch_infected_shout_probability),
    has_spawned_infected(false) {}

void WitchInfected::move(int32_t x_movement, int32_t y_movement) {
    if (this->state == DEAD_WITCH_INFECTED) return;
    this->state = MOVING_WITCH_INFECTED;
    this->getDirectionOfMovement()
        ->setDirection(x_movement * this->speed, y_movement * this->speed);
}

bool WitchInfected::isDead() {
    return this->state == DEAD_WITCH_INFECTED;
}

std::string WitchInfected::getEntityType() {
    return "witch";
}

std::string WitchInfected::getState() {
    switch(this->state) {
        case IDLE_WITCH_INFECTED:
            return "idle";
        case MOVING_WITCH_INFECTED:
            return "moving";
        case DEAD_WITCH_INFECTED:
            return "dead";
        case ATTACKING_WITCH_INFECTED:
            return "attacking";
        case SHOUTING_WITCH_INFECTED:
            return "shouting";
    }
    return "idle";
}

void WitchInfected::setChase(Entity* entity) {
    this->getDirectionOfMovement()
        ->setChase(*entity->getDirectionOfMovement(), this->speed);
}

void WitchInfected::checkForSoldiersInRangeAndSetAttack(std::map<uint32_t, Entity*> &soldiers) {
    if (this->state == DEAD_WITCH_INFECTED) return;
    if (this->incapacitated > 0) return;
    
    std::map<uint32_t, Entity*> alive_soldiers = Infected::filterDeadSoldiers(soldiers);

    auto iterator = std::find_if(alive_soldiers.begin(), 
        alive_soldiers.end(), [this](std::pair<uint32_t, Entity*> alive_soldiers) {
        return Infected::isInRange(alive_soldiers.second, this->attack_range);
    });

    if (iterator != alive_soldiers.end()) {
        this->state = ATTACKING_WITCH_INFECTED;
        iterator->second->setDamageForTheRound(this->attack_damage);
        this->incapacitated = attack_cooldown;
    }
}

void WitchInfected::checkForSoldiersInRangeAndSetChase(std::map<uint32_t, Entity*> &soldiers) {
    if (this->state == DEAD_WITCH_INFECTED) return;
    if (this->incapacitated > 0) return;
    
    std::map<uint32_t, Entity*> alive_soldiers = Infected::filterDeadSoldiers(soldiers);

    auto iterator = std::find_if(alive_soldiers.begin(), 
        alive_soldiers.end(), [this](std::pair<uint32_t, Entity*> alive_soldiers) {
        return Infected::isInRange(alive_soldiers.second, this->look_range);
    });

    if (iterator != alive_soldiers.end()) {
        this->setChase(iterator->second);
    }
}

void WitchInfected::makeStronger(double factor) {
    this->attack_damage *= factor;
    this->attack_range *= factor;
    this->look_range *= factor;
    this->speed *= factor;
    int32_t hit_points = this->getHitPoints();
    hit_points *= factor;
    this->setHitPoints(hit_points);
}

void WitchInfected::update(Map &map) {
    if (this->state == DEAD_WITCH_INFECTED) return;

    Entity::resolveDamage();

    if (this->getHitPoints() <= 0) this->state = DEAD_WITCH_INFECTED;

    if (this->incapacitated > 0) {
        this->incapacitated--;
        return;
    }

    if (this->state == MOVING_WITCH_INFECTED) map.move(this->getId());
    
    if (rand() % 100 < this->shout_probability && !this->has_spawned_infected) {
        this->state = SHOUTING_WITCH_INFECTED;
        this->incapacitated = shout_cooldown;
    }
}

bool WitchInfected::hasSpawnedInfected() {
    return this->has_spawned_infected;
}

void WitchInfected::setSpawnedInfected() {
    this->has_spawned_infected = true;
}

bool WitchInfected::isShouting() {
    return this->state == SHOUTING_WITCH_INFECTED;
}