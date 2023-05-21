#include "entity_infected_common.h"

CommonInfected::CommonInfected(uint32_t id, uint32_t positionX, uint32_t positionY) : 
    Infected(id, positionX, positionY, CONFIG.infected_health),
    state(IDLE_INFECTED) {}

void CommonInfected::checkForSoldiersInRangeAndSetChase(std::map<u_int32_t, Entity*> &soldiers) {
    auto iterator = std::find_if(soldiers.begin(), soldiers.end(), [this](std::pair<uint32_t, Entity*> soldier) {
        return this->isInRange(soldier.second);
    });

    if (iterator != soldiers.end()) {
        this->setChase(iterator->second);
    }

/*
    for (auto& soldier : soldiers) {
        if (this->isInRange(soldier.second)) {
            //add some randomness to the chase
            //as it is, it will always chase the first soldier in range
            this->setChase(soldier.second);
            return;
        }
    }
*/
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
    this->getDirectionOfMovement()->setDirection(x_movement * CONFIG.infected_speed, y_movement * CONFIG.infected_speed);
}

bool CommonInfected::isInRange(Entity* entity) {
    int32_t distance = this->getDirectionOfMovement()->calculateDistance(*entity->getDirectionOfMovement());
    return (distance > CONFIG.common_infected_range);
}

void CommonInfected::setChase(Entity* entity) {
    this->getDirectionOfMovement()->setChase(*entity->getDirectionOfMovement(), CONFIG.common_infected_speed);
    this->state = MOVING_INFECTED;
}