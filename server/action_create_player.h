#ifndef SERVER_ACTION_CREATE_PLAYER_H
#define SERVER_ACTION_CREATE_PLAYER_H

#include "action.h"
#include "entity_player.h"

class CreatePlayer : public Action {
    public:
        CreatePlayer();
        virtual void execute(IdHandler& handler) override;
    ~CreatePlayer() override;
};
#endif
