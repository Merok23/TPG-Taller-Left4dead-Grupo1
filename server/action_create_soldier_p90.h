#ifndef SERVER_ACTION_CREATE_SOLDIER_P90_H
#define SERVER_ACTION_CREATE_SOLDIER_P90_H

#include "action.h"
#include "weapon_p90.h"

class CreateSoldierP90 : public Action {
    private:
        std::string name;
    public:

        /**
         * @brief Constructor de la clase CreateSoldierP90.
         */
        explicit CreateSoldierP90(const std::string& name);

        virtual void execute(IdHandler& handler) override;

        ~CreateSoldierP90() override;
};
#endif
