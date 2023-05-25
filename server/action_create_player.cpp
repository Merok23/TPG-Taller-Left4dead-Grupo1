#include "action_create_player.h"

CreatePlayer::CreatePlayer() {}

void CreatePlayer::execute(IdHandler& handler) {
    handler.createPlayer(this->getClientId());
}

CreatePlayer::~CreatePlayer() {}
