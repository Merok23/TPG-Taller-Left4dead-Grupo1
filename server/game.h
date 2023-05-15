#include <cstdint>
#include "entity.h"
#include "../common/queue.h"
#include "../common/action.h"
#include "game_state_for_client.h"
#include "map.h"
#include <map>


class Game {
    private: 
        std::map<u_int32_t, Entity*> entities;
        Map gameMap;
    public:
        Game();
        void addEntity(Entity* entity);
        void setMoving(uint32_t id, int8_t x, int8_t y);
        GameStateForClient update();
        ~Game();
};
