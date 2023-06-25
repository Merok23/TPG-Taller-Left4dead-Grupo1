#ifndef SERVER_ACTION_CHEAT_INFINITE_HP_H
#define SERVER_ACTION_CHEAT_INFINITE_HP_H

#include "action.h"

class SetInfiniteHitpointsCheat : public Action {
    public:
        /**
         * @brief Constructor de la clase SetInfiniteHitpointsCheat.
         */
        SetInfiniteHitpointsCheat();
        
        virtual void execute(IdHandler& handler) override;

        ~SetInfiniteHitpointsCheat() override;
};
#endif
