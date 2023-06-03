#include "entity_crater.h"

Crater::Crater(uint32_t id, uint32_t x, uint32_t y) : Entity(id, CONFIG.crater_hit_points, x, y, CONFIG.crater_radius) {}

void Crater::move(int32_t x_movement, int32_t y_movement) {}

void Crater::update(Map& map) {}

void Crater::shoot(std::vector<HitEntity>& entities_hit) {}

bool Crater::isInfected() {
    return false;
}

bool Crater::isSoldier() {
    return false;
}

std::string Crater::getEntityType() {
    std::string type = "crater";
    return type;
}

bool Crater::isDead() {
    return false;
}

std::string Crater::getState() {
    return "idle";
}
