#ifndef SERVER_ENTITY_INFECTED_COMMON_H
#define SERVER_ENTITY_INFECTED_COMMON_H

#include <algorithm>
#include <map>
#include <utility>

#include "entity_infected.h"
#include "config.h"

enum CommonInfectedState {
    IDLE_INFECTED,
    MOVING_INFECTED,
    DEAD_INFECTED,
    ATTACKING_INFECTED
};

/**
 * @class CommonInfected
 * @brief One of the infected types, it's the most common one.
 *        It doesn't have any special abilities, it just chases and attacks.
 */
class CommonInfected : public Infected {
    private:
        CommonInfectedState state; /**< State of the infected. */
        int32_t look_range; /**< Range where the infected can chase you. */
        int32_t attack_range; /**< Range of attack. */
        int32_t attack_cooldown; /**< Ammount of game iterations before another attack. */
        int32_t attack_damage; /**< Damage of the attack. */
        int32_t incapacitated; /**< Incapacitated counter, while is greater than 0, infected does nothing. */
        int32_t speed; /**< Speed of the infected. */
        int32_t attack_duration; /**< Time before the infected goes to idle, used for animations. */
    public:
        /**
         * @brief Constructor
         * @param id All Entities have an id, this is the infected's id.
         * @param positionX The x position of the infected on the map.
         * @param positionY The y position of the infected on the map.
         */
        CommonInfected(uint32_t id, uint32_t positionX, uint32_t positionY);
        
        /**
         * @brief Used to move entities, it really should be called "setMove"
         *        since it doesn't actually move the entity, it just sets the direction
         *        and the state, so when it updates, it moves.
         * @param x_movement The direction of movement you want to set on the x axis.
         * @param y_movement The direction of movement you want to set on the y axis. 
         */
        virtual void move(int32_t x_movement, int32_t y_movement) override;
        
        /**
         * @brief Update is where the infected moves, attacks, chases, etc. depending
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
         * @brief Multiplies the stats of the CommonInfected by a factor, making it stronger.
         * @param factor The factor you want to multiply the stats by.
         */
        virtual void makeStronger(double factor) override;
        
        /**
         * @brief Checks if the infected is dead.
         * @return true if it's dead, false otherwise.
         */
        virtual bool isDead() override;
        
        /**
         * @brief Gets the state of the infected.
         * @return "idle", "moving", "dead" or "attacking"
         */
        virtual std::string getState() override; 
        
        /**
         * @brief Gets the type of the infected.
         * @return "common"
         */
        virtual std::string getEntityType() override;
        
        /**
         * @brief Used after spawning from a witch, sets the movement to the witch's direction.
         * @param witch The witch that spawned the infected.
         */
        void setFollowWitch(Entity* witch);
        
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
