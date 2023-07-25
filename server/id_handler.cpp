#include "id_handler.h"

IdHandler::IdHandler(Game &game) : game(game), my_ids(), mutex() {}

void IdHandler::createPlayer(uint32_t client_id, Weapon* weapon, std::string name) {
    std::unique_lock<std::mutex> lock(mutex);
    //game returns the game id:
    my_ids[client_id] = game.addPlayer(weapon, name);
}

void IdHandler::setMoving(uint32_t client_id, int32_t x, int32_t y) {
    std::unique_lock<std::mutex> lock(mutex);
    uint32_t id = my_ids[client_id];
    game.setMoving(id, x, y);
}

void IdHandler::shoot(uint32_t client_id, bool isShooting) {
    uint32_t id = my_ids[client_id];
    if (isShooting) game.setShooting(id);
    else game.stopShooting(id);
}

void IdHandler::reload(uint32_t client_id, bool isReloading) {
    uint32_t id = my_ids[client_id];
    game.setReloading(id);
}

void IdHandler::setCheat(uint32_t client_id, Cheat cheatType) {
    uint32_t id = my_ids[client_id];
    game.setCheat(id, cheatType);
}

uint32_t IdHandler::getAmmountOfAmmoUsed(uint32_t client_id) {
    uint32_t id = my_ids[client_id];
    return game.getAmountOfAmmoUsedBySoldier(id);
}

uint32_t IdHandler::getAmmountOfInfectedKilled(uint32_t client_id) {
    uint32_t id = my_ids[client_id];
    return game.getAmountOfInfectedKilledBySoldier(id);
}

uint32_t IdHandler::getTimeOfDeath(uint32_t client_id) {
    uint32_t id = my_ids[client_id];
    return game.getTimeOfDeathOfSoldier(id);
}