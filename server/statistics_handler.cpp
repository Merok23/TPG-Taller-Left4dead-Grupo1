#include "statistics_handler.h"

StatisticsHandler statistics_handler;

StatisticsHandler::StatisticsHandler() : top_infected_kills(), top_ammo_used(), top_time_alive(), ranking_size(5), was_updated(false),mutex() {
    std::ifstream file("../server/statistics.txt", std::ios::in);
    std::string line;
    if (file.is_open()) {
        while (std::getline(file, line)) {
            if (std::isdigit(line[0]) && this->top_infected_kills.size() < this->ranking_size) {
                this->top_infected_kills.push_back(std::stoi(line));
            }
            else if (std::isdigit(line[0]) && this->top_ammo_used.size() < this->ranking_size) {
                this->top_ammo_used.push_back(std::stoi(line));
            }
            else if (std::isdigit(line[0]) && this->top_time_alive.size() < this->ranking_size) {
                this->top_time_alive.push_back(std::stoi(line));
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

    if (infected_kills > this->top_infected_kills.back()) {
        this->updateList(this->top_infected_kills, infected_kills);
        was_updated = true;
    }

    if (ammo_used > this->top_ammo_used.back()) {
        this->updateList(this->top_ammo_used, ammo_used);
        was_updated = true;
    }

    if (time_alive > this->top_time_alive.back()) {
        this->updateList(this->top_time_alive, time_alive);
        was_updated = true;
    }
}

void StatisticsHandler::saveAllStatistics() {
    if (!was_updated) return;
    std::ofstream file("../server/statistics.txt", std::ofstream::out | std::ofstream::trunc);

    if (!file.is_open()) {
        std::cout << "ERROR: Can't open statistics file" << std::endl;
        return;
    }

    file << "TOP 5: Infected kills" << std::endl;
    for (const auto& infected_kills : this->top_infected_kills) {
        file << infected_kills << std::endl;
    }
    file << std::endl;

    file << "TOP 5: Ammo used" << std::endl;
    for (const auto& ammo_used : this->top_ammo_used) {
        file << ammo_used << std::endl;
    }
    file << std::endl;

    file << "TOP 5: Time alive" << std::endl;
    for (const auto& time_alive : this->top_time_alive) {
        file << time_alive << std::endl;
    }
    file << std::endl;
    file.close();
}

std::list<uint32_t> StatisticsHandler::getTopInfectedKills() {
    std::unique_lock<std::mutex> lock(mutex);
    return this->top_infected_kills;
}

std::list<uint32_t> StatisticsHandler::getTopAmmoUsed() {
    std::unique_lock<std::mutex> lock(mutex);
    return this->top_ammo_used;
}

std::list<uint32_t> StatisticsHandler::getTopTimeAlive() {
    std::unique_lock<std::mutex> lock(mutex);
    return this->top_time_alive;
}

StatisticsHandler::~StatisticsHandler() {}