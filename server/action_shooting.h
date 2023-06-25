#ifndef SERVER_ACTION_SHOOTING_H
#define SERVER_ACTION_SHOOTING_H

#include "action.h"
#include <functional>
#include <iostream>

class Shooting : public Action {
    private:
    bool shooting; /**< Indica si el cliente está disparando o no. */

    public:
    /**
     * @brief Constructor de la clase Shooting.
     * 
     * @param shooting Valor que indica si se está disparando o no.
     */
    explicit Shooting(bool shooting); 

    virtual void execute(IdHandler& handler) override;

    ~Shooting() override;
};
#endif
