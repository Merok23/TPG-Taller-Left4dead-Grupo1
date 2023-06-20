#include <cstdint>
#include <map>
#include "entity.h"

typedef struct Statistics {
    //if game mode == survival, then ranking = true, because is the only game mode where stadistics have ranking
    bool ranking;
    //save as <ranking, value> if game mode != survival, then ranking =  0
    std::pair<uint8_t, uint32_t> infected_killed_info;
    std::pair<uint8_t, uint32_t> ammo_used_info;
    std::pair<uint8_t, uint32_t> game_time_info;
    
    Statistics() {
        this->ranking = false;
        this->infected_killed_info = std::make_pair(0, 0);
        this->ammo_used_info = std::make_pair(0, 0);
        this->game_time_info = std::make_pair(0, 0);
    }

    void setStatistics(bool ranking, std::pair<uint8_t, uint32_t> infected_killed_info, 
        std::pair<uint8_t, uint32_t> ammo_used_info, 
        std::pair<uint8_t, uint32_t> game_time_info) {
        this->ranking = ranking;
        this->infected_killed_info = infected_killed_info;
        this->ammo_used_info = ammo_used_info;
        this->game_time_info = game_time_info;
    }

    std::pair<uint8_t, uint32_t> getInfectedKilledInfo() {
        return this->infected_killed_info;
    }

    std::pair<uint8_t, uint32_t> getAmmoUsedInfo() {
        return this->ammo_used_info;
    }   

    std::pair<uint8_t, uint32_t> getGameTimeInfo() {
        return this->game_time_info;
    }

    bool getRanking() {
        return this->ranking;
    }    

} Statistics;

class GameStateForClient {
    private:
        std::map<uint32_t, Entity*> entities;
        uint32_t width;
        uint32_t height;
        bool game_over;
        bool players_won;
        Statistics statistics;

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
        std::pair<uint8_t, uint32_t> getInfectedKilled();
        std::pair<uint8_t, uint32_t> getAmmoUsed();
        std::pair<uint8_t, uint32_t> getGameLoopTime();
        void setStadistics(bool ranking, std::pair<uint8_t, uint32_t> infected_killed_info, 
            std::pair<uint8_t, uint32_t> ammo_used_info, 
            std::pair<uint8_t, uint32_t> game_time_info);
        bool& isGameOver();
        bool& didPlayersWin();
};
