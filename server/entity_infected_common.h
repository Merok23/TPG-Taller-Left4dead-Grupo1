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
    DEAD_INFECTED,
    ATTACKING_INFECTED
};


class CommonInfected : public Infected {
    private:
        CommonInfectedState state;
        int32_t look_range;
        int32_t attack_range;
        int32_t attack_cooldown;
        int32_t attack_damage;
        int32_t incapacitated;
        int32_t speed;
    public:
        CommonInfected(uint32_t id, uint32_t positionX, uint32_t positionY);
        virtual void move(int32_t x_movement, int32_t y_movement) override;
        virtual void update(Map& map) override;
        virtual void checkForSoldiersInRangeAndSetChase(std::map<u_int32_t, 
            Entity*> &soldiers) override;
        virtual void checkForSoldiersInRangeAndSetAttack(std::map<u_int32_t, Entity*> &soldiers) override;
        virtual bool isDead() override;
            
    private:
        void resolveDamage();
        bool isInRange(Entity* entity,const int32_t &range);
        void setChase(Entity* entity);
        bool checkForBorderCaseRange(const int32_t &soldier_x,const int32_t &infected_x,const int32_t &range);
};
#endif
