#include <functional>
#include <iostream>

#include "action_shooting.h"

Shooting::Shooting(bool shooting) : shooting(shooting) {}

void Shooting::execute(IdHandler& handler) {
    handler.shoot(this->getClientId(), shooting);
}

Shooting::~Shooting() {}