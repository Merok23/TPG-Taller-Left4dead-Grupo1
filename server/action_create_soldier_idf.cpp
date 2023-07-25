#include "action_create_soldier_idf.h"


CreateSoldierIdf::CreateSoldierIdf(const std::string& name) : name(name)  {}

void CreateSoldierIdf::execute(IdHandler& handler) {
    Weapon* weapon = new MachineGun();
    handler.createPlayer(this->getClientId(), weapon, this->name);
}

CreateSoldierIdf::~CreateSoldierIdf() {}