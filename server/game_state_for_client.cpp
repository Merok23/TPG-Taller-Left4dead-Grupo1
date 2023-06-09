#include "game_state_for_client.h"

GameStateForClient::GameStateForClient
    (const std::map<uint32_t, Entity*> &entities, 
    bool game_over, 
    bool players_won) :
    entities(entities),
    game_over(game_over),
    players_won(players_won), 
    statistics() {}

    
std::map<uint32_t, Entity*>& GameStateForClient::getEntities(){
    return this->entities;
}

bool& GameStateForClient::isGameOver() {
    return this->game_over;
}

bool& GameStateForClient::didPlayersWin() {
    return this->players_won;
}

void GameStateForClient::setStadisticsCTZ(bool ranking, std::pair<uint8_t, uint32_t> infected_killed_info, 
    std::pair<uint8_t, uint32_t> ammo_used_info, 
    std::pair<uint8_t, uint32_t> game_time_info) {
        this->statistics.setStatisticsCTZ(ranking, infected_killed_info, ammo_used_info, game_time_info);
}

void GameStateForClient::setStatisticsSurvival(bool ranking, std::pair<uint8_t, uint32_t> infected_killed_info, 
    std::pair<uint8_t, uint32_t> ammo_used_info, 
    std::pair<uint8_t, uint32_t> game_time_info, 
    std::list<uint32_t> infected_kills_top,
    std::list<uint32_t> ammo_used_top_10,
    std::list<uint32_t> time_alive_top) {
        this->statistics.setStatisticsSurvival(ranking, infected_killed_info, ammo_used_info, game_time_info, infected_kills_top, ammo_used_top_10, time_alive_top);
}

Statistics& GameStateForClient::getStatistics() {
    return this->statistics;
}
