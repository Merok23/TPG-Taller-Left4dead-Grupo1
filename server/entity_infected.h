#include "entity.h"
#include "config.h"
#pragma once



class Infected : public Entity {
    private:
        //uint32_t damage;
    public:
        Infected(uint32_t id, uint32_t positionX, uint32_t positionY, int32_t hit_points);
        virtual void move(int32_t x_movement, int32_t y_movement) override = 0;
        virtual void update(Map& map) override = 0;
        virtual void shoot(std::vector<HitEntity>& entities_hit) override;
        virtual bool isInfected() override;
        virtual void checkForSoldiersInRangeAndSetChase(std::map<u_int32_t, Entity*> &soldiers) = 0;
        virtual ~Infected() override;
};
