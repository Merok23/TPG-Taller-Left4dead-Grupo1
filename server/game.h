#ifndef GAME_H_
#define GAME_H_

#include <cstdint>
#include <map>
#include <functional>

#include "vector_wrapper.h"
#include "../common/queue.h"
#include "game_state_for_client.h"
#include "entity.h"
#include "map.h"
#include "hit_entity.h"


class Game {
    private: 
        std::map<u_int32_t, Entity*> entities;
        Map gameMap;
    public:
        explicit Game(int32_t width, int32_t height);
        void addEntity(Entity* entity);
        void setMoving(const uint32_t& id, const int8_t &x,const int8_t &y);
        void setShooting(const uint32_t& id);
        std::map<u_int32_t, Entity*>& getEntities();
        std::shared_ptr<GameStateForClient> update();
    private:
        std::vector<HitEntity> setUpHitEntities(const std::vector<VectorWrapper>& entities_hit);
};

#endif //GAME_H_