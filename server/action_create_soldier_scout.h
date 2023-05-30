#ifndef SERVER_ACTION_CREATE_SOLDIER_SCOUT_H
#define SERVER_ACTION_CREATE_SOLDIER_SCOUT_H

#include "action.h"
#include "weapon_scout.h"

class CreateSoldierScout : public Action {
    public:
        CreateSoldierScout();
        virtual void execute(IdHandler& handler) override;

        ~CreateSoldierScout() override;
};
#endif

