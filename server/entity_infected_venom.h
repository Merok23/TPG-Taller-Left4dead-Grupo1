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
        int32_t shoot_attack_counter;
        int32_t shoot_attack_timing;
        int32_t blast_attack_counter;
        int32_t blast_attack_timing;
        int32_t blast_radius;
        int32_t projectile_radius;
        
    public:
        VenomInfected(uint32_t id, uint32_t positionX, uint32_t positionY);
        virtual void move(int32_t x_movement, int32_t y_movement) override;
        virtual void update(Map& map) override;
        virtual void checkForSoldiersInRangeAndSetChase(std::map<u_int32_t, 
            Entity*> &soldiers) override;
        virtual void checkForSoldiersInRangeAndSetAttack(std::map<u_int32_t, Entity*> &soldiers) override;
        virtual void makeStronger(double factor) override;
        virtual std::string getState() override; 
        virtual std::string getEntityType() override;
        int32_t getShootingRange();
        Movement getBlastPosition();
        void setChase(Entity* entity) override;
        void setAttack(Entity* entity) override;
        void setBlastDamage(std::vector<Entity*> &entities);
        void setShooting();
        bool isShootingAProjectile();
        bool isTimeForBlasting();
        bool isTimeForShooting();
        std::tuple<uint32_t, uint32_t> getProjectilePosition();
        virtual bool isDead() override;
};



#endif
