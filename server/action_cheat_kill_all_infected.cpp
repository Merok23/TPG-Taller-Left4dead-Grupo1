#include "action_cheat_kill_all_infected.h"

KillAllInfectedCheat::KillAllInfectedCheat() {}

void KillAllInfectedCheat::execute(IdHandler& handler) {
    handler.setCheat(this->getClientId(), Cheat::KILL_ALL_INFECTED);
}

KillAllInfectedCheat::~KillAllInfectedCheat() {}
