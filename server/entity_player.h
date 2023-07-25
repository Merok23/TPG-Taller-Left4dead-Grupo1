#ifndef SERVER_ENTITY_PLAYER_H
#define SERVER_ENTITY_PLAYER_H

#include <vector>
#include <string>
#include <utility>
#include <algorithm>

#include "entity.h"
#include "movement.h"
#include "config.h"
#include "weapon.h"

enum SoldierState {
    IDLE_SOLDIER,
    MOVING_SOLDIER,
    SHOOTING_SOLDIER,
    RELOADING_SOLDIER,
    DOWN_SOLDIER,
    REVIVING_SOLDIER,
    DEAD_SOLDIER
};

/**
 * @class Player
 * @brief Player is a type of Entity, it has a weapon and can shoot, it represents the soldiers(players). 
 */
class Player : public Entity {
    private:
        SoldierState state; /**< State of Player. */
        Weapon* my_weapon; /**< Weapon of Player. */
        int32_t incapacitated; /**< Incapacitated counter, while is greater than 0, Player does nothing. */
        int32_t reload_cooldown; /**< Time before Player can shoot again. */
        int32_t revival_countdown; /**< Timer for the player revival. */
        int32_t time_until_dead; /**< Time the player can be knocked out before dying. */
        int lives; /**< Amount of times the player can be knocked out.*/
        uint32_t infected_killed; /**< Amount of infected killed by the player. */
        std::chrono::high_resolution_clock::time_point start_time_of_death; /**< Player spawn time. */
        uint32_t time_of_death; /**< Time of death of the soldier. */
        bool infinite_hitpoints; /**< If true, the player will not die. */
        std::string name; /**< Name of the player. */

    public:
        /**
         * @brief Construct a new Player object.
         * 
         * @param id All Entities have an id, this is the Player's id. (not the same as the client id)
         * @param positionX The x position of the Player on the map.
         * @param positionY The y position of the Player on the map.
         * @param weapon Player's weapon.
         */
        Player(uint32_t id, uint32_t positionX, uint32_t positionY, Weapon* weapon);

        /**
         * @brief Used to move entities, it really should be called "setMove"
         *        since it doesn't actually move the entity, it just sets the direction
         *        and the state, so when it updates, it moves.
         * @param x_movement The direction of movement you want to set on the x axis.
         * @param y_movement The direction of movement you want to set on the y axis. 
         */
        virtual void move(int32_t x_movement, int32_t y_movement) override;

        /**
         * @brief Here is where the player moves, dies, revives, shoots, reloads, etc.
         * @param map the map is used for moving the entity in the game. 
         */
        virtual void update(Map& map) override;

        /**
         * @brief Used to shoot, given a vector of entities_hit, it sets the damage.
         * @param entities_hit Vector of entities hit by the shot.
         */
        virtual void shoot(std::vector<HitEntity>& entities_hit) override;
        
        /**
         * @brief Used to reload the weapon on the next update. 
         */
        void setReload();

        /**
         * @brief Used to know if the entity is infected, it should always return false.
         * @return false
         */
        virtual bool isInfected() override;

        /**
         * @brief Used to know if the entity is a soldier, it should always return true.
         * @return true
         */
        virtual bool isSoldier() override;

        /**
         * @brief Used to know the entity type.
         * @return as string that says player + the weapon the player has "player_(weapon)"
         */
        virtual std::string getEntityType() override;

        /**
         * @brief Used to know if the soldier is dead.
         * @return true if the entity is dead, false otherwise.
         */
        virtual bool isDead() override;

        /**
         * @brief Used to know the state of the soldier
         * @return a string with the state: "idle", "moving", "shooting", 
         *         "reloading", "down", "reviving", "dead".
         */
        virtual std::string getState() override;

        /**
         * @brief Used to tell the soldier to stop shooting. 
         */
        void stopShooting();

        /**
         * @brief Used to know how much ammo the soldier has left.
         * @returns the ammo left in his weapon. 
         */
        int32_t getAmmoLeft();

        /**
         * @brief Used to know how many lives the soldier has left.
         * @return lives left.
         */
        uint8_t getLives();

        /**
         * @brief Used to know if the soldier is reviving
         * @returns true if the soldier is reviving, false otherwise. 
         */
        bool isReviving();

        /**
         * @brief Used to know if the soldier is down.
         * @returns true if the soldier is down, false otherwise. 
         */
        bool isDown();

        /**
         * @brief Used to know how many infected the soldier has killed.
         * @returns the amount of infected killed.
         */
        uint32_t getAmmountOfInfectedKilled();

        /**
         * @brief Used to know how many ammo the soldier has used.
         * @returns the amount of ammo used.
         */
        uint32_t getAmmountOfAmmoUsed();

        /**
         * @brief Used to know the time of death of the soldier.
         * @returns the time of death.
         */
        uint32_t getTimeOfDeath();

        /**
         * @brief Sets the state of the soldier to reviving.
         */
        void setReviving();

        /**
         * @brief Sets infinite hitpoints to the player, it can't lose hp. 
         */
        void setInfiniteHitpoints();

        /**
         * @brief Sets the name of the player.
         * @param name The name of the player.
         */
        void setName(const std::string& name);

        /**
         * @brief Gets the name of the player.
         * @return The name of the player.
         */
        std::string getName();
        
        /**
         * @brief Destructor for polymorphism. 
         */
        virtual ~Player() override;
    private:

        /**
         * @brief Removes the infected that are out of the range of the weapon.
         */
        void removeInfectedOutOfRange(std::vector<HitEntity>& entities_hit);
        
        /**
         * @brief Orders the infected by distance to the soldier. 
         */
        void orderByDistance(std::vector<HitEntity>& entities_hit);
};
#endif
