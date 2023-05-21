#include "entity_infected.h"


Infected::Infected(uint32_t id, uint32_t x, uint32_t y, int32_t hit_points) : 
    Entity(id, hit_points, x, y) {}


//the infected shouldn't be able to shoot
//maybe let's create two abstract classes that inherit from entity
//one for the infected and one for the soldiers
void Infected::shoot(std::vector<HitEntity>& entities_hit) {
    return;
}

bool Infected::isInfected() {
    return true;
}

Infected::~Infected() {}
