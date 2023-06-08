#include "action_cheat_infinite_hp.h"

SetInfiniteHitpointsCheat::SetInfiniteHitpointsCheat() {}

void SetInfiniteHitpointsCheat::execute(IdHandler& handler) {
    handler.setCheat(this->getClientId(), Cheat::INFINITE_HITPOINTS);
}

SetInfiniteHitpointsCheat::~SetInfiniteHitpointsCheat() {}
