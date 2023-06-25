#include <functional>
#include <iostream>
#include "action_moving.h"

Moving::Moving(std::array<int8_t, 2> directions) : directions(directions) {}

void Moving::execute(IdHandler& handler) {
    handler.setMoving(this->getClientId(), directions[0], directions[1]);
}

Moving::~Moving() {}
