#include "action.h"

Action::Action() : client_id(CONFIG.invalid_id) {}

void Action::setClientId(uint32_t client_id) {
    this->client_id = client_id; 
}

uint32_t Action::getClientId() {
    return this->client_id;
}

Action::~Action() {}
