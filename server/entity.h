#ifndef SERVER_ENTITY_H
#define SERVER_ENTITY_H

#include <cstdint>
#include <functional>
#include <vector>
#include <string>
#include <utility>

#include "map.h"
#include "movement.h"
#include "hit_entity.h"
#include "config.h"

#pragma once


/**
 * @class Entity abstract class, used to polymorph.
 */
class Entity {
    private:
        uint32_t id; /**< Entity id, it's supposed to be unique. */
        int32_t hit_points; /**< Entity hit points. */
        Movement direction_of_movement; /**< Entity movement. */
        int32_t damage_for_the_round; /**< Damage the entity will take next time it updates. */
        
    public:
        /**
         * @brief Constructor
         * @param id All Entities have an id, it's supposed to be unique.
         * @param hit_points The hit points of the entity.
         * @param x The x position of the entity on the map.
         * @param y The y position of the entity on the map.
         * @param radius The radius of the entity.
        */
        Entity(uint32_t id, int32_t hit_points, uint32_t x, uint32_t y, uint32_t radius);

        /**
         * @brief Used to know the entity's id
         * @return The entity's id
         */
        uint32_t getId();
        /**
         * @brief Used to know the entity's hit points
         * @return The entity's hit points
         */
        int32_t getHitPoints();
        /**
         * @brief Used to know the entity's damage for the round.
         * @return The entity's damage for the round. 
         */
        int32_t getDamageForTheRound();

        /**
         * @brief Used to set the entity's hit points
         * @param hit_points The entity's new hit points
         */
        void setHitPoints(int32_t hit_points);

        /**
         * @brief Used to accumulate damage for the round.
         * @param damage The damage to accumulate.
         */
        void setDamageForTheRound(int32_t damage);

        /**
         * @brief sets the damage for the round to 0. 
         */
        void resetDamageForTheRound();

        /**
         * @brief Gets the Movement of the Entity.
         * @return The Movement of the Entity.
         */
        Movement* getDirectionOfMovement();

        /**
         * @brief Resolves the damage for the round. (Subtracts the damage for the round from the hit points)
         */
        void resolveDamage();

        /**
         * @brief Used to know the entity type.
         * @returns The entity type as a string. 
         */
        virtual std::string getEntityType() = 0;

        /**
         * @brief Used to set the direction of movement of the entity.
         */
        virtual void move(int32_t x_movement, int32_t y_movement) = 0; 
        
        /**
         * @brief Used to update the entity, here the entities do almost everything. 
         */
        virtual void update(Map& map) = 0;

        /**
         * @brief shouldn't be here, but it's to late to change it. 
         */
        virtual void shoot(std::vector<HitEntity>& entities_hit) = 0;
        /**
         * @brief Used to know if the entity is infected.
         * @return true if the entity is infected, false otherwise.
         */
        virtual bool isInfected() = 0;

        /**
         * @brief Used to know if the entity is a soldier.
         * @return true if the entity is a soldier, false otherwise.
         */
        virtual bool isSoldier() = 0;

        /**
         * @brief Used to know if the entity is dead.
         * @return true if the entity is dead, false otherwise.
         */
        virtual bool isDead() = 0;

        /**
         * @brief Used to know the entity's state.
         * @return The entity's state as a string.
         */
        virtual std::string getState() = 0;

        /**
         * @brief Destructor.
         * @return Used for polymorphism.
         */
        virtual ~Entity() = 0;
};
#endif
