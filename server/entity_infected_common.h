#include "entity_infected.h"
#include "config.h"
#include <algorithm>

enum CommonInfectedState {
    IDLE_INFECTED,
    MOVING_INFECTED
};


class CommonInfected : public Infected {
    private:
        CommonInfectedState state;
    public:
        CommonInfected(uint32_t id, uint32_t positionX, uint32_t positionY);
        virtual void move(int32_t x_movement, int32_t y_movement) override;
        virtual void update(Map& map) override;
        virtual void checkForSoldiersInRangeAndSetChase(std::map<u_int32_t, Entity*> &soldiers) override;
    private:
        bool isInRange(Entity* entity);
        void setChase(Entity* entity);
};