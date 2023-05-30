#include "action_create_soldier_scout.h"


CreateSoldierScout::CreateSoldierScout() {}

void CreateSoldierScout::execute(IdHandler& handler) {
    Weapon* weapon = new Scout();
    handler.createPlayer(this->getClientId(), weapon);
}

CreateSoldierScout::~CreateSoldierScout() {}
