
#include "entity_infected_spear.h"

SpearInfected::SpearInfected(uint32_t id, uint32_t positionX, uint32_t positionY) :
    Infected(id, positionX, positionY, CONFIG.spear_infected_health, CONFIG.spear_infected_radius),
    state(IDLE_SPEAR_INFECTED),
    look_range(CONFIG.spear_infected_look_range),
    attack_range(CONFIG.spear_infected_attack_range),
    attack_cooldown(CONFIG.spear_infected_attack_cooldown),
    attack_damage(CONFIG.spear_infected_damage),
    incapacitated(0),
    speed(CONFIG.spear_infected_speed) {}

void SpearInfected::move(int32_t x_movement, int32_t y_movement) {
    if (this->state == DEAD_SPEAR_INFECTED) return; 
    this->state = MOVING_SPEAR_INFECTED;
    this->getDirectionOfMovement()->setDirection(x_movement * this->speed,
        y_movement * this->speed);
}

void SpearInfected::update(Map& map) {
    if (this->state == DEAD_SPEAR_INFECTED) return;
    
    Entity::resolveDamage();

    if (this->getHitPoints() <= 0) this->state = DEAD_SPEAR_INFECTED;
    
    if (this->incapacitated > 0) {
        this->incapacitated--;
        return;
    }
    
    if (this->state == MOVING_SPEAR_INFECTED) map.move(this->getId());
}

bool SpearInfected::isDead() {
    return this->state == DEAD_SPEAR_INFECTED;
}

void SpearInfected::setChase(Entity* entity) {
    this->getDirectionOfMovement()->setChase(*entity->getDirectionOfMovement(), 
        this->speed);
    this->state = MOVING_SPEAR_INFECTED;
}

void SpearInfected::checkForSoldiersInRangeAndSetAttack(std::map<u_int32_t, Entity*> &soldiers) {
    //this shouldn't happen since when it's dead its removed from the game
    //but it's here for a border case where it was killed before attacking
    if (this->state == DEAD_SPEAR_INFECTED) return;
    if (this->incapacitated > 0) return;
    std::map<uint32_t, Entity*> alive_soldiers = Infected::filterDeadSoldiers(soldiers);
    auto iterator = std::find_if(alive_soldiers.begin(), 
        alive_soldiers.end(), [this](std::pair<uint32_t, Entity*> alive_soldiers) {
        return Infected::isInRange(alive_soldiers.second, this->attack_range);
    });
    //aca falta agregar un factor random.
    if (iterator != alive_soldiers.end()) {
        this->state = ATTACKING_SPEAR_INFECTED;
        iterator->second->setDamageForTheRound(this->attack_damage);
        this->incapacitated = attack_cooldown;
    }
}

void SpearInfected::checkForSoldiersInRangeAndSetChase(std::map<u_int32_t, Entity*> &soldiers) {
    if (this->state == DEAD_SPEAR_INFECTED) return;
    if (this->incapacitated > 0) return;
    std::map<uint32_t, Entity*> alive_soldiers = Infected::filterDeadSoldiers(soldiers);
    auto iterator = std::find_if(alive_soldiers.begin(), 
        alive_soldiers.end(), [this](std::pair<uint32_t, Entity*> alive_soldiers) {
        return Infected::isInRange(alive_soldiers.second, this->look_range);
    });
    if (iterator != alive_soldiers.end()) {
        this->state = ATTACKING_SPEAR_INFECTED;
        this->setChase(iterator->second);
    }
}

void SpearInfected::makeStronger(double factor) {
    this->attack_damage *= factor;
    this->attack_range *= factor;
    this->look_range *= factor;
    this->speed *= factor;
    int32_t hit_points = this->getHitPoints();
    hit_points *= factor;
    this->setHitPoints(hit_points);
}

std::string SpearInfected::getState() {
    switch (this->state) {
        case IDLE_SPEAR_INFECTED:
            return "idle";
        case MOVING_SPEAR_INFECTED:
            return "moving";
        case DEAD_SPEAR_INFECTED:
            return "dead";
        case ATTACKING_SPEAR_INFECTED:
            return "attacking";
        default:
            return "idle";
    }
}

std::string SpearInfected::getEntityType() {
    return "spear";
}
