#ifndef SERVER_ENTITY_INFECTED_H
#define SERVER_ENTITY_INFECTED_H

#include <vector>
#include <map>
#include <utility>
#include <string>

#include "entity.h"
#include "config.h"
#pragma once


/**
 * @class Infected abstract class
 * @brief  It has all the methods all infected should have 
 *         and the game uses it to polymorph.
 */
class Infected : public Entity {
    public:
        /**
         * @brief Constructor
         * @param id All Entities have an id, this is the infected's id.
         * @param positionX The x position of the infected on the map.
         * @param positionY The y position of the infected on the map.
         * @param hit_points The hit points of the infected.
         * @param radius The radius of the infected.
         */
        Infected(uint32_t id, uint32_t positionX, uint32_t positionY, int32_t hit_points, uint32_t radius);

        /**
         * @brief Used by the infected to setMove, generally after setChase.
        */
        virtual void move(int32_t x_movement, int32_t y_movement) override = 0;
        /**
         * @brief Used to update the entity, here it's virtual
         */
        virtual void update(Map& map) override = 0;
        
        /**
         * @brief Used to shoot, infected don;t shoot so here it does nothing.
         */
        virtual void shoot(std::vector<HitEntity>& entities_hit) override;
        
        /**
         * @brief Used to know if the entity is infected, it should always return true.
         * @return true
         */
        virtual bool isInfected() override;

        /**
         * @brief Used to know if the entity is a soldier, it should always return false.
         * @return false
         */
        virtual bool isSoldier() override;

        /**
         * @brief Used to know the entity type.
         * @return a string with the entity type.
         */
        virtual std::string getEntityType() override = 0;
        
        /**
         * @brief ChecksIfASoldier is in Range, if it is, sets the chase.
         * @param soldiers A map of all the (alive)soldiers in the game.
         */        
        virtual void checkForSoldiersInRangeAndSetChase(std::map<u_int32_t, Entity*> &soldiers) = 0;
        
        /**
         * @brief ChecksIfASoldier is in Range, if it is, sets the attack.
         * @param soldiers A map of all the (alive)soldiers in the game.
         */
        virtual void checkForSoldiersInRangeAndSetAttack(std::map<u_int32_t, Entity*> &soldiers) = 0;

        /**
         * @brief used by all the infected that do a basic check for chasing.
         * @param soldiers A map of all the (alive)soldiers in the game.
         * @param range The range of the check.
         */
        void checkForSoldiersInRangeAndSetChaseWithRange(std::map<u_int32_t, Entity*> &soldiers, const int32_t &range);
        
        /**
         * @brief used by all the infected that do a basic check for attacking.
         * @param soldiers A map of all the (alive)soldiers in the game.
         * @param range The range of the check.
         */        
        void checkForSoldiersInRangeAndSetAttackWithRange(std::map<u_int32_t, Entity*> &soldiers, const int32_t &range);
        /**
         * @brief Sets the movement towards the entity passed.
         * @param entity The entity you want to chase.
         */  
        virtual void setChase(Entity* entity) = 0;
        
        /**
         * @brief Sets the damage of the round to the entity passed
         * @param entity The entity you want to attack.
         */            
        virtual void setAttack(Entity* entity) = 0;
        
        /**
         * @brief makes the infected stronger. 
         */
        virtual void makeStronger(double factor) = 0;

        /**
         * @brief Used to know the state of the entity.
         * @return a string with the entity state.
         */
        virtual std::string getState() override;

        /**
         * @brief Used to know if an entity is in a given range.
         * @param entity The entity you want to check.
         * @param range The range you want to check.
         * @return true if the entity is in range, false otherwise. 
         */
        bool isInRange(Entity* entity, const int32_t &range);
        
        /**
         * @brief Used to move the infected to the middle, usually after spawning. 
         */
        void moveToMiddle();
        
        /**
         * @brief It sets an increible ammount of damage to the infected (killing it).
         */
        void killCheat();

        /**
         * @brief Destructor, does nothing but is needed because of polymorphism.
         */
        virtual ~Infected() override;
    private:
        /**
         * @brief Used for the toroidal map, checks if the entity is in range on the x axis. 
         */
        bool checkForBorderCaseRange(const int32_t &soldier_x,const int32_t &infected_x,const int32_t &range);
};
#endif
