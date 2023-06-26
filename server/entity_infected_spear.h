#ifndef SERVER_ENTITY_INFECTED_SPEAR_H
#define SERVER_ENTITY_INFECTED_SPEAR_H

#include "entity_infected.h"
#include "config.h"

#include <algorithm>
#include <map>
#include <utility>

enum SpearInfectedState {
    IDLE_SPEAR_INFECTED,
    MOVING_SPEAR_INFECTED,
    DEAD_SPEAR_INFECTED,
    ATTACKING_SPEAR_INFECTED
};

/**
 * @class SpearInfected
 * @brief One of the infected types, it's like the common infected, but stronger.
 */
class SpearInfected : public Infected {
    private:
        SpearInfectedState state; /**< State of Spear. */
        int32_t look_range; /**< Range where Spear can chase you. */
        int32_t attack_range; /**< Range of attack. */
        int32_t attack_cooldown; /**< Ammount of game iterations before another attack. */
        int32_t attack_damage; /**< Damage of the attack. */
        int32_t incapacitated; /**< Incapacitated counter, while is greater than 0, Spear does nothing. */
        int32_t speed; /**< Speed of Spear. */
        int32_t attack_duration; /**< Time before Spear goes to idle, used for animations. */
    public:
        /**
         * @brief Constructor
         * @param id All Entities have an id, this is the Spear's id.
         * @param positionX The x position of Spear on the map.
         * @param positionY The y position of Spear on the map.
         */
        SpearInfected(uint32_t id, uint32_t positionX, uint32_t positionY);
        
        /**
         * @brief Used to move entities, it really should be called "setMove"
         *        since it doesn't actually move the entity, it just sets the direction
         *        and the state, so when it updates, it moves.
         * @param x_movement The direction of movement you want to set on the x axis.
         * @param y_movement The direction of movement you want to set on the y axis. 
         */
        virtual void move(int32_t x_movement, int32_t y_movement) override;
        
        /**
         * @brief Update is where the Spear moves, attacks, chases, etc. depending
         *        on it's state.
         * @param map Used to move the entity on the map. 
         */
        virtual void update(Map& map) override;
        
        /**
         * @brief ChecksIfASoldier is in Range, if it is, sets the chase.
         * @param soldiers A map of all the (alive)soldiers in the game.
         */
        virtual void checkForSoldiersInRangeAndSetChase(std::map<u_int32_t, 
            Entity*> &soldiers) override;
        
        /**
         * @brief ChecksIfASoldier is in Range, if it is, sets the attack.
         * @param soldiers A map of all the (alive)soldiers in the game.
         */
        virtual void checkForSoldiersInRangeAndSetAttack(std::map<u_int32_t, Entity*> &soldiers) override;
        
        /**
         * @brief Makes Spear stronger by a factor.
         * @param factor The factor you want to make Spear stronger by.
         */
        virtual void makeStronger(double factor) override;
        
        /**
         * @brief Used to know if Spear is dead
         * @returns True if Spear is dead, false otherwise.
         */
        virtual bool isDead() override;
        
        /**
         * @brief Used to know the state of Spear
         * @returns "idle", "moving", "attacking", or "dead".
         */
        virtual std::string getState() override; 
        
        /**
         * @brief Used to know the entity type.
         * @returns "spear".
         */
        virtual std::string getEntityType() override;
        
        /**
         * @brief Sets the movement towards the entity passed.
         * @param entity The entity you want to chase.
         */   
        void setChase(Entity* entity) override;
        
        /**
         * @brief Sets the damage of the round to the entitty passed
         * @param entity The entity you want to attack.
         */
        void setAttack(Entity* entity) override;
};
#endif
