#ifndef STATISTICS_HANDLER_H
#define STATISTICS_HANDLER_H

#include <mutex>
#include <fstream>
#include <list>
#include <algorithm>
#include <iostream>


class StatisticsHandler {
    private: 
    std::list<uint32_t> infected_kills_top_10;
    std::list<uint32_t> ammo_used_top_10;
    std::list<uint32_t> time_alive_top_10;
    uint8_t ranking_size;
    bool was_updated;
    std::mutex mutex;

    void updateList(std::list<uint32_t>& list, uint32_t& value);
    public:
    StatisticsHandler();
    void updateStatistics(uint32_t& infected_kills, uint32_t& ammo_used, uint32_t& time_alive);
    std::list<uint32_t> getInfectedKillsTop10();
    std::list<uint32_t> getAmmoUsedTop10();
    std::list<uint32_t> getTimeAliveTop10();
    void saveAllStatistics();
    ~StatisticsHandler();
};

extern StatisticsHandler statistics_handler;

#endif
