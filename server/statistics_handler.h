#ifndef STATISTICS_HANDLER_H
#define STATISTICS_HANDLER_H

#include <mutex>
#include <fstream>
#include <vector>
#include <algorithm>

class StatisticsHandler {
    private: 
    std::vector<uint32_t> infected_kills_top_10;
    std::vector<uint32_t> ammo_used_top_10;
    std::vector<uint32_t> time_alive_top_10;
    std::mutex mutex;

    void saveAllStatistics(std::ofstream& file);
    void updateList(std::vector<uint32_t> list, uint32_t value);
    public:
    StatisticsHandler();
    void updateStatistics(uint32_t infected_kills, uint32_t ammo_used, uint32_t time_alive);
    ~StatisticsHandler();
};
#endif