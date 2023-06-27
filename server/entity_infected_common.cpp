#include <utility>
#include <map>

#include "entity_infected_common.h"

CommonInfected::CommonInfected(uint32_t id, uint32_t positionX, uint32_t positionY) : 
    Infected(id, positionX, positionY, CONFIG.infected_health, CONFIG.common_infected_radius),
    state(IDLE_INFECTED),
    look_range(CONFIG.common_infected_range),
    attack_range(CONFIG.common_infected_attack_range),
    attack_cooldown(CONFIG.common_infected_attack_cooldown),
    attack_damage(CONFIG.common_infected_damage),
    incapacitated(0),
    speed(CONFIG.common_infected_speed),
    attack_duration(CONFIG.common_infected_attack_duration) {}

void CommonInfected::update(Map& map) {
    if (this->state == DEAD_INFECTED) return;
    
    Entity::resolveDamage(); 
    
    if (this->getHitPoints() <= 0) this->state = DEAD_INFECTED; 
    if (this->state == DEAD_INFECTED) return; //we could move the first check down here
    
    if (this->incapacitated > 0) {
        this->incapacitated--;
        if (this->attack_duration < 0) {
            this->state = IDLE_INFECTED; //we reset the animation
            this->attack_duration = CONFIG.common_infected_attack_duration;
        } else {
            this->attack_duration--;
        }
        return;
    }
    
    if (this->state == MOVING_INFECTED) map.move(this->getId());
}

bool CommonInfected::isDead() {
    return (this->state == DEAD_INFECTED);
}

void CommonInfected::move(int32_t x_movement, int32_t y_movement) {
    if (this->state == DEAD_INFECTED) return; 
    if (this->state == ATTACKING_INFECTED) return;
    this->state = MOVING_INFECTED;
    this->getDirectionOfMovement()->setDirection(x_movement * this->speed,
        y_movement * this->speed);
}

void CommonInfected::setChase(Entity* entity) {
    this->getDirectionOfMovement()->setChase(*entity->getDirectionOfMovement(), 
        this->speed);
    this->state = MOVING_INFECTED;
}


void CommonInfected::makeStronger(double factor) {
    this->attack_damage *= factor;
    this->look_range *= factor;
    this->speed *= factor;
    int32_t hit_points = this->getHitPoints();
    hit_points *= factor;
    this->setHitPoints(hit_points);
}

std::string CommonInfected::getState() {
    if (this->state == IDLE_INFECTED) return "idle";
    if (this->state == MOVING_INFECTED) return "moving";
    if (this->state == ATTACKING_INFECTED) return "attacking";
    return "dead";
}

std::string CommonInfected::getEntityType() {
    return "common_infected";
}

void CommonInfected::checkForSoldiersInRangeAndSetAttack(std::map<u_int32_t, Entity*> &soldiers) {
    if (this->state == DEAD_INFECTED) return;
    if (this->incapacitated > 0) return;
    
    Infected::checkForSoldiersInRangeAndSetAttackWithRange(soldiers, this->attack_range);
}

void CommonInfected::setAttack(Entity* entity) {
    this->state = ATTACKING_INFECTED;
    entity->setDamageForTheRound(this->attack_damage);
    this->incapacitated = attack_cooldown;
    this->attack_duration = CONFIG.common_infected_attack_duration;
}

void CommonInfected::checkForSoldiersInRangeAndSetChase(std::map<u_int32_t, Entity*> &soldiers) {
    //this shouldn't happen since when it's dead its removed from the game
    //but it's here for a border case where it was killed before chasing
    if (this->state == DEAD_INFECTED) return;
    if (this->incapacitated > 0) return;
    
    Infected::checkForSoldiersInRangeAndSetChaseWithRange(soldiers, this->look_range);
}

void CommonInfected::setFollowWitch(Entity* witch) {
    this->getDirectionOfMovement()->setChase(*witch->getDirectionOfMovement(), 
        this->speed);
    this->state = MOVING_INFECTED;
}
