#include "entity.h"
#include "movement.h"

enum State {
    IDLE,
    MOVING
};

class Player : public Entity {
    private:
        State state;
    public:
        explicit Player(int id);
        virtual void move(int x, int y) override;
        virtual void update(Map& map) override;
};
