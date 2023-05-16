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
        explicit Player(int id, Map &map);
        virtual void move(int x, int y) override;
        void update();
};
