#include "action.h"
#include <functional>
#include <iostream>
class Moving : public Action {
    private:
    std::array<int32_t, 2> position;

    public:
    explicit Moving(std::array<int32_t, 2> position); 
    virtual void execute(IdHandler& handler) override {
        handler.setMoving(this->getClientId(), position[0], position[1]);
        return;    
    }
    ~Moving() override {}  

};