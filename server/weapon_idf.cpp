#include "weapon_idf.h"

MachineGun::MachineGun() : 
base_damage(CONFIG.weapon_idf_base_damage), 
range(CONFIG.weapon_idf_range),
magazine_size(CONFIG.weapon_idf_magazine_size),
rounds_left(CONFIG.weapon_idf_magazine_size),
burst_size(CONFIG.weapon_idf_burst_size),
distance_modifier(CONFIG.weapon_idf_distance_modifier),
ammo_used(0) {}

bool MachineGun::inRange(uint32_t distance) {
    return distance <= this->range;
}

int32_t MachineGun::calculateDamage(const uint32_t &distance, const uint32_t &hitCount) {
    double damage = 0;
    if (hitCount > 1 || this->emptyMagazine()) return 0;
    double distance_double = (double) distance;
    damage = this->base_damage - distance_double * this->distance_modifier;
    if (damage < 0) damage = 0;
    return (int32_t) damage;
}

void MachineGun::reload() {
    this->rounds_left = this->magazine_size;
}

bool MachineGun::emptyMagazine() {
    return this->rounds_left == 0;
}

void MachineGun::useAmmo() {
    this->rounds_left -= burst_size;
}

std::string MachineGun::getWeaponType() {
    return std::string("idf");
}

uint32_t MachineGun::getAmmoLeft() {
    return this->rounds_left;
}

uint32_t MachineGun::getAmountOfAmmoUsed() {
    return this->ammo_used;
}