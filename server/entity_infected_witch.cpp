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
    has_spawned_infected(false),
    attack_duration(CONFIG.witch_infected_attack_duration),
    shout_minum_distance(CONFIG.witch_infected_shout_minimum_distance) {}

void WitchInfected::move(int32_t x_movement, int32_t y_movement) {
    if (this->state == DEAD_WITCH_INFECTED) return;
    if (this->state == ATTACKING_WITCH_INFECTED) return;
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
            return "screaming";
    }
    return "idle";
}

void WitchInfected::setChase(Entity* entity) {
    this->getDirectionOfMovement()
        ->setChase(*entity->getDirectionOfMovement(), this->speed);
    this->state = MOVING_WITCH_INFECTED;
}

void WitchInfected::checkForSoldiersInRangeAndSetAttack(std::map<uint32_t, Entity*> &soldiers) {
    if (this->state == DEAD_WITCH_INFECTED) return;
    if (this->incapacitated > 0) return;
    Infected::checkForSoldiersInRangeAndSetAttackWithRange(soldiers, this->attack_range);
}

void WitchInfected::setAttack(Entity* entity) {
    this->state = ATTACKING_WITCH_INFECTED;
    entity->setDamageForTheRound(this->attack_damage);
    this->incapacitated = attack_cooldown;
    this->attack_duration = CONFIG.witch_infected_attack_duration;
}

void WitchInfected::checkForSoldiersInRangeAndSetChase(std::map<uint32_t, Entity*> &soldiers) {
    if (this->state == DEAD_WITCH_INFECTED) return;
    if (this->incapacitated > 0) return;    
    Infected::checkForSoldiersInRangeAndSetChaseWithRange(soldiers, this->look_range);
}

void WitchInfected::makeStronger(double factor) {
    this->attack_damage *= factor;
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
    if (this->state == DEAD_WITCH_INFECTED) return;

    if (this->incapacitated > 0) {
        this->incapacitated--;
        if (attack_duration < 0 && this->state != SHOUTING_WITCH_INFECTED) {
            this->state = IDLE_WITCH_INFECTED;
            this->attack_cooldown = CONFIG.witch_infected_attack_cooldown;
        } else {
            this->attack_duration--;
        }
        return;
    }

    if (this->state == MOVING_WITCH_INFECTED) map.move(this->getId());
    
    if (rand() % 100 < this->shout_probability && !this->has_spawned_infected) {
        this->state = SHOUTING_WITCH_INFECTED;
        this->incapacitated = shout_cooldown;
    }

    if (this->state == ATTACKING_WITCH_INFECTED && incapacitated == 0) {
        this->state = IDLE_WITCH_INFECTED;
    }
}

bool WitchInfected::hasSpawnedInfected() {
    return this->has_spawned_infected;
}

void WitchInfected::setSpawnedInfected() {
    this->has_spawned_infected = true;
}

bool WitchInfected::isInDistanceForShouting(const int32_t &position_x) {
    return abs(this->getDirectionOfMovement()->getX() - position_x) < this->shout_minum_distance;
}

bool WitchInfected::isShouting() {
    return this->state == SHOUTING_WITCH_INFECTED;
}