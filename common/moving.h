#include "action.h"
#include <functional>
#include <iostream>
class Moving : public Action {
public:
    std::array<int8_t, 2> position;

    Moving(std::array<int8_t, 2> position) : position(position) {}; 
     virtual void execute(Game& game) override {
        //game.setMoving(id, position[0], position[1]);
        return;    
    }
    ~Moving() noexcept override {}  // Se especifica "noexcept" para el destructor virtual sobrescrito

};