#ifndef SERVER_ACTION_H
#define SERVER_ACTION_H

#include <stdio.h>
#include <functional>
#include <iostream>

#include "id_handler.h"
#include "config.h"

/**
 * @class Action
 * 
 * Esta clase representa euna acción genérica en el juego.
 */
class Action {
    private:
        uint32_t client_id; /**< ID del cliente que ejecuta la acción. */
    public:
        /**
         * @brief Constructor de la clase Action.
         */
        Action();

         /**
         * @brief Ejecuta la acción.
         * @param handler Referencia al objeto IdHandler, para ejecutar la accion del cliente.
         */
        virtual void execute(IdHandler& handler) = 0; 

        /**
         * @brief Establece el ID del cliente.
         * @param client_id ID del cliente.
         */
        void setClientId(uint32_t client_id);

        /**
         * @brief Obtiene el ID del cliente.
         * @return uint32_t ID del cliente.
         */
        uint32_t getClientId();

        /**
         * @brief Destructor de la clase Action.
         */
         virtual ~Action();
};
#endif
