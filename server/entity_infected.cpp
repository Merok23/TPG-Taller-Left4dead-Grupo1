#include "entity_infected.h"


Infected::Infected(uint32_t id, uint32_t x, uint32_t y, int32_t hit_points, uint32_t radius) : 
    Entity(id, hit_points, x, y, radius) {}


//the infected shouldn't be able to shoot
//maybe let's create two abstract classes that inherit from entity
//one for the infected and one for the soldiers
void Infected::shoot(std::vector<HitEntity>& entities_hit) {
    return;
}

bool Infected::isInfected() {
    return true;
}

bool Infected::isSoldier() {
    return false;
}

std::string Infected::getState() {
    return "";
}

bool Infected::isInRange(Entity* entity, const int32_t &range) {
    bool in_range = false;
    int32_t soldier_x = entity->getDirectionOfMovement()->getX();
    int32_t infected_x = this->getDirectionOfMovement()->getX();
    //careful, this can return false, so if you have to add 
    //other condition before this, check for if (!is_in_range)
    in_range = checkForBorderCaseRange(soldier_x, infected_x, range);
    int32_t distance = 
        this->getDirectionOfMovement()->calculateDistance(*entity->getDirectionOfMovement());
    if (distance <= range) in_range = true;
    return (in_range);
}

std::map<uint32_t, Entity*> Infected::filterDeadSoldiers(const std::map<uint32_t, Entity*> &soldiers) {
    std::map<uint32_t, Entity*> alive_soldiers;
    for (auto soldier : soldiers) {
        if (!soldier.second->isDead()) 
            alive_soldiers.insert(std::pair<uint32_t, Entity*>(soldier.first, soldier.second));
    }
    return alive_soldiers;
}

bool Infected::checkForBorderCaseRange(const int32_t &soldier_x,const int32_t &infected_x,const int32_t &range) {
    //soldier is on the end of the map and infected on the start
    if (soldier_x + range > CONFIG.scenario_width) {
        return ((soldier_x - infected_x - CONFIG.scenario_width) 
            < range);
    }
    //infected is on the end of the map and soldier on the start
    return (((soldier_x + CONFIG.scenario_width - infected_x) < range) 
        && (infected_x + range > CONFIG.scenario_width));
}

void Infected::killCheat() {
    this->setDamageForTheRound(CONFIG.cheat_infinite_hitpoints);
}

Infected::~Infected() {}
