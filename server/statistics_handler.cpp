#include "statistics_handler.h"


StatisticsHandler::StatisticsHandler() : infected_kills_top_10(10), ammo_used_top_10(10), time_alive_top_10(10), mutex() {}

void StatisticsHandler::updateList(std::vector<uint32_t> vector, uint32_t value) {
    if (!vector.empty()) vector.pop_back();
    auto it = std::find_if(vector.rbegin(), vector.rend(), [value](int elemento) {
        return elemento < value;
    });

    vector.insert(it.base(), value);
}

void StatisticsHandler::updateStatistics(uint32_t infected_kills, uint32_t ammo_used, uint32_t time_alive) {
    std::unique_lock<std::mutex> lock(mutex);
    bool was_updated = false;

    if (infected_kills > this->infected_kills_top_10.back()) {
        this->updateList(this->infected_kills_top_10, infected_kills);
        was_updated = true;
    }

    if (ammo_used > this->ammo_used_top_10.back()) {
        this->updateList(this->ammo_used_top_10, ammo_used);
        was_updated = true;
    }

    if (time_alive > this->time_alive_top_10.back()) {
        this->updateList(this->time_alive_top_10, time_alive);
        was_updated = true;
    }

    if (was_updated) {
        std::ofstream file;
        file.open("statistics.txt");
        this->saveAllStatistics(file);
        file.close();
    }
}

void StatisticsHandler::saveAllStatistics(std::ofstream& file) {
    file << "TOP 10: Infected kills";
    for (const auto& infected_kills : this->infected_kills_top_10) {
        file << infected_kills << " ";
    }
    file << std::endl;

    file << "TOP 10: Ammo used ";
    for (const auto& ammo_used : this->ammo_used_top_10) {
        file << ammo_used << " ";
    }
    file << std::endl;

    file << "TOP 10: Time alive ";
    for (const auto& time_alive : this->time_alive_top_10) {
        file << time_alive << " ";
    }
    file << std::endl;
}