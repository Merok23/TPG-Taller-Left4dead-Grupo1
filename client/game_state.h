#ifndef CLIENT_GAME_STATE_H
#define CLIENT_GAME_STATE_H
#include "entity.h"
#include <memory>
#include <map>

class GameState {
    public:
    //podria ser unique_ptr???
    std::map<uint32_t, Entity*> entities;
    bool game_over;
    bool players_won;
    bool lost_connection;
    uint32_t ammo_used;
    uint32_t infected_killed;
    uint32_t game_loop_time;
    
    GameState();
    explicit GameState(const std::map<u_int32_t, Entity*>& entities, 
        bool game_over, 
        bool players_won);
    
    explicit GameState(const std::map<u_int32_t, Entity*>& entities, 
        bool game_over, 
        bool players_won, 
        uint32_t ammo_used,
        uint32_t infected_killed,
        uint32_t game_loop_time);
    
    uint32_t getInfectedKilled();
    uint32_t getAmmoUsed();
    uint32_t getGameLoopTime();
    void setLostConnection();
    ~GameState();
}; 
#endif
