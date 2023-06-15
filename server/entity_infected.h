#ifndef SERVER_ENTITY_INFECTED_H
#define SERVER_ENTITY_INFECTED_H

#include <vector>
#include <map>
#include <utility>
#include <string>

#include "entity.h"
#include "config.h"
#pragma once



class Infected : public Entity {
    public:
        Infected(uint32_t id, uint32_t positionX, uint32_t positionY, int32_t hit_points, uint32_t radius);
        virtual void move(int32_t x_movement, int32_t y_movement) override = 0;
        virtual void update(Map& map) override = 0;
        virtual void shoot(std::vector<HitEntity>& entities_hit) override;
        virtual bool isInfected() override;
        virtual bool isSoldier() override;
        virtual std::string getEntityType() override = 0;
        virtual void checkForSoldiersInRangeAndSetChase(std::map<u_int32_t, Entity*> &soldiers) = 0;
        virtual void checkForSoldiersInRangeAndSetAttack(std::map<u_int32_t, Entity*> &soldiers) = 0;

        void checkForSoldiersInRangeAndSetChaseWithRange(std::map<u_int32_t, Entity*> &soldiers, const int32_t &range);
        void checkForSoldiersInRangeAndSetAttackWithRange(std::map<u_int32_t, Entity*> &soldiers, const int32_t &range);

        virtual void setChase(Entity* entity) = 0;
        virtual void setAttack(Entity* entity) = 0;
        virtual void makeStronger(double factor) = 0;
        virtual std::string getState() override;
        bool isInRange(Entity* entity, const int32_t &range);
        void moveToMiddle();
        virtual ~Infected() override;
        void killCheat();
    private:
        bool checkForBorderCaseRange(const int32_t &soldier_x,const int32_t &infected_x,const int32_t &range);
};
#endif
