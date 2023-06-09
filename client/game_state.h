#ifndef CLIENT_GAME_STATE_H
#define CLIENT_GAME_STATE_H
#include "entity.h"
#include <memory>
#include <map>

class GameState {
    public:
    //podria ser unique_ptr???
    std::map<uint32_t, std::shared_ptr<Entity>> entities;
    bool game_over;
    bool players_won;

    explicit GameState(const std::map<u_int32_t, std::shared_ptr<Entity>>& entities, 
        bool game_over, 
        bool players_won);
    void print();
    ~GameState();
}; 
#endif
