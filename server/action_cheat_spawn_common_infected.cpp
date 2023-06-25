#include "action_cheat_spawn_common_infected.h"

SpawnCommonInfectedCheat::SpawnCommonInfectedCheat() {}

void SpawnCommonInfectedCheat::execute(IdHandler& handler) {
    handler.setCheat(this->getClientId(), Cheat::SPAWN_COMMON_INFECTED);
}


SpawnCommonInfectedCheat::~SpawnCommonInfectedCheat() {}