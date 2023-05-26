#include "weapon_scout.h"

Scout::Scout() : 
base_damage(CONFIG.weapon_scout_base_damage), 
range(CONFIG.weapon_scout_range),
magazine_size(CONFIG.weapon_scout_magazine_size),
rounds_left(CONFIG.weapon_scout_magazine_size),
damage_falloff(CONFIG.weapon_scout_damage_falloff) {}

bool Scout::inRange(uint32_t distance) {
    return distance <= this->range;
}

int32_t Scout::calculateDamage(const uint32_t &distance, const uint32_t &hitCount) {
    double damage = 0;
    if (this->emptyMagazine()) return 0;
    damage = this->base_damage * CONFIG.weapon_scout_damage_falloff * hitCount;
    return (int32_t) damage;
}

void Scout::reload() {
    this->rounds_left = this->magazine_size;
}

bool Scout::emptyMagazine() {
    return this->rounds_left == 0;
}

void Scout::useAmmo() {
    this->rounds_left -= -1;
}

std::string Scout::getWeaponType() {
    return std::string("scout");
}

uint32_t Scout::getAmmoLeft() {
    return this->rounds_left;
}
