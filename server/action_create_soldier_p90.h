#ifndef SERVER_ACTION_CREATE_SOLDIER_P90_H
#define SERVER_ACTION_CREATE_SOLDIER_P90_H

#include "action.h"
#include "weapon_p90.h"

class CreateSoldierP90 : public Action {
    public:
        CreateSoldierP90();
        virtual void execute(IdHandler& handler) override;

        ~CreateSoldierP90() override;
};
#endif