#include <functional>
#include <iostream>
#include "action_moving.h"

Moving::Moving(std::array<int32_t, 2> position) : position(position) {}

void Moving::execute(IdHandler& handler) {
    handler.setMoving(this->getClientId(), position[0], position[1]);
}

Moving::~Moving() {}
