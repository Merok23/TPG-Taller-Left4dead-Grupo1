#ifndef SERVER_ACTION_RELOADING_H
#define SERVER_ACTION_RELOADING_H

#include "action.h"
#include <functional>
#include <iostream>

class Reloading : public Action {
    private:
    bool reloading; /**< Indica si el cliente está recargando o no. */

    public:
     /**
     * @brief Constructor de la clase Reloading.
     * 
     * @param reloading Valor que indica si se está recargando o no.
     */
    explicit Reloading(bool reloading); 

    virtual void execute(IdHandler& handler) override;

    ~Reloading() override;
};
#endif
