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
        Queue<Action*> actions; //queue bloqueante por donde van a entrar todos los comandos
        Map gameMap;
    public:
        Game();
        void addEntity(Entity* entity);
        GameStateForClient getGameState();
        void resolveAction(Action* newAction);
        void removeEntity(int id);
        ~Game();
};
