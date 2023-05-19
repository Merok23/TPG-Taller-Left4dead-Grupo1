#include "entity.h"
#define INFECTED_HIT_POINTS 80

enum InfectedState {
    IDLE_INFECTED,
    MOVING_INFECTED
};

class Infected : public Entity {
    private:
        //uint32_t damage;
        InfectedState state;
    public:
        Infected(uint32_t id, uint32_t positionX, uint32_t positionY);
        virtual void move(int32_t x_movement, int32_t y_movement) override;
        virtual void update(Map& map) override;
        virtual void shoot(std::vector<HitEntity>& entities_hit) override;
};
