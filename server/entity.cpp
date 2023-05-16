#include "entity.h"

Entity::Entity(uint32_t id, int32_t hit_points, Map &map) : 
    id(id),
    hit_points(hit_points),
    direction_of_movement(0, 0, RADIUS),
    map(map) {}

uint32_t Entity::getId() {
    return this->id;
}


int32_t Entity::getHitPoints() {
    return this->hit_points;
}

Movement* Entity::getDirectionOfMovement() {
    return &this->direction_of_movement;
}

void Entity::setHitPoints(int32_t hit_points) {
    this->hit_points = hit_points;
}
