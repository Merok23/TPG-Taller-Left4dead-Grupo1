#include "action.h"
#include "entity_player.h"

class CreatePlayer : public Action {
    public:
        explicit CreatePlayer() {}; 
        virtual void execute(IdHandler& handler) override {
            handler.createPlayer(this->getClientId());
        } 
    ~CreatePlayer() override {} 

};