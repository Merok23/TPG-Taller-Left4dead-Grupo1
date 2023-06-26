#ifndef SERVER_ENTITY_INFECTED_WITCH_H
#define SERVER_ENTITY_INFECTED_WITCH_H

#include <vector>
#include <map>
#include <utility>
#include <algorithm>
#include <string>

#include "entity_infected.h"
#include "config.h"

enum WitchInfectedState {
    IDLE_WITCH_INFECTED,
    MOVING_WITCH_INFECTED,
    DEAD_WITCH_INFECTED,
    ATTACKING_WITCH_INFECTED,
    SHOUTING_WITCH_INFECTED
};

/**
 * @class WitchInfected
 * @brief Witch is a special Infected, it can attack and chase soldiers like the rest,
 *        but it can also scream, spawning common infected.
 */
class WitchInfected : public Infected {
    private:
        WitchInfectedState state; /**< State of Witch. */
        int32_t look_range; /**< Range where Witch can chase you. */
        int32_t attack_range; /**< Range of attack. */
        int32_t attack_cooldown; /**< Cooldown of attack. */
        int32_t attack_damage; /**< Damage of the attack. */
        int32_t incapacitated; /**< Incapacitated counter, while is greater than 0, Witch does nothing. */
        int32_t speed; /**< Speed of Witch. */
        int32_t shout_cooldown; /**< Time Witch is incapacitated by the Shout. */
        double shout_probability; /**< Probability of Witch using Shout. */
        bool has_spawned_infected; /**< Has the Witch spawned infected. */
        int32_t attack_duration; /**< Time before Witch goes idle, used for animations. */
        int32_t shout_minum_distance; /** < Minimum distance for the Witch to use Shout. */
    public:
        /**
         * @brief Constructor
         * @param id All Entities have an id, this is the Witch's id.
         * @param positionX The x position of Witch on the map.
         * @param positionY The y position of Witch on the map.
         */
        WitchInfected(uint32_t id, uint32_t positionX, uint32_t positionY);
        
        /**
         * @brief Used to move entities, it really should be called "setMove"
         *        since it doesn't actually move the entity, it just sets the direction
         *        and the state, so when it updates, it moves.
         * @param x_movement The direction of movement you want to set on the x axis.
         * @param y_movement The direction of movement you want to set on the y axis. 
         */
        virtual void move(int32_t x_movement, int32_t y_movement) override;
        
        /**
         * @brief Update is where Witch moves, attacks, chases, etc. depending
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
         * @brief Makes Witch stronger by a factor.
         * @param factor The factor you want to make Witch stronger by.
         */     
        virtual void makeStronger(double factor) override;
        
        /**
         * @brief Used to know if Witch is dead.
         * @returns True if Witch is dead, false otherwise.
         */
        virtual bool isDead() override;
        
        /**
         * @brief Used to know the state of Witch.
         * @returns "idle", "moving", "attacking", "screaming", or "dead".
         */            
        virtual std::string getState() override;
        
        /**
         * @brief Used to know the type of entity
         * @returns "witch"
         */ 
        virtual std::string getEntityType() override;
        
        /**
         * @brief Used to know if Witch has already spawned infected.
         * @returns true if Witch spawned infected, false if it didn't
         */
        bool hasSpawnedInfected();
        
        /**
         * @brief Used to tell Witch that it has spawned infected.
         */
        void setSpawnedInfected();
        
        /**
         * @brief Used to know if Witch is shouting.
         * @returns true if Witch is shouting, false if it isn't
         */
        bool isShouting();
        
        /**
         * @brief Used to know if a given position is in distance for Witch to shout.
         * @returns true if Witch is in distance, false if it isn't
         */
        bool isInDistanceForShouting(const int32_t &position_x);

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
}; //end WitchInfected
#endif
