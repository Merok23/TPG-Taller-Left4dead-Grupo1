#include <utility>
#include <map>

#include "entity_infected_common.h"

CommonInfected::CommonInfected(uint32_t id, uint32_t positionX, uint32_t positionY) : 
    Infected(id, positionX, positionY, CONFIG.infected_health),
    state(IDLE_INFECTED) {}

void CommonInfected::checkForSoldiersInRangeAndSetChase(std::map<u_int32_t, Entity*> &soldiers) {
    auto iterator = std::find_if(soldiers.begin(), 
        soldiers.end(), [this](std::pair<uint32_t, Entity*> soldier) {
        return this->isInRange(soldier.second);
    });
    //aca falta agregar un factor random.
    if (iterator != soldiers.end()) {
        this->setChase(iterator->second);
    }
}

void CommonInfected::update(Map& map) {
    if (this->state == MOVING_INFECTED) {
        map.move(this->getId());
    }
    int32_t hit_points = this->getHitPoints();
    hit_points -= this->getDamageForTheRound();
    this->setHitPoints(hit_points);
    this->setDamageForTheRound(0);
}

void CommonInfected::move(int32_t x_movement, int32_t y_movement) {
    this->state = MOVING_INFECTED;
    this->getDirectionOfMovement()->setDirection(x_movement * CONFIG.infected_speed,
        y_movement * CONFIG.infected_speed);
}

bool CommonInfected::isInRange(Entity* entity) {
    bool in_range = false;
    int32_t soldier_x = entity->getDirectionOfMovement()->getX();
    int32_t infected_x = this->getDirectionOfMovement()->getX();
    //careful, this can return false, so if you have to add 
    //other condition before this, check for if (!is_in_range)
    in_range = checkForBorderCaseRange(soldier_x, infected_x);
    int32_t distance = 
        this->getDirectionOfMovement()->calculateDistance(*entity->getDirectionOfMovement());
    if (distance < CONFIG.common_infected_range) in_range = true;
    return (in_range);
}

void CommonInfected::setChase(Entity* entity) {
    this->getDirectionOfMovement()->setChase(*entity->getDirectionOfMovement(), 
        CONFIG.common_infected_speed);
    this->state = MOVING_INFECTED;
}

bool CommonInfected::checkForBorderCaseRange(int32_t soldier_x, int32_t infected_x) {
    //soldier is on the end of the map and infected on the start
    if (soldier_x + CONFIG.common_infected_range > CONFIG.scenario_width) {
        return ((soldier_x - infected_x - CONFIG.scenario_width) 
            < CONFIG.common_infected_range);
    }
    //infected is on the end of the map and soldier on the start
    return (((infected_x - soldier_x - CONFIG.scenario_width) < CONFIG.common_infected_range) 
        && (infected_x + CONFIG.common_infected_range > CONFIG.scenario_width));
}
