#include <string>

#include "entity.h"

Entity::Entity(uint32_t id, const std::string& type, State state, const std::string& weapon_type, 
    int32_t ammo_left, int32_t hit_points, uint32_t x, uint32_t y, 
        bool facing_left, bool moving_up) : 
            id(id),
                type(type),
                    state(state),
                        weapon_type(weapon_type),
                            ammo_left(ammo_left),
                                hit_points(hit_points),
                                    x_position(x), 
                                        y_position(y), 
                                            is_facing_left(facing_left), 
                                                is_moving_up(moving_up) {}



uint32_t Entity::getId() {
    return this->id;
}

int32_t Entity::getHitPoints() {
    return this->hit_points;
}

std::string Entity::getType() {
    return type;
}

std::string Entity::getWeaponType() {
    return this->weapon_type;
}

int32_t Entity::getAmmoLeft() {
    return this->ammo_left;
}

std::string Entity::getState() {
    if (this->state == RUN) {
        return "moving";
    } else if (this->state == SHOOT) {
        return "shooting";
    } else if (this->state == RELOAD) {
        return "reloading";
    } else if (this->state == DIE) {
        return "dead";
    }
    return "idle";
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
