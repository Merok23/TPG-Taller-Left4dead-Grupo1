#ifndef ENTITY_INFECTED_VENOM_H
#define ENTITY_INFECTED_VENOM_H

#include <vector>
#include <map>
#include <utility>
#include <algorithm>
#include <string>

#include "entity_infected.h"
#include "config.h"

enum VenomInfectedState {
    IDLE_VENOM_INFECTED,
    MOVING_VENOM_INFECTED,
    DEAD_VENOM_INFECTED,
    BLASTING_VENOM_INFECTED,
    SHOOTING_VENOM_INFECTED
};
/**
 * @class VenomInfected
 * @brief VenomInfected is a type of Infected, it has a blast attack and a shoot attack(ranged). 
 */
class VenomInfected : public Infected {
    private:
        VenomInfectedState state; /**< State of Venom. */
        int32_t look_range; /**< Range where Venom can chase you. */
        int32_t blast_range; /**< Range of blast attack. */
        int32_t shoot_range; /**< Range of shoot attack. */
        int32_t blast_damage; /**< Damage of the blast attack. */
        int32_t incapacitated; /**< Incapacitated counter, while is greater than 0, Venom does nothing. */
        int32_t speed; /**< Speed of Venom. */
        int32_t blast_incapacitated_time; /**< Time before Venom goes to idle after blast, used for animations. */
        int32_t shoot_incapacitated_time; /**< Time before Venom goes to idle after shoot, used for animations. */
        int32_t shoot_attack_counter; /**< Counter for shoot attack, used for animations. */
        int32_t shoot_attack_timing; /**< Time for the counter to reach. */
        int32_t blast_attack_counter; /**< Counter for blast attack, used for animations. */
        int32_t blast_attack_timing; /**< Time for the counter to reach, used for doing damage too. */
        int32_t blast_radius; /**< Radius of blast attack. */
        int32_t projectile_radius; /**< Radius of projectile attack (hitbox). */
        
    public:
        /**
         * @brief Constructor
         * @param id All Entities have an id, this is the Venom's id.
         * @param positionX The x position of Venom on the map.
         * @param positionY The y position of Venom on the map. 
         */
        VenomInfected(uint32_t id, uint32_t positionX, uint32_t positionY);
        
        /**
         * @brief Used to set the direction of movement of entities, it should be called setMove()
         * @param x_movement The direction of movement you want to set on the x axis.
         * @param y_movement The direction of movement you want to set on the y axis.
         */
        virtual void move(int32_t x_movement, int32_t y_movement) override;
        
        /**
         * @brief Update is where Venom moves, attacks, chases, etc. depending
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
         * @brief Makes Venom stronger by a factor.
         * @param factor The factor you want to make Venom stronger by.
         */        
        virtual void makeStronger(double factor) override;
        
        /**
         * @brief Used to know the state of Venom
         * @returns "idle", "moving", "attacking", "blasting", "shooting" or "dead".
         */        
        virtual std::string getState() override; 
        
        /**
         * @brief Used to know the type of entity
         * @returns "venom"
         */
        virtual std::string getEntityType() override;
        
        /**
         * @brief Used to know the shooting range of venom
         * @returns shoot_range (could change with makeStronger)
         */
        int32_t getShootingRange();
        
        /**
         * @brief Used to know the blast position.
         * @returns Movement with the position of the blast in it.
         */
        Movement getBlastPosition();
        
        /**
         * @brief Sets the movement towards the entity passed.
         * @param entity The entity you want to chase.
         */        
        void setChase(Entity* entity) override;
        
        /**
         * @brief This one is different, it sets the state to blasting,
         *        and initializes the blast attack counter, the attack will happen 
         *        when the counter reaches the timing.
         * @param entity isn't used.
         */        
        void setAttack(Entity* entity) override;
        
        /**
         * @brief Sets the damage for the round to all entities passed.
         * @param entities A vector of all the entities hit by the blast.
         */
        void setBlastDamage(std::vector<Entity*> &entities);
        
        /**
         * @brief Sets the state to shooting, and initializes the shoot attack counter,
         *        the attack will happen when the counter reaches the timing.
         */
        void setShooting();
        
        /**
         * @brief Used to know if Venom is shooting a projectile.
         * @returns true if Venom is shooting a projectile, false otherwise.
         */
        bool isShootingAProjectile();
        
        /**
         * @brief Used to know if it's time for blasting (blast counter == blast timing)
         * @returns true if it's time. false otherwise.
         */
        bool isTimeForBlasting();
        
        /**
         * @brief Used to know if it's time for shooting (shoot counter == shoot timing)
         * @returns true if it's time. false otherwise.
         */
        bool isTimeForShooting();
        
        /**
         * @brief Used to know where to create a projectile.
         * @returns tuple of position x and y, where the projectile should be created.
         */
        std::tuple<uint32_t, uint32_t> getProjectilePosition();
        
        /**
         * @brief Used to know if Venom is dead
         * @returns True if Venom is dead, false otherwise.
         */        
        virtual bool isDead() override;
};
#endif
