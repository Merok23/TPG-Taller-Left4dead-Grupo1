#include "entity_infected_venom.h"

VenomInfected::VenomInfected(uint32_t id, uint32_t position_x, uint32_t position_y) :
    Infected(id, position_x, position_y, CONFIG.venom_infected_health, CONFIG.venom_infected_radius),
    state(IDLE_VENOM_INFECTED),
    look_range(CONFIG.venom_infected_look_range),
    blast_range(CONFIG.venom_infected_blast_range),
    shoot_range(CONFIG.venom_infected_shoot_range),
    blast_damage(CONFIG.venom_infected_blast_damage),
    incapacitated(0),
    speed(CONFIG.venom_infected_speed),
    blast_incapacitated_time(CONFIG.venom_infected_blast_incapacitated_time),
    shoot_incapacitated_time(CONFIG.venom_infected_shoot_incapacitated_time),
    shoot_attack_counter(0),
    shoot_attack_timing(CONFIG.venom_infected_shoot_timing),
    blast_attack_counter(0),
    blast_attack_timing(CONFIG.venom_infected_blast_damage_timing),
    blast_radius(CONFIG.venom_infected_blast_radius),
    projectile_radius(CONFIG.venom_infected_projectile_radius) {}

void VenomInfected::move(int32_t x_movement, int32_t y_movement) {
    if (this->state == DEAD_VENOM_INFECTED) return;
    this->state = MOVING_VENOM_INFECTED;
    this->getDirectionOfMovement()->setDirection(x_movement * this->speed, y_movement * this->speed);
}

void VenomInfected::update(Map &map) {
    if (this->state == DEAD_VENOM_INFECTED) return;

    Entity::resolveDamage();

    if (this->getHitPoints() <= 0) {
        this->state = DEAD_VENOM_INFECTED;
        return;
    } 

    if (this->state == BLASTING_VENOM_INFECTED) this->blast_attack_counter++;
    if (this->state == SHOOTING_VENOM_INFECTED) this->shoot_attack_counter++;
    

    if (this->incapacitated > 0) {
        this->incapacitated--;
        //if we were blasting or shooting and we finished, we reset the timing counter
        if (this->incapacitated == 0) {
            this->blast_attack_counter = 0;
            this->shoot_attack_counter = 0;
        } 
        return;
    }

    if (this->state == MOVING_VENOM_INFECTED) map.move(this->getId());
}

void VenomInfected::checkForSoldiersInRangeAndSetChase(std::map<uint32_t, Entity*> &soldiers) {
    if (this->state == DEAD_VENOM_INFECTED) return;
    if (this->incapacitated > 0) return;

    Infected::checkForSoldiersInRangeAndSetChaseWithRange(soldiers, this->look_range);
}

void VenomInfected::checkForSoldiersInRangeAndSetAttack(std::map<uint32_t, Entity*> &soldiers) {
    if (this->state == DEAD_VENOM_INFECTED) return;
    if (this->incapacitated > 0) return;

    Infected::checkForSoldiersInRangeAndSetAttackWithRange(soldiers, this->blast_range);
}

void VenomInfected::setChase(Entity* entity) {
    if (this->state == DEAD_VENOM_INFECTED) return;
    if (this->incapacitated > 0) return;

    this->state = MOVING_VENOM_INFECTED;
    this->getDirectionOfMovement()->setChase(*entity->getDirectionOfMovement(), this->speed);
}

void VenomInfected::setAttack(Entity* entity) {
    if (this->state == DEAD_VENOM_INFECTED) return;
    if (this->incapacitated > 0) return;
    if (this->state == BLASTING_VENOM_INFECTED) return;
    if (this->state == SHOOTING_VENOM_INFECTED) return;

    // we don't do the damage here, instead, we'll fire up a flag so
    // when the time is ready, the game will call us with the entities
    // hit. (we use the state and the counter for this)
    this->state = BLASTING_VENOM_INFECTED;
    this->blast_attack_counter = 0;
    this->incapacitated = this->blast_incapacitated_time;
}

void VenomInfected::setBlastDamage(std::vector<Entity*> &entities) {
    for (auto &&entity : entities) {
        entity->setDamageForTheRound(this->blast_damage);
    }
}

void VenomInfected::setShooting() {
    if (this->state == DEAD_VENOM_INFECTED) return;
    if (this->incapacitated > 0) return;
    if (this->state == BLASTING_VENOM_INFECTED) return;
    if (this->state == SHOOTING_VENOM_INFECTED) return;

    // we don't do the damage here, instead, we'll fire up a flag so
    // when the time is ready, the game will call us with the entities
    // hit. (we use the state and the counter for this)
    this->state = SHOOTING_VENOM_INFECTED;
    this->shoot_attack_counter = 0;
    this->incapacitated = this->shoot_incapacitated_time;
}

bool VenomInfected::isTimeForBlasting() {
    return this->blast_attack_counter == this->blast_attack_timing;
}

bool VenomInfected::isTimeForShooting() {
    return this->shoot_attack_counter == this->shoot_attack_timing;
}

bool VenomInfected::isShootingAProjectile() {
    return this->state == SHOOTING_VENOM_INFECTED;
}

void VenomInfected::makeStronger(double factor) {
    this->blast_damage *= factor;
    this->speed *= factor;
    this->setHitPoints(this->getHitPoints() * factor);
}

std::string VenomInfected::getEntityType() {
    return "venom";
}

std::string VenomInfected::getState() {
    switch (this->state) {
        case (IDLE_VENOM_INFECTED): {
            return "idle";
        }
        case (MOVING_VENOM_INFECTED): {
            return "moving";
        }
        case (BLASTING_VENOM_INFECTED): {
            return "blasting";
        }        
        case (SHOOTING_VENOM_INFECTED): {
            return "shooting";
        }
        case (DEAD_VENOM_INFECTED): {
            return "dead";
        }
        default:
            return "idle";
    }
}

int32_t VenomInfected::getShootingRange() {
    return this->shoot_range;
}

Movement VenomInfected::getBlastPosition() {
    uint32_t x;
    if (this->getDirectionOfMovement()->isFacingLeft()) {
        x = this->getDirectionOfMovement()->getX() - this->blast_radius;
    } else {
        x = this->getDirectionOfMovement()->getX() + this->blast_radius;
    }
    return (Movement(x, this->getDirectionOfMovement()->getY(), this->blast_radius));
}

std::tuple<uint32_t, uint32_t> VenomInfected::getProjectilePosition() {
    uint32_t x;
    if (this->getDirectionOfMovement()->isFacingLeft()) {
        x = this->getDirectionOfMovement()->getX() - this->projectile_radius;
    } else {
        x = this->getDirectionOfMovement()->getX() + this->projectile_radius;
    }
    return std::make_tuple(x, this->getDirectionOfMovement()->getY());
}

bool VenomInfected::isDead() {
    return this->state == DEAD_VENOM_INFECTED;
}

