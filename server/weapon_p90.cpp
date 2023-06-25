#include "weapon_p90.h"

AssaultRifle::AssaultRifle() : 
base_damage(CONFIG.weapon_p90_base_damage), 
range(CONFIG.weapon_p90_range),
magazine_size(CONFIG.weapon_p90_magazine_size),
rounds_left(CONFIG.weapon_p90_magazine_size),
burst_size(CONFIG.weapon_p90_burst_size),
distance_modifier(CONFIG.weapon_p90_distance_modifier),
ammo_used(0) {}

bool AssaultRifle::inRange(uint32_t distance) {
    return distance <= this->range;
}

int32_t AssaultRifle::calculateDamage(const uint32_t &distance, const uint32_t &hitCount) {
    double damage = 0;
    if (hitCount > 1 || this->emptyMagazine()) return 0;
    double distance_double = (double) distance;
    damage = this->base_damage - distance_double * this->distance_modifier;
    if (damage < 0) damage = 0;
    return (int32_t) damage;
}

void AssaultRifle::reload() {
    this->rounds_left = this->magazine_size;
}

bool AssaultRifle::emptyMagazine() {
    return this->rounds_left == 0;
}

void AssaultRifle::useAmmo() {
    this->rounds_left -= burst_size;
    this->ammo_used += burst_size;
}

std::string AssaultRifle::getWeaponType() {
    return std::string("p90");
}

uint32_t AssaultRifle::getAmmoLeft() {
    return this->rounds_left;
}

uint32_t AssaultRifle::getAmountOfAmmoUsed() {
    return this->ammo_used;
}

