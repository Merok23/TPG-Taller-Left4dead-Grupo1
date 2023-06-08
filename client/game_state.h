#ifndef CLIENT_GAME_STATE_H
#define CLIENT_GAME_STATE_H
#include "entity.h"
#include <map>
class GameState {
    public:
    std::map<uint32_t, std::shared_ptr<Entity>> entities;

    explicit GameState(const std::map<u_int32_t, std::shared_ptr<Entity>>& entities);
    void print();
    ~GameState();
}; 
#endif
