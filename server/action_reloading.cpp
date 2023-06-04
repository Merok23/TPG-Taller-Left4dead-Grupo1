#include <functional>
#include <iostream>

#include "action_reloading.h"

Reloading::Reloading(bool reloading) : reloading(reloading) {}

void Reloading::execute(IdHandler& handler) {
    handler.reload(this->getClientId(), reloading);
}

Reloading::~Reloading() {}