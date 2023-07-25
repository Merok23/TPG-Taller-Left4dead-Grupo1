#include "action_create_soldier_scout.h"


CreateSoldierScout::CreateSoldierScout(const std::string& name) : name(name) {}

void CreateSoldierScout::execute(IdHandler& handler) {
    Weapon* weapon = new Scout();
    handler.createPlayer(this->getClientId(), weapon, this->name);
}

CreateSoldierScout::~CreateSoldierScout() {}
