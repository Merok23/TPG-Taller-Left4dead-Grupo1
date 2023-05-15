#ifndef SERVER_ACTION_H
#define SERVER_ACTION_H
#include <stdio.h>
#include <functional>
#include <iostream>

#include "../server/game.h"
class Action {
    public:
        virtual void execute(Game& game) = 0; //Como no es instanciable, no hace falta constructor.
        virtual ~Action() noexcept {} ; // Se especifica "noexcept" para el destructor virtual
};
#endif