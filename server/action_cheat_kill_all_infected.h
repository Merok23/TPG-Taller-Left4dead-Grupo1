#ifndef SERVER_ACTION_CHEAT_KILL_ALL_INFECTED_H
#define SERVER_ACTION_CHEAT_KILL_ALL_INFECTED_H

#include "action.h"

class KillAllInfectedCheat : public Action {
    public:
        /**
         * @brief Constructor de la clase KillAllInfectedCheat.
         */
        KillAllInfectedCheat();

        virtual void execute(IdHandler& handler) override;

        ~KillAllInfectedCheat() override;
};
#endif
