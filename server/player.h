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
        void move(int x, int y);
        void update();
};
