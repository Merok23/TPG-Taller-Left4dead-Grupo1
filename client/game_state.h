#ifndef CLIENT_GAME_STATE_H
#define CLIENT_GAME_STATE_H
#include "entity.h"
#include <map>
class GameState {
    private:
    std::map<u_int32_t, Entity*> entities;

    public: 
    explicit GameState(const std::map<u_int32_t, Entity*>& entities);

}; 

#endif