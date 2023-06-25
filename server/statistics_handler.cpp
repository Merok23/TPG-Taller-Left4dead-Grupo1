#include "statistics_handler.h"

StatisticsHandler statistics_handler;

StatisticsHandler::StatisticsHandler() : infected_kills_top_10(10), ammo_used_top_10(10), time_alive_top_10(10), ranking_size(10), was_updated(false),mutex() {
    std::cout << "Entre a statistics handler" << std::endl;
    std::ifstream file("../statistics.txt", std::ios::in);
    std::cout << "Entre a statistics handler 2" << std::endl;
    std::string line;
    if (file.is_open()) {
        std::cout << "Entre a statistics handler 3" << std::endl;
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

    for (int i = 0; i < this->ranking_size; i++) {
        std::cout << this->infected_kills_top_10[i] << std::endl;
        std::cout << this->ammo_used_top_10[i] << std::endl;
        std::cout << this->time_alive_top_10[i] << std::endl;
    }
    file.close();
}



void StatisticsHandler::updateList(std::vector<uint32_t>& vector, uint32_t& value) {
    if (!vector.empty()) vector.pop_back();
    auto it = std::find_if(vector.rbegin(), vector.rend(), [value](int elemento) {
        return elemento < (int)value;
    });

    vector.insert(it.base(), value);
}

void StatisticsHandler::updateStatistics(uint32_t& infected_kills, uint32_t& ammo_used, uint32_t& time_alive) {
    std::unique_lock<std::mutex> lock(mutex);

    if (infected_kills > this->infected_kills_top_10.back()) {
        std::cout << "Entre a update statistics" << std::endl;
        std::cout << "infected kills: " << infected_kills << std::endl;
        std::cout << "infected kills back: " << this->infected_kills_top_10.back() << std::endl;
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
    std::ofstream file("../statistics.txt", std::ofstream::out);

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

std::vector<uint32_t> StatisticsHandler::getInfectedKillsTop10() {
    std::unique_lock<std::mutex> lock(mutex);
    return this->infected_kills_top_10;
}

std::vector<uint32_t> StatisticsHandler::getAmmoUsedTop10() {
    std::unique_lock<std::mutex> lock(mutex);
    return this->ammo_used_top_10;
}

std::vector<uint32_t> StatisticsHandler::getTimeAliveTop10() {
    std::unique_lock<std::mutex> lock(mutex);
    return this->time_alive_top_10;
}

StatisticsHandler::~StatisticsHandler() {}