#include <cstdint>
#include <map>
#include "entity.h"


class GameStateForClient {
    private:
        std::map<uint32_t, Entity*> entities;
        uint32_t width;
        uint32_t height;
        bool game_over;
        bool players_won;
        uint32_t ammo_used;
        uint32_t infected_killed;
        uint32_t game_loop_time; 
    public:
        GameStateForClient(const std::map<uint32_t, Entity*> &entities, 
            uint32_t width,
            uint32_t height, 
            bool game_over, 
            bool players_won);
        explicit GameStateForClient(GameStateForClient*& other);
        std::map<uint32_t, Entity*>& getEntities();
        uint32_t getWidth();
        uint32_t getHeight();
        uint32_t getInfectedKilled();
        uint32_t getAmmoUsed();
        uint32_t getGameLoopTime();
        void setGameLoopTime(uint32_t time);
        void setInfectedKilled(uint32_t infected_killed);
        void setAmmoUsed(uint32_t ammo_used);
        bool& isGameOver();
        bool& didPlayersWin();
};
