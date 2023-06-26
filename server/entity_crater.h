#ifndef ENTITY_CRATER_H
#define ENTITY_CRATER_H
#include <vector>
#include <string>

#include "entity.h"
#include "map.h"
#include "hit_entity.h"

/**
 * @class Crater
 * 
 * @brief a crater in the map, it's update doesn't do anything
 *        the only way to interact with it is to collide with it. 
 */
class Crater : public Entity {
    public:
        /**
         * @brief Constructor
         * @param id All Entities have an id, this is the crater's id.
         * @param positionX The x position of the crater on the map.
         * @param positionY The y position of the crater on the map.
         */
        Crater(uint32_t id, uint32_t positionX, uint32_t positionY);
        
        /**
         * @brief used to move entities, here it does nothing. (craters don't move)
         *        it's here because it's a virtual function on Entity.
         * @param x_movement The direction of movement you want to set on the x axis.
         * @param y_movement The direction of movement you want to set on the y axis.
         */
        virtual void move(int32_t x_movement, int32_t y_movement) override;
        
        /**
         * @brief used to update the entity, here it does nothing.
         *        it's here because it's a virtual function on Entity.
         * @param map Generally used to move the entity in the map
         *            again, it's only here because of the virtual function.
         */
        virtual void update(Map& map) override;
        
        /**
         * @brief used to shoot, here it does nothing.
         *        it's here because it's a virtual function on Entity.
         * @param entities_hit A vector of entities that were hit by the projectile.
         */
        virtual void shoot(std::vector<HitEntity>& entities_hit) override;
        
        /**
         * @brief used to know if the entity is infected, here it always returns false.
         * @return false
         */
        virtual bool isInfected() override;
        
        /**
         * @brief used to know if the entity is a soldier, here it always returns false.
         * @return false
         */
        virtual bool isSoldier() override;
        
        /**
         * @brief used to get the entity type.
         * @return "crater"
         */
        virtual std::string getEntityType() override;
        
        /**
         * @brief used to know if the entity is dead, here it always returns false.
         * @return false
         */
        virtual bool isDead() override;
        
        /**
         * @brief used to get the entity state.
         * @return "idle"
         */
        virtual std::string getState() override;
};
#endif
