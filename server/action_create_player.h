#include "action.h"
#include "entity_player.h"

class CreatePlayer : public Action {
    private:
    int nada; 

    public:
    explicit CreatePlayer(int nada) : nada(nada) {}; 
    virtual void execute(Game& game) override {
        Entity* player = new Player(1, 5, 5);
        game.addEntity(player);
        //game.addPlayerId(1); //Para que distinga si es un jugador o un infectado
    } 
    ~CreatePlayer() override {}  // Se especifica "noexcept" para el destructor virtual sobrescrito

};