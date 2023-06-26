#ifndef ENTITY_PROJECTILE_VENOM_H
#define ENTITY_PROJECTILE_VENOM_H

#include "entity_projectile.h"

enum VenomProjectileState {
    FLYING_PROJECTILE,
    EXPLODING_PROJECTILE,
    DESTROYED_PROJECTILE
};

/**
 * @class VenomProjectile
 * @brief Represents a venom projectile in the game, it's a projectile that explodes on impact.
 */
class VenomProjectile : public Projectile {
    private:
        int32_t damage; /**< Damage the projectile does. */
        int32_t projectile_speed; /**< Speed of the projectile. */
        VenomProjectileState state; /**< State of the projectile. */
        int8_t explosion_counter; /**< Counter of the explosion, when it expires, the projectile dissapears*/
    public:
        /**
         * @brief Constructor
         * @param id All Entities have an id, this is the projectile's id.
         * @param positionX The x position of projectile on the map.
         * @param positionY The y position of projectile on the map. 
         */
        VenomProjectile(
            uint32_t id, 
            uint32_t positionX, 
            uint32_t positionY);

        /**
         * @brief Sets the damage of the round to the Entity. it also sets the explosion counter. 
         */
        virtual void setImpact(Entity* entity) override;

        //Entity methods:
        virtual void move(int32_t x_movement, int32_t y_movement) override;
        virtual void update(Map& map) override;
        virtual bool isDead() override;
        virtual std::string getEntityType() override;
        virtual std::string getState() override;
};

#endif 