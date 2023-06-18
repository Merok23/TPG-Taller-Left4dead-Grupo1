#ifndef ENTITY_PROJECTILE_H
#define ENTITY_PROJECTILE_H

#include "entity.h"

class Projectile : public Entity {
    public:
        Projectile(
            uint32_t id, 
            uint32_t positionX, 
            uint32_t positionY,
            int32_t radius);
        virtual void setImpact(Entity* entity) = 0;

        //Entity methods:
        virtual std::string getEntityType() override = 0; 
        virtual void move(int32_t x_movement, int32_t y_movement) override = 0; 
        virtual void update(Map& map) override = 0;
        virtual void shoot(std::vector<HitEntity>& entities_hit) override;
        virtual bool isInfected() override;
        virtual bool isSoldier() override;
        virtual bool isDead() override = 0;
        virtual std::string getState() override = 0;
};

#endif