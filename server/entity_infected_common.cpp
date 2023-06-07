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
    speed(CONFIG.common_infected_speed) {}

void CommonInfected::update(Map& map) {
    if (this->state == DEAD_INFECTED) return;
    
    Entity::resolveDamage(); 
    
    if (this->getHitPoints() <= 0) this->state = DEAD_INFECTED; 
    
    if (this->incapacitated > 0) {
        this->incapacitated--;
        return;
    }
    
    if (this->state == MOVING_INFECTED) {
        map.move(this->getId());
    }
}

bool CommonInfected::isDead() {
    return (this->state == DEAD_INFECTED);
}

void CommonInfected::move(int32_t x_movement, int32_t y_movement) {
    if (this->state == DEAD_INFECTED) return; 
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
    this->attack_range *= factor;
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
    std::map<uint32_t, Entity*> alive_soldiers = Infected::filterDeadSoldiers(soldiers);
    //TODO: make a random pick of the soldier, not always the first one
    auto iterator = std::find_if(alive_soldiers.begin(), 
        alive_soldiers.end(), [this](std::pair<uint32_t, Entity*> alive_soldiers) {
        return Infected::isInRange(alive_soldiers.second, this->attack_range);
    });
    if (iterator != alive_soldiers.end()) {
        this->state = ATTACKING_INFECTED;
        iterator->second->setDamageForTheRound(this->attack_damage);
        this->incapacitated = attack_cooldown;
    }
}

void CommonInfected::checkForSoldiersInRangeAndSetChase(std::map<u_int32_t, Entity*> &soldiers) {
    //this shouldn't happen since when it's dead its removed from the game
    //but it's here for a border case where it was killed before chasing
    if (this->state == DEAD_INFECTED) return;
    if (this->incapacitated > 0) return;
    std::map<uint32_t, Entity*> alive_soldiers = Infected::filterDeadSoldiers(soldiers);
    auto iterator = std::find_if(alive_soldiers.begin(), 
        alive_soldiers.end(), [this](std::pair<uint32_t, Entity*> alive_soldiers) {
        return Infected::isInRange(alive_soldiers.second, this->look_range);
    });
    //aca falta agregar un factor random.
    if (iterator != alive_soldiers.end()) {
        this->setChase(iterator->second);
    }
}
