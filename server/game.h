#ifndef GAME_H_
#define GAME_H_

#include <cstdint>
#include <map>
#include <list>
#include <functional>
#include <vector>
#include <memory>
#include <algorithm>
#include <random>

#include "vector_wrapper.h"
#include "../common/queue.h"
#include "game_state_for_client.h"
#include "entity.h"
#include "map.h"
#include "hit_entity.h"
#include "entity_infected.h"
#include "entity_crater.h"
#include "entity_player.h"
#include "entity_infected_common.h"
#include "entity_infected_spear.h"
#include "entity_infected_witch.h"
#include "entity_infected_venom.h"
#include "entity_projectile_venom.h"
#include "server_enum.h"

/**
 * @class Game
 * @brief Here is the meat of the server, it's the class that handles
 *        all the game logic.
 *        The game is divided in rounds, and it's updated in a "lazy" manner
 *        that means all the actions are executed set a "state", and then, when
 *        the game updates, all the entities do what their states tell them to do. 
 */
class Game {
    private: 
        //Entities should be shared_ptr<Entity>, if not, it can't be deleted mid game and 
        //will grow infinetly until the game ends.
        std::map<uint32_t, Entity*> entities; /**< Entities of the game, dead or alive. */
        Map gameMap; /**< Game map, used for calculating and isolating collision logic. */
        std::map<uint32_t, Entity*> infected; /**< Infected in the game, used for optimizations on the logic. */
        std::map<uint32_t, Entity*> soldiers; /**< Soldiers in game, used for optimizations on the logic. */
        std::map<uint32_t, WitchInfected*> witches; /**< Witches in game. (alive) */
        std::map<uint32_t, VenomInfected*> venoms; /**< Alive Venoms. */
        std::map<uint32_t, Projectile*> projectiles; /**< Projectiles. */
        /*
         * Shooting soldiers as a list has a funny bug
         * if you shoot twice with one soldier for example 
         * it will try to shoot twice. but for doing that
         * you'll have to press two attack buttons at the same time
         * which is not possible, so it's not a big deal
         * the solution is changing it to a map.
        */
        std::list<uint32_t> shooting_soldiers; /**< Soldiers that are shooting this round. */
        bool clear_the_zone; /**< Is the game mode clear the zone? */
        bool zone_is_set; /**< Has the zombies for clear the zone spawned.*/
        int clear_the_zone_max_infected; /**< Maximum amount of infected per game. */
        bool survival_mode; /**< Is the game set to survival mode? */
        int survival_mode_counter; /**< Counter used for spawning in survival. */
        int max_common_infected_per_spawn; /**< Max common infected per spawn. (survival) */
        int max_spear_infected_per_spawn; /**< Max Spear infected per spawn (survival) */
        int max_witch_infected_per_spawn; /**< Max witch infected per spawn (survival) */
        int max_venom_infected_per_spawn; /**< Max venom infected per spawn (survival) */
        int max_jumper_infected_per_spawn; /**< Max jumper infected per spawn (survival) */
        double survival_mode_multiplier; /**< Multiplier for survival mode. (makes it harder as time goes on)*/
        uint32_t current_id; /**< Current ID for entities of the game. */
        bool game_started; /**< Has a player spawned? */
        bool game_over; /**< Is the game over? */
        bool players_won; /**< Have the players won? (Clear the Zone)*/
        bool craters_have_spawned; /**< Have craters already spawned? */
        //random number generator:
        std::mt19937 rng;
        std::uniform_int_distribution<int> dist;

        
    public:
        /**
         * @brief Constructor for the game.
         * @param width Width of the game map.
         * @param height Height of the game map.
         */
        explicit Game(int32_t width, int32_t height);
        
        /**
         * @brief Constructor for the game.
         * @param width Width of the game map.
         * @param height Height of the game map.
         * @param gameMode Game mode of the game (test, survival, clear the zone). 
         */
        Game(int32_t width, int32_t height, GameMode gameMode);

        /**
         * @brief Adds an entity to the game.
         * @param entity Entity to be added. 
         */
        void addEntity(Entity* entity);

        /**
         * @brief Adds a soldier to the game.
         * @param weapon Weapon of the soldier.
         * @param name Name of the soldier.
         * @returns Game ID of the soldier.
         */
        uint32_t addPlayer(Weapon* weapon, std::string name);

        /**
         * @brief Gives a possible spawnPoint for a player
         * @return Tuple with the x and y of the spawn point. 
         */
        std::tuple<int, int> getPlayerSpawnPoint();

        /**
         * @brief Removes an entity from all the maps that are not entities.
         * @param id ID of the entity to be removed. 
         */
        void removeEntity(const uint32_t& id);

        /**
         * @brief Sets the movement of the given id to the direction given.
         * @param id ID of the entity to be set.
         * @param x Direction in the x axis. 
         * @param y Direction in the y axis.
         */
        void setMoving(const uint32_t& id, const int32_t &x,const int32_t &y);

        /**
         * @brief Sets given id (soldier) to shoot this round.
         * @param id ID of the soldier to be set. 
         */
        void setShooting(const uint32_t& id);

        /**
         * @brief Sets given id (soldier) to stop shooting this round.
         * @param id ID of the soldier to be set. 
         */
        void stopShooting(const uint32_t& id);

        /**
         * @brief Sets given id (soldier) to reload.
         * @param id ID of the soldier to be set.
         */
        void setReloading(const uint32_t& id);

        /**
         * @brief Sets a given cheat to be executed this round
         *        (kill all infected, infinite hp, or spawn infected)
         * @param id ID of the soldier to be set.
         * @param cheat Cheat to be executed.
         */
        void setCheat(const uint32_t& id, const Cheat& cheat);

        /**
         * @brief Obtains the map entities, used for returning the game state.
         * @returns Map of entities. 
         */
        std::map<uint32_t, Entity*>& getEntities();

        /**
         * @brief updates all the entities and does a lot of checks for game logic.
         */
        std::shared_ptr<GameStateForClient> update();

        /**
         * @brief Obtains the current free ID for entities.
         * @returns Current free ID for entities. 
         */
        uint32_t getCurrentId();

        /**
         * @brief Sets the game mode to survival.
         */
        void setSurvivalMode();

        /**
         * @brief Gets the amount of ammo used by the soldier in the game.
         * @param id ID of the soldier.
         * @returns Amount of ammo used by the soldier. 
         */
        uint32_t getAmountOfAmmoUsedBySoldier(const uint32_t& id);

        /**
         * @brief Gets the amount of infected killed by the soldier in the game.
         * @param id ID of the soldier.
         * @returns Amount of infected killed by the soldier. 
         */
        uint32_t getAmountOfInfectedKilledBySoldier(const uint32_t& id);

        /**
         * @brief Gets the time the soldier spent alive in the game.
         * @param id ID of the soldier.
         * @returns Time the soldier spent alive in the game in seconds.  
         */
        uint32_t getTimeOfDeathOfSoldier(const uint32_t& id);

        /**
         * @brief Destructor for the game.
         *       Deletes all the entities in the game. (frees) 
         */
        ~Game();
        
    private:
        /**
         * @brief Adds a new projectile to the game.
         * @param projectile Projectile to be added. 
         */
        void addProjectile(Projectile* projectile);

        /**
         * @brief Checks for any players in range of infected and sets chase or attacks. 
         */
        void infectedCheckForAttackAndChase();

        /**
         * @brief Checks for soldier in range for chasing.
         * @param alive_soldiers Map of alive soldiers.
         */
        void infectedCheckForSoldiersInRange(std::map<uint32_t, Entity*> &alive_soldiers);

        /**
         * @brief Checks for soldier in range for attacking. 
         * @param alive_soldiers Map of alive soldiers.
         */
        void checkForInfectedAttack(std::map<uint32_t, Entity*> &alive_soldiers);

        /**
         * @brief Checks if the soldier passed by id is shooting, if it is, it gives them
         *        the entities hit.
         * @param id ID of the soldier. 
         */
        void shootingEntitiesShoot(const uint32_t& id);

        /**
         * @brief Updates all the game entities. 
         */
        void updateAllEntities();

        /**
         * @brief Makes all shooting soldiers shoot.
         */
        void checkForShooting();

        /**
         * @brief Checks the game conditions for a game over. 
         */
        void checkForGameOver();

        /**
         * @brief Checks if any witch is screaming and if it is,
         *        it checks if it can shout, if it can, then spawns infected. 
         */
        void checkForScreamingWitches();

        /**
         * @brief Checks if any projectile made it's target. 
         */
        void checkForCollidingProjectiles();

        /**
         * @brief Checks for any venom that is blasting
         *        if it is, it checks if it's time, and then, it gives
         *        them the entities hit. 
         */
        void checkForBlastingVenoms();

        /**
         * @brief Checks for any venom that is shooting
         *        if they are, it checks if it's time, and then creates the projetile. 
         */
        void checkForShootingVenoms();

        /**
         * @brief Checks if any soldier is in conditions to revive.
         *        if it is, it sets the reviving state on them. 
         */
        void checkForRevivingSoldiers();

        /**
         * @brief Checks if the soldiers died.
         * @returns True if all the soldiers died, false otherwise. 
         */
        bool checkForPartyWipe();
        //unique ptr so we don't copy the vector more than once
        //std::unique_ptr<std::vector<HitEntity>> setUpHitEntities(std::vector<VectorWrapper>& entities_hit);
        //For some reason unique ptr version doesn't compile even we have the C++17 standard (preguntar)
        std::vector<HitEntity> setUpHitEntities(std::vector<VectorWrapper>& entities_hit);

        /**
         * @brief Makes a survival update(Checks if it has to spawn zombies)
         *        or make them stronger, if it has, then it does. 
         */
        void survivalUpdate();

        /**
         * @brief Spawns infected for the survival mode. 
         */
        void spawnInfected();

        /**
         * @brief Spawns 'amount' of given infected at the borders of the map.
         * @param type Type of infected to be spawned.
         * @param amount Amount of infected to be spawned.
         */
        void spawnSpecificInfected(const InfectedType &type, const int &amount);
        
        /**
         * @brief Spawns 'amount' of given infected at the end of the map. 
         * @param type Type of infected to be spawned.
         * @param amount Amount of infected to be spawned.
         */
        void spawnSpecificInfectedAtEnd(const InfectedType &type, const int &amount);

        /**
         * @brief Creates a new infected (heap) of the given type.
         * @param type Type of infected to be created.
         * @param id ID of the infected.
         * @param x X coordinate of the infected.
         * @param y Y coordinate of the infected.
         * @returns Pointer to the created infected. 
         */
        Entity* createInfected(const InfectedType &type, const uint32_t &id, const uint32_t &x, const uint32_t &y);
        
        /**
         * @brief Converts the type of given infected to it's radius.
         * @param type Type of infected.
         * @returns Radius of the infected. 
         */
        int32_t typeToRadius(const InfectedType &type);

        /**
         * @brief Spawns 'amount' of given craters anywhere on the map. 
         */
        void spawnCraters(int amount);

        /**
         * @brief Spawns craters at the border so the player can't go there. 
         */
        void spawnCratersAtTheBorder();

        /**
         * @brief Executes the spawn infected cheat, 
         *        spawning a common infected to the right of the id given (soldier).
         * @param id ID of the soldier.
         */
        void spawnInfectedCheat(const uint32_t& id);

        /**
         * @brief Spawns common infected caused by the witche's scream.
         * @param id ID of the witch. 
         */
        void spawnWitchInfectedFromScream(const uint32_t& id);

        /**
         * @brief Kills all the infected in the map. 
         */
        void killAllInfectedCheat();

        /**
         * @brief Searches for a free position at the borders, modifies the x and y
         *        coordinates to the position found. if it can't find it in the border
         *        then checks 'radius' to the center of the map and tries again.
         * @param radius Radius of the entity to be spawned.
         * @param x X coordinate of the entity to be spawned.
         * @param y Y coordinate of the entity to be spawned.
         * @returns True if it found a position, false otherwise(it's never false). 
         */
        bool searchForPositionAtBorders(const uint32_t& radius, uint32_t &x, uint32_t &y);

        /**
         * @brief Searches for a free position anywhere, modifies the x and y
         *        coordinates to the position found.
         * @param radius Radius of the entity to be spawned.
         * @param x X coordinate of the entity to be spawned.
         * @param y Y coordinate of the entity to be spawned.
         * @returns True if it found a position, false otherwise(it's never false). 
         */
        bool searchForPositionAnywhere(const uint32_t& radius, uint32_t &x, uint32_t &y);

        /**
         * @brief Searches for a free position at the end of the map, modifies the x and y
         *        coordinates to the position found.
         * @param radius Radius of the entity to be spawned.
         * @param x X coordinate of the entity to be spawned.
         * @param y Y coordinate of the entity to be spawned.
         * @returns True if it found a position, false otherwise(it's never false). 
         */
        bool searchForPositionAtEnd(const uint32_t& radius, uint32_t &x, uint32_t &y);

        /**
         * @brief Searches for a free position at the centre of mass of the soldiers, modifies the x and y 
         *        coordinates to the position found.
         * @param radius Radius of the entity to be spawned.
         * @param x X coordinate of the entity to be spawned.
         * @param y Y coordinate of the entity to be spawned.
         * @returns True if it found a position, false otherwise(it's never false).
         */
        bool searchForPositionCloseToCentreOfMass(const uint32_t& radius, uint32_t &x, uint32_t &y);

        /**
         * @brief Makes all infected stronger.
         *        (Used in the survival mode)
         */
        void makeInfectedStronger();

        /**
         * @brief Sets the zone for the clear the zone mode. 
         */
        void setTheZone();

        /**
         * @brief Gives Venom(id) the soldiers hit by their blast
         * @param id ID of the Venom.
         */
        void setBlastVenom(const uint32_t& id);

        /**
         * @brief Creates a new VenomProjectile (heap) for the given Venom.
         * @param venom Venom that shot the projectile. 
         */
        void createVenomProjectile(VenomInfected* venom);

        /**
         * @brief Filters the dead soldiers from soldiers and then returns it.
         * @returns Map of the alive soldiers.
         */
        std::map<uint32_t, Entity*> getAliveSoldiers();
        //void removeDeadProjectiles();
};
#endif 
