#include "entity_infected.h"


Infected::Infected(uint32_t id, uint32_t x, uint32_t y) : 
    Entity(id, CONFIG.infected_health, x, y),
    state(IDLE_INFECTED) {}

void Infected::move(int32_t x_movement, int32_t y_movement) {
    this->state = MOVING_INFECTED;
    //I decided that they move twice the speed of the players (dunno)
    this->getDirectionOfMovement()->setDirection(x_movement + x_movement, y_movement + y_movement);
}

void Infected::update(Map& map) {
    if (this->state == MOVING_INFECTED) {
        map.move(this->getId());
    }
    int32_t hit_points = this->getHitPoints();
    hit_points -= this->getDamageForTheRound();
    this->setHitPoints(hit_points);
    this->setDamageForTheRound(0);
}
//the infected shouldn't be able to shoot
//maybe let's create two abstract classes that inherit from entity
//one for the infected and one for the soldiers
void Infected::shoot(std::vector<HitEntity>& entities_hit) {
    return;
}
