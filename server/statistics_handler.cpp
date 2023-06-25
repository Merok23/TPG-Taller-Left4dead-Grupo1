#include "statistics_handler.h"

StatisticsHandler statistics_handler;

StatisticsHandler::StatisticsHandler() : infected_kills_top_10(), ammo_used_top_10(), time_alive_top_10(), ranking_size(10), was_updated(false),mutex() {
    std::ifstream file("../statistics.txt", std::ios::in);
    std::string line;
    if (file.is_open()) {
        while (std::getline(file, line)) {
            if (std::isdigit(line[0]) && this->infected_kills_top_10.size() < this->ranking_size) {
                this->infected_kills_top_10.push_back(std::stoi(line));
            }
            else if (std::isdigit(line[0]) && this->ammo_used_top_10.size() < this->ranking_size) {
                this->ammo_used_top_10.push_back(std::stoi(line));
            }
            else if (std::isdigit(line[0]) && this->time_alive_top_10.size() < this->ranking_size) {
                this->time_alive_top_10.push_back(std::stoi(line));
            }
            
        }
    }
    file.close();
}



void StatisticsHandler::updateList(std::list<uint32_t>& vector, uint32_t& value) {
    if (!vector.empty()) vector.pop_back();
    auto it = std::find_if(vector.rbegin(), vector.rend(), [value](int elemento) {
        return elemento > (int)value;
    });

    vector.insert(it.base(), value);
}

void StatisticsHandler::updateStatistics(uint32_t& infected_kills, uint32_t& ammo_used, uint32_t& time_alive) {
    std::unique_lock<std::mutex> lock(mutex);

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
}

void StatisticsHandler::saveAllStatistics() {
    if (!was_updated) return;
    std::ofstream file("../statistics.txt", std::ofstream::out | std::ofstream::trunc);

    if (!file.is_open()) {
        std::cout << "ERROR: Can't open statistics file" << std::endl;
        return;
    }


    file << "TOP 10: Infected kills" << std::endl;
    for (const auto& infected_kills : this->infected_kills_top_10) {
        file << infected_kills << std::endl;
    }
    file << std::endl;

    file << "TOP 10: Ammo used " << std::endl;
    for (const auto& ammo_used : this->ammo_used_top_10) {
        file << ammo_used << std::endl;
    }
    file << std::endl;

    file << "TOP 10: Time alive " << std::endl;
    for (const auto& time_alive : this->time_alive_top_10) {
        file << time_alive << std::endl;
    }
    file << std::endl;
    file.close();
}

std::list<uint32_t> StatisticsHandler::getInfectedKillsTop10() {
    std::unique_lock<std::mutex> lock(mutex);
    return this->infected_kills_top_10;
}

std::list<uint32_t> StatisticsHandler::getAmmoUsedTop10() {
    std::unique_lock<std::mutex> lock(mutex);
    return this->ammo_used_top_10;
}

std::list<uint32_t> StatisticsHandler::getTimeAliveTop10() {
    std::unique_lock<std::mutex> lock(mutex);
    return this->time_alive_top_10;
}

StatisticsHandler::~StatisticsHandler() {}