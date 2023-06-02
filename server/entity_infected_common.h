#ifndef SERVER_ENTITY_INFECTED_COMMON_H
#define SERVER_ENTITY_INFECTED_COMMON_H

#include <algorithm>
#include <map>
#include <utility>

#include "entity_infected.h"
#include "config.h"

enum CommonInfectedState {
    IDLE_INFECTED,
    MOVING_INFECTED,
    DEAD_INFECTED
};


class CommonInfected : public Infected {
    private:
        CommonInfectedState state;
    public:
        CommonInfected(uint32_t id, uint32_t positionX, uint32_t positionY);
        virtual void move(int32_t x_movement, int32_t y_movement) override;
        virtual void update(Map& map) override;
        virtual void checkForSoldiersInRangeAndSetChase(std::map<u_int32_t, 
            Entity*> &soldiers) override;
        virtual bool isDead() override;
        virtual std::string getState() override;    
    private:
        void resolveDamage();
        bool isInRange(Entity* entity);
        void setChase(Entity* entity);
        bool checkForBorderCaseRange(int32_t soldier_x, int32_t infected_x);
};
#endif
