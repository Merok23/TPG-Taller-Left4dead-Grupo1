#include "action.h"


void Action::setClientId(uint32_t client_id) {
    this->client_id = client_id; 
}

uint32_t Action::getClientId() {
    return this->client_id;
}
