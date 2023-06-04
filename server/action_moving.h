#ifndef SERVER_ACTION_MOVING_H
#define SERVER_ACTION_MOVING_H

#include "action.h"
#include <functional>
#include <iostream>
class Moving : public Action {
    private:
    std::array<int8_t, 2> position;

    public:
    explicit Moving(std::array<int8_t, 2> position); 
    virtual void execute(IdHandler& handler) override;
    ~Moving() override;
};
#endif
