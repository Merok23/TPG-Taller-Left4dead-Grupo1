#ifndef SERVER_ACTION_CREATE_SOLDIER_SCOUT_H
#define SERVER_ACTION_CREATE_SOLDIER_SCOUT_H

#include "action.h"
#include "weapon_scout.h"

class CreateSoldierScout : public Action {
    public:
        /**
         * @brief Constructor de la clase CreateSoldierScout.
         */
        CreateSoldierScout();

        /**
         * @brief Ejecuta la acción.
         * @param handler Referencia al objeto IdHandler, para ejecutar la accion del cliente.
         */
        virtual void execute(IdHandler& handler) override;

        ~CreateSoldierScout() override;
};
#endif

