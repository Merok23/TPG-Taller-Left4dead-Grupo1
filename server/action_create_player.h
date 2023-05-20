#include "action.h"
#include "player.h"

class CreatePlayer : public Action {
    private:
    int nada; 

    public:
    explicit CreatePlayer(int nada) : nada(nada) {}; 
    virtual void execute(Game& game) override {
        Player newPlayer = Player(1, 5, 5);
        Entity *player = &newPlayer;
        game.addEntity(std::move(player));
        //game.addPlayerId(1); //Para que distinga si es un jugador o un infectado
    }

    ~CreatePlayer() override {}  // Se especifica "noexcept" para el destructor virtual sobrescrito

};