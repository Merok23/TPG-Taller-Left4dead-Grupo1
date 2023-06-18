#include "entity_projectile_venom.h"

VenomProjectile::VenomProjectile(
    uint32_t id, 
    uint32_t position_x, 
    uint32_t position_y) :
    Projectile(id, position_x, position_y, CONFIG.venom_infected_projectile_radius),
    damage(CONFIG.venom_infected_shoot_damage),
    projectile_speed(CONFIG.venom_infected_projectile_speed), 
    state(FLYING_PROJECTILE),
    explosion_counter(CONFIG.venom_infected_projectile_explosion_counter) {}

void VenomProjectile::setImpact(Entity* entity) {
    this->state = EXPLODING_PROJECTILE;
    entity->setDamageForTheRound(this->damage);
}

void VenomProjectile::move(int32_t x_movement, int32_t y_movement) {
    if (this->state == DESTROYED_PROJECTILE || this->state == EXPLODING_PROJECTILE) return;
    this->state = FLYING_PROJECTILE;
    this->getDirectionOfMovement()->setDirection(x_movement * this->projectile_speed, y_movement * this->projectile_speed);
}

void VenomProjectile::update(Map &map) {
    if (this->state == DESTROYED_PROJECTILE) return;
    //moving without using the map ignores collisions:
    if (this->state == FLYING_PROJECTILE) this->getDirectionOfMovement()->move();

    if (this->state == EXPLODING_PROJECTILE) {
        if (this->explosion_counter == 0) {
            this->state = DESTROYED_PROJECTILE;
            return;
        }
        this->explosion_counter--;
    }

    if (map.isOutOfBoundaries(*this->getDirectionOfMovement())) {
        this->state = DESTROYED_PROJECTILE;
        return;
    }
}

bool VenomProjectile::isDead() {
    return this->state == DESTROYED_PROJECTILE;
}

std::string VenomProjectile::getEntityType() {
    return "venom_projectile";
}

std::string VenomProjectile::getState() {
    if (this->state == FLYING_PROJECTILE) return "flying";
    if (this->state == EXPLODING_PROJECTILE) return "exploding";
    return "destroyed";
}
