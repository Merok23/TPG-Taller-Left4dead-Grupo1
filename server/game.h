#include "entity.h"

#include <cstdint>
#include <map>
#include <functional>

#include "../common/queue.h"
#include "../common/action.h"
#include "game_state_for_client.h"
#include "map.h"


class Game {
    private: 
        std::map<u_int32_t, Entity*> entities;
        Map gameMap;
    public:
        Game(int32_t width, int32_t height);
        void addEntity(Entity* entity);
        void setMoving(uint32_t id, int8_t x, int8_t y);
        GameStateForClient update();
        ~Game();
};
