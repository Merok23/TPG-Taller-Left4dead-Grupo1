#include "action_create_soldier_p90.h"


CreateSoldierP90::CreateSoldierP90(const std::string& name) : name(name)  {}

void CreateSoldierP90::execute(IdHandler& handler) {
    Weapon* weapon = new AssaultRifle();
    handler.createPlayer(this->getClientId(), weapon, this->name);
}

CreateSoldierP90::~CreateSoldierP90() {}