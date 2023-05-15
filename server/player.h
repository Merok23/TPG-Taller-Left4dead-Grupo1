#include "entity.h"
#include "movement.h"

enum State {
    IDLE,
    MOVING
};

class Player : public Entity {
    private:
        Movement direction_of_movement;
        State state;
    public:
        explicit Player(int id);
        void move(int x, int y);
        Movement getDirectionOfMovement();
};
