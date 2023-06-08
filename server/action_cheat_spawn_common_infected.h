#ifndef SERVER_ACTION_CHEAT_SPAWN_COMMON_INFECTED_H
#define SERVER_ACTION_CHEAT_SPAWN_COMMON_INFECTED_H

#include "action.h"

class SpawnCommonInfectedCheat : public Action {
    public:
        SpawnCommonInfectedCheat();
        virtual void execute(IdHandler& handler) override;
        ~SpawnCommonInfectedCheat() override;
};
#endif
