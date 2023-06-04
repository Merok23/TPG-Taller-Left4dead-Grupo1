#ifndef SERVER_ACTION_SHOOTING_H
#define SERVER_ACTION_SHOOTING_H

#include "action.h"
#include <functional>
#include <iostream>

class Shooting : public Action {
    private:
    bool shooting;

    public:
    explicit Shooting(bool shooting); 
    virtual void execute(IdHandler& handler) override;
    ~Shooting() override;
};
#endif
