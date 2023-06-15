#include "entity_infected_venom.h"

VenomInfected::VenomInfected(uint32_t id, uint32_t position_x, uint32_t position_y) :
    Infected(id, position_x, position_y, CONFIG.venom_infected_health, CONFIG.venom_infected_radius),
    state(IDLE_VENOM_INFECTED),
    look_range(CONFIG.venom_infected_look_range),
    blast_range(CONFIG.venom_infected_blast_range),
    shoot_range(CONFIG.venom_infected_shoot_range),
    blast_damage(CONFIG.venom_infected_blast_damage),
    incapacitated(0),
    speed(CONFIG.venom_infected_speed),
    blast_incapacitated_time(CONFIG.venom_infected_blast_incapacitated_time),
    shoot_incapacitated_time(CONFIG.venom_infected_shoot_incapacitated_time) {}

void VenomInfected::move(int32_t x_movement, int32_t y_movement) {
    if (this->state == DEAD_VENOM_INFECTED) return;
    this->state = MOVING_VENOM_INFECTED;
    this->getDirectionOfMovement()->setDirection(x_movement * this->speed, y_movement * this->speed);
}

void VenomInfected::update(Map &map) {
    if (this->state == DEAD_VENOM_INFECTED) return;

    Entity::resolveDamage();

    if (this->getHitPoints() <= 0) {
        this->state = DEAD_VENOM_INFECTED;
        return;
    } 

    if (this->incapacitated > 0) {
        this->incapacitated--;
        return;
    }

    if (this->state == MOVING_VENOM_INFECTED) map.move(this->getId());
}

void VenomInfected::checkForSoldiersInRangeAndSetChase(std::map<uint32_t, Entity*> &soldiers) {
    if (this->state == DEAD_VENOM_INFECTED) return;
    if (this->incapacitated > 0) return;

    std::map<uint32_t, Entity*> alive_soldiers = Infected::filterDeadSoldiers(soldiers);

    auto iterator = std::find_if(alive_soldiers.begin(), 
        alive_soldiers.end(), [this](std::pair<uint32_t, Entity*> alive_soldiers) {
        return Infected::isInRange(alive_soldiers.second, this->look_range);
    });

    if (iterator != alive_soldiers.end()) {
        this->setChase(iterator->second);
    }
}



bool VenomInfected::isDead() {
    return this->state == DEAD_VENOM_INFECTED;
}

