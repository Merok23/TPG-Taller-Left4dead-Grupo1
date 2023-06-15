#ifndef SERVER_ENTITY_INFECTED_WITCH_H
#define SERVER_ENTITY_INFECTED_WITCH_H

#include <vector>
#include <map>
#include <utility>
#include <algorithm>
#include <string>

#include "entity_infected.h"
#include "config.h"

enum WitchInfectedState {
    IDLE_WITCH_INFECTED,
    MOVING_WITCH_INFECTED,
    DEAD_WITCH_INFECTED,
    ATTACKING_WITCH_INFECTED,
    SHOUTING_WITCH_INFECTED
};


class WitchInfected : public Infected {
    private:
        WitchInfectedState state;
        int32_t look_range;
        int32_t attack_range;
        int32_t attack_cooldown;
        int32_t attack_damage;
        int32_t incapacitated;
        int32_t speed;
        int32_t shout_cooldown; //time she's incapacitated by the shout, not the cooldown of the shout
        double shout_probability;
        bool has_spawned_infected; //I have decided they can only spawn infected once
                                   //this can be changed later if wanted.
    public:
        WitchInfected(uint32_t id, uint32_t positionX, uint32_t positionY);
        virtual void move(int32_t x_movement, int32_t y_movement) override;
        virtual void update(Map& map) override;
        virtual void checkForSoldiersInRangeAndSetChase(std::map<u_int32_t, 
            Entity*> &soldiers) override;
        virtual void checkForSoldiersInRangeAndSetAttack(std::map<u_int32_t, Entity*> &soldiers) override;
        virtual void makeStronger(double factor) override;
        virtual bool isDead() override;
        virtual std::string getState() override; 
        virtual std::string getEntityType() override;
        bool hasSpawnedInfected();
        void setSpawnedInfected();
        bool isShouting();
        void setChase(Entity* entity) override;
        void setAttack(Entity* entity) override;
};
#endif
