#include <utility>
#include <map>

#include "entity_infected_common.h"

CommonInfected::CommonInfected(uint32_t id, uint32_t positionX, uint32_t positionY) : 
    Infected(id, positionX, positionY, CONFIG.infected_health),
    state(IDLE_INFECTED),
    look_range(CONFIG.common_infected_range),
    attack_range(CONFIG.common_infected_attack_range),
    attack_cooldown(CONFIG.common_infected_attack_cooldown),
    attack_damage(CONFIG.common_infected_damage),
    incapacitated(0),
    speed(CONFIG.common_infected_speed) {}

void CommonInfected::checkForSoldiersInRangeAndSetChase(std::map<u_int32_t, Entity*> &soldiers) {
    //this shouldn't happen since when it's dead its removed from the game
    //but it's here for a border case where it was killed before chasing
    if (this->state == DEAD_INFECTED) return;
    if (this->incapacitated > 0) return;
    auto iterator = std::find_if(soldiers.begin(), 
        soldiers.end(), [this](std::pair<uint32_t, Entity*> soldier) {
        return this->isInRange(soldier.second, this->look_range);
    });
    //aca falta agregar un factor random.
    if (iterator != soldiers.end()) {
        this->setChase(iterator->second);
    }
}

void CommonInfected::update(Map& map) {
    if (this->state == DEAD_INFECTED) return;
    this->resolveDamage(); 
    if (this->getHitPoints() <= 0) this->state = DEAD_INFECTED; 
    if (this->incapacitated > 0) {
        this->incapacitated--;
        return;
    }
    if (this->state == MOVING_INFECTED) {
        map.move(this->getId());
    }
}

void CommonInfected::resolveDamage() {
    int32_t hit_points = this->getHitPoints();
    hit_points -= this->getDamageForTheRound();
    this->setHitPoints(hit_points);
    this->resetDamageForTheRound();
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

bool CommonInfected::isInRange(Entity* entity,const int32_t &range) {
    bool in_range = false;
    int32_t soldier_x = entity->getDirectionOfMovement()->getX();
    int32_t infected_x = this->getDirectionOfMovement()->getX();
    //careful, this can return false, so if you have to add 
    //other condition before this, check for if (!is_in_range)
    in_range = checkForBorderCaseRange(soldier_x, infected_x, range);
    int32_t distance = 
        this->getDirectionOfMovement()->calculateDistance(*entity->getDirectionOfMovement());
    if (distance <= range) in_range = true;
    return (in_range);
}

void CommonInfected::setChase(Entity* entity) {
    this->getDirectionOfMovement()->setChase(*entity->getDirectionOfMovement(), 
        this->speed);
    this->state = MOVING_INFECTED;
}

bool CommonInfected::checkForBorderCaseRange(const int32_t &soldier_x,const int32_t &infected_x,const int32_t &range) {
    //soldier is on the end of the map and infected on the start
    if (soldier_x + range > CONFIG.scenario_width) {
        return ((soldier_x - infected_x - CONFIG.scenario_width) 
            < range);
    }
    //infected is on the end of the map and soldier on the start
    return (((soldier_x + CONFIG.scenario_width - infected_x) < range) 
        && (infected_x + range > CONFIG.scenario_width));
}

void CommonInfected::checkForSoldiersInRangeAndSetAttack(std::map<u_int32_t, Entity*> &soldiers) {
    if (this->state == DEAD_INFECTED) return;
    if (this->incapacitated > 0) return;
    //TODO: make a random pick of the soldier, not always the first one
    auto iterator = std::find_if(soldiers.begin(), 
        soldiers.end(), [this](std::pair<uint32_t, Entity*> soldier) {
        return this->isInRange(soldier.second, this->attack_range);
    });
    if (iterator != soldiers.end()) {
        this->state = ATTACKING_INFECTED;
        iterator->second->setDamageForTheRound(this->attack_damage);
        this->incapacitated = attack_cooldown;
    }
}


std::string CommonInfected::getState() {
    if (this->state == IDLE_INFECTED) return "idle";
    if (this->state == MOVING_INFECTED) return "moving";
    return "dead";
}

std::string CommonInfected::getEntityType() {
    return "common_infected";
}
