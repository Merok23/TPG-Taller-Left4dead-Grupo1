#ifndef SERVER_ACTION_RELOADING_H
#define SERVER_ACTION_RELOADING_H

#include "action.h"
#include <functional>
#include <iostream>

class Reloading : public Action {
    private:
    bool reloading; // no estoy segura si se puede parar de recargar

    public:
    explicit Reloading(bool reloading); 
    virtual void execute(IdHandler& handler) override;
    ~Reloading() override;
};
#endif
