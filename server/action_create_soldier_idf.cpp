#include "action_create_soldier_idf.h"


CreateSoldierIdf::CreateSoldierIdf() {}

void CreateSoldierIdf::execute(IdHandler& handler) {
    Weapon* weapon = new MachineGun();
    handler.createPlayer(this->getClientId(), weapon);
}

CreateSoldierIdf::~CreateSoldierIdf() {}