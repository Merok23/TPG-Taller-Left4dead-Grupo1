#ifndef SERVER_ACTION_MOVING_H
#define SERVER_ACTION_MOVING_H

#include "action.h"
#include <functional>
#include <iostream>
class Moving : public Action {
    private:
    std::array<int8_t, 2> directions; /**< Posición a la que se mueve el cliente. */

    public:
    /**
     * @brief Constructor de la clase Moving.
     * @param directions Array de dos elementos que representa la dirección de movimiento.
     */
    explicit Moving(std::array<int8_t, 2> directions); 

    virtual void execute(IdHandler& handler) override;

    ~Moving() override;
};
#endif
