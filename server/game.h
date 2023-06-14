#ifndef GAME_H_
#define GAME_H_

#include <cstdint>
#include <map>
#include <list>
#include <functional>
#include <vector>
#include <memory>
#include <algorithm>

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
#include "server_enum.h"

enum Cheat {
    INFINITE_HITPOINTS,
    SPAWN_COMMON_INFECTED,
    KILL_ALL_INFECTED
};


class Game {
    private: 
        std::map<uint32_t, Entity*> entities;
        Map gameMap;
        std::map<uint32_t, Entity*> infected;
        std::map<uint32_t, Entity*> soldiers;
        std::map<uint32_t, WitchInfected*> witches;
        /*
         * Shooting soldiers as a list has a funny bug
         * if you shoot twice with one soldier for example 
         * it will try to shoot twice. but for doing that
         * you'll have to press two attack buttons at the same time
         * which is not possible, so it's not a big deal
         * the solution is changing it to a map.
        */
        std::list<uint32_t> shooting_soldiers;
        bool clear_the_zone;
        bool zone_is_set;
        int clear_the_zone_max_infected;
        bool survival_mode;
        int survival_mode_counter;
        int max_common_infected_per_spawn;
        int max_spear_infected_per_spawn;
        int max_witch_infected_per_spawn;
        double survival_mode_multiplier;
        uint32_t current_id;
        bool game_started;
        bool game_over;
        bool players_won;
        bool craters_have_spawned;
        
    public:
        explicit Game(int32_t width, int32_t height);
        Game(int32_t width, int32_t height, GameMode gameMode);
        void addEntity(Entity* entity);
        void removeEntity(const uint32_t& id);
        void setMoving(const uint32_t& id, const int32_t &x,const int32_t &y);
        void setShooting(const uint32_t& id);
        void stopShooting(const uint32_t& id);
        void setReloading(const uint32_t& id);
        void setCheat(const uint32_t& id, const Cheat& cheat);
        std::map<uint32_t, Entity*>& getEntities();
        std::shared_ptr<GameStateForClient> update();
        void infectedCheckForSoldiersInRange();
        uint32_t getCurrentId();
        void setSurvivalMode();
        void checkForRevivingSoldiers();
        ~Game();
        
    private:
        void shootingEntitiesShoot(const uint32_t& id);
        void updateAllEntities();
        void checkForShooting();
        void checkForInfectedAttack();
        void checkForGameOver();
        void checkForScreamingWitches();
        bool checkForPartyWipe();
        //unique ptr so we don't copy the vector more than once
        //std::unique_ptr<std::vector<HitEntity>> setUpHitEntities(std::vector<VectorWrapper>& entities_hit);
        //For some reason unique ptr version doesn't compile even we have the C++17 standard (preguntar)
        std::vector<HitEntity> setUpHitEntities(std::vector<VectorWrapper>& entities_hit);
        void survivalUpdate();
        void spawnInfected();
        void spawnCraters(int ammount);
        void spawnCratersAtTheBorder();
        void spawnCommonInfected(int ammount);
        void spawnSpearInfected(int ammount);
        void spawnWitchInfected(int ammount);
        void spawnInfectedCheat(const uint32_t& id);
        void spawnWitchInfectedFromScream(const uint32_t& id);
        void killAllInfectedCheat();
        bool searchForPosition(const uint32_t& radius, uint32_t &x, uint32_t &y);
        void makeInfectedStronger();
        void setTheZone();
};
#endif 
