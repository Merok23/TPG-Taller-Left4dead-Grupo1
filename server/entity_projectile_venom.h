#ifndef ENTITY_PROJECTILE_VENOM_H
#define ENTITY_PROJECTILE_VENOM_H

#include "entity_projectile.h"

enum VenomProjectileState {
    FLYING_PROJECTILE,
    EXPLODING_PROJECTILE,
    DESTROYED_PROJECTILE
};

class VenomProjectile : public Projectile {
    private:
        int32_t damage;
        int32_t projectile_speed;
        VenomProjectileState state;
        int8_t explosion_counter;
    public:
        VenomProjectile(
            uint32_t id, 
            uint32_t positionX, 
            uint32_t positionY);
        virtual void setImpact(Entity* entity) override;

        //Entity methods:
        virtual void move(int32_t x_movement, int32_t y_movement) override;
        virtual void update(Map& map) override;
        virtual bool isDead() override;
        virtual std::string getEntityType() override;
        virtual std::string getState() override;
};

#endif 