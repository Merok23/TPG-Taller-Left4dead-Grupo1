#ifndef SERVER_ENTITY_INFECTED_SPEAR_H
#define SERVER_ENTITY_INFECTED_SPEAR_H

#include "entity_infected.h"
#include "config.h"

#include <algorithm>
#include <map>
#include <utility>

enum SpearInfectedState {
    IDLE_SPEAR_INFECTED,
    MOVING_SPEAR_INFECTED,
    DEAD_SPEAR_INFECTED,
    ATTACKING_SPEAR_INFECTED
};

class SpearInfected : public Infected {
    private:
        SpearInfectedState state;
        int32_t look_range;
        int32_t attack_range;
        int32_t attack_cooldown;
        int32_t attack_damage;
        int32_t incapacitated;
        int32_t speed;
    public:
        SpearInfected(uint32_t id, uint32_t positionX, uint32_t positionY);
        virtual void move(int32_t x_movement, int32_t y_movement) override;
        virtual void update(Map& map) override;
        virtual void checkForSoldiersInRangeAndSetChase(std::map<u_int32_t, 
            Entity*> &soldiers) override;
        virtual void checkForSoldiersInRangeAndSetAttack(std::map<u_int32_t, Entity*> &soldiers) override;
        virtual void makeStronger(double factor) override;
        virtual bool isDead() override;
        virtual std::string getState() override; 
        virtual std::string getEntityType() override;
        void setChase(Entity* entity) override;
        void setAttack(Entity* entity) override;
};
#endif
