#include "entity_projectile.h"

Projectile::Projectile(
    uint32_t id, 
    uint32_t position_x, 
    uint32_t position_y,
    int32_t radius) :
    Entity(id, 100, position_x, position_y, radius) {}

void Projectile::shoot(std::vector<HitEntity>& entities_hit) {
    return;
}

bool Projectile::isInfected() {
    return false;
}

bool Projectile::isSoldier() {
    return false;
}
