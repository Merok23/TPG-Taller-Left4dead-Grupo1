#ifndef SERVER_ACTION_H
#define SERVER_ACTION_H
#include <stdio.h>
#include <functional>
#include <iostream>
#include "id_handler.h"

class Action {
    private:
        uint32_t client_id;
    public:
        Action() : client_id(8589934591) {};
        virtual void execute(IdHandler& handler) = 0; //Como no es instanciable, no hace falta constructor.
        void setClientId(uint32_t client_id);
        uint32_t getClientId(); 
        virtual ~Action() {} ; // Se especifica "noexcept" para el destructor virtual
};
#endif