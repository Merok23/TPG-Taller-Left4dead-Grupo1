#include "entity.h"

Entity::Entity(uint32_t id, int32_t hit_points, uint32_t x, uint32_t y) : 
    id(id),
    hit_points(hit_points),
    direction_of_movement(x, y, RADIUS),
    damage_for_the_round(0) {}

uint32_t Entity::getId() {
    return this->id;
}

void Entity::setDamageForTheRound(int32_t damage) {
    this->damage_for_the_round += damage;
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
