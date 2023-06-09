#include <string>

#include "entity.h"

Entity::Entity(uint32_t id, EntityTypeGS type, State state, uint8_t lives, WeaponType weapon_type, 
    int32_t ammo_left, int32_t hit_points, uint32_t x, uint32_t y, 
        bool facing_left, bool moving_up) : 
            id(id),
                type(type),
                    lives(lives),
                        weapon_type(weapon_type),
                            ammo_left(ammo_left),
                                hit_points(hit_points),
                                    x_position(x), 
                                        y_position(y), 
                                            is_facing_left(facing_left), 
                                                is_moving_up(moving_up), state(state) {}


Entity::Entity(uint32_t id, EntityTypeGS type, State state, int32_t hit_points, uint32_t x, uint32_t y, 
    bool facing_left, bool moving_up) : 
        id(id),
            type(type),
                lives(0),
                    weapon_type(WeaponType::NONE),
                        ammo_left(0),
                            hit_points(hit_points),
                                x_position(x), 
                                    y_position(y), 
                                        is_facing_left(facing_left), 
                                            is_moving_up(moving_up), state(state) {}
uint32_t Entity::getId() {
    return this->id;
}

int32_t Entity::getHitPoints() {
    return this->hit_points;
}

EntityTypeGS Entity::getEntityType() {
    return this->type;
}

std::string Entity::getType() {
    if (this->type == SOLDIER) {
        return "player";
    } else if (this->type == COMMON_INFECTED) {
        return "common_infected";
    }
    return "none";
}

WeaponType Entity::getWeaponType() {
    return this->weapon_type;
}

std::string Entity::getWeapon() {
    if (this->weapon_type == WeaponType::IDF) {
        return "idf";
    } else if (this->weapon_type == WeaponType::P90) {
        return "p90";
    } else if (this->weapon_type == WeaponType::SCOUT) {
        return "scout";
    }
    return "none";
}

int32_t Entity::getAmmoLeft() {
    return this->ammo_left;
}

State Entity::getState() {
    return this->state;
}
std::string Entity::getStateEnum() {
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

uint8_t Entity::getLives() {
    return this->lives;
}