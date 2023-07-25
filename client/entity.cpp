#include <string>

#include "entity.h"

Entity::Entity(uint32_t id, EntityType type, State state, uint8_t lives, 
    int32_t ammo_left, int32_t hit_points, uint32_t x, uint32_t y, 
        bool facing_left, bool moving_up, const std::string& name) : 
            id(id),
                type(type),
                    lives(lives),
                        ammo_left(ammo_left),
                            hit_points(hit_points),
                                x_position(x), 
                                    y_position(y), 
                                        is_facing_left(facing_left), 
                                            is_moving_up(moving_up),
                                                name(name), 
                                                    state(state) {}


Entity::Entity(uint32_t id, EntityType type, State state, int32_t hit_points, uint32_t x, uint32_t y, 
    bool facing_left, bool moving_up) : 
        id(id),
            type(type),
                lives(0),
                    ammo_left(0),
                        hit_points(hit_points),
                            x_position(x), 
                                y_position(y), 
                                    is_facing_left(facing_left), 
                                        is_moving_up(moving_up), 
                                            name(""),
                                                state(state) {}
uint32_t Entity::getId() {
    return this->id;
}

int32_t Entity::getHitPoints() {
    return this->hit_points;
}

EntityType Entity::getEntityType() {
    return this->type;
}


int32_t Entity::getAmmoLeft() {
    return this->ammo_left;
}

State Entity::getState() {
    return this->state;
}


int32_t Entity::getPositionX() {
    return this->x_position;
}

int32_t Entity::getPositionY() {
    return this->y_position;
}

bool Entity::isFacingLeft() {
    return this->is_facing_left;
}

bool Entity::isMovingUp() {
    return this->is_moving_up;
}

uint8_t Entity::getLives() {
    return this->lives;
}