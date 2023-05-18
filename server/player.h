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
        Player(int id, uint32_t positionX, uint32_t positionY);
        virtual void move(int x, int y) override;
        virtual void update(Map& map) override;
};
