#ifndef ENTITY_INFECTED_VENOM_H
#define ENTITY_INFECTED_VENOM_H

#include <vector>
#include <map>
#include <utility>
#include <algorithm>
#include <string>

#include "entity_infected.h"
#include "config.h"

enum VenomInfectedState {
    IDLE_VENOM_INFECTED,
    MOVING_VENOM_INFECTED,
    DEAD_VENOM_INFECTED,
    BLASTING_VENOM_INFECTED,
    SHOOTING_VENOM_INFECTED
};

class VenomInfected : public Infected {
    private:
        VenomInfectedState state;
        int32_t look_range;
        int32_t blast_range;
        int32_t shoot_range;
        int32_t blast_damage;
        int32_t incapacitated;
        int32_t speed;
        int32_t blast_incapacitated_time; 
        int32_t shoot_incapacitated_time;
    public:
        VenomInfected(uint32_t id, uint32_t positionX, uint32_t positionY);
        virtual void move(int32_t x_movement, int32_t y_movement) override;
        virtual void update(Map& map) override;
        virtual void checkForSoldiersInRangeAndSetChase(std::map<u_int32_t, 
            Entity*> &soldiers) override;
        virtual void checkForSoldiersInRangeAndSetAttack(std::map<u_int32_t, Entity*> &soldiers) override;
        virtual void makeStronger(double factor) override;
        virtual bool isDead() override;
        virtual std::string getState() override; 
        virtual std::string getEntityType() override;
        bool isShootingAProjectile();
    private:
        void setChase(Entity* entity);
};



#endif
