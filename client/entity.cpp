#include "entity.h"

Entity::Entity(uint32_t id, const std::string& type, int32_t hit_points, uint32_t x, uint32_t y) : 
    id(id),
    type(type),
    hit_points(hit_points),
    x_position(x), 
    y_position(y) {}


uint32_t Entity::getId() {
    return this->id;
}

int32_t Entity::getHitPoints() {
    return this->hit_points;
}

std::string Entity::getType() {
    return type;
}

int32_t Entity::getPositionX() {
    return this->x_position;
}

int32_t Entity::getPositionY() {
    return this->y_position;
}