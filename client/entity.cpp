#include "entity.h"

Entity::Entity(uint32_t id, int32_t hit_points) : 
    id(id),
    hit_points(hit_points) {}

uint32_t Entity::getId() {
    return this->id;
}

int32_t Entity::getHitPoints() {
    return this->hit_points;
}

std::string Entity::getEntityType() {
    std::string type = "entity";
    return type;
}