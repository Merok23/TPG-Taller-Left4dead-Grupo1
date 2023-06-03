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
#include "entity_player.h"

class Game {
    private: 
        std::map<uint32_t, Entity*> entities;
        Map gameMap;
        std::map<uint32_t, Entity*> infected;
        std::map<uint32_t, Entity*> soldiers;
        /*
         * Shooting soldiers as a list has a funny bug
         * if you shoot twice with one soldier, for example 
         * it will try to shoot twice, but for doing that
         * you have to press two attack buttons at the same time
         * which is not possible, so it's not a big deal
         * the solution is changing to a map.
        */
        std::list<uint32_t> shooting_soldiers;
        uint32_t current_id;
        
    public:
        explicit Game(int32_t width, int32_t height);
        void addEntity(Entity* entity);
        void removeEntity(const uint32_t& id);
        void setMoving(const uint32_t& id, const int32_t &x,const int32_t &y);
        void setShooting(const uint32_t& id);
        void stopShooting(const uint32_t& id);
        void setReloading(const uint32_t& id);
        std::map<uint32_t, Entity*>& getEntities();
        std::shared_ptr<GameStateForClient> update();
        void infectedCheckForSoldiersInRange();
        uint32_t getCurrentId();
        ~Game();
        
    private:
        void shootingEntitiesShoot(const uint32_t& id);
        void updateAllEntities();
        void checkForShooting();
        void checkForInfectedAttack();
        std::vector<HitEntity> setUpHitEntities(const std::vector<VectorWrapper>& entities_hit);
};
#endif 
