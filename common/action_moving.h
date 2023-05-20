#include "action.h"
#include <functional>
#include <iostream>
class Moving : public Action {
    private:
    std::array<int8_t, 2> position;

    public:
    explicit Moving(std::array<int8_t, 2> position); 
    virtual void execute(Game& game) override {
        //game.setMoving(id, position[0], position[1]);
        return;    
    }
    ~Moving() noexcept override {}  // Se especifica "noexcept" para el destructor virtual sobrescrito

};