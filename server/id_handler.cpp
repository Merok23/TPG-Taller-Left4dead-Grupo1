#include "id_handler.h"

IdHandler::IdHandler(Game &game) : game(game), my_ids(), m() {}

void IdHandler::createPlayer(uint32_t client_id, Weapon* weapon) {
    std::unique_lock<std::mutex> lock(m);
    //game returns the game id:
    my_ids[client_id] = game.addPlayer(weapon);
    //std::tuple<int, int> pos = game.getPlayerSpawnPoint();
    //Entity* entity = new Player(game.getCurrentId(), std::get<0>(pos), std::get<1>(pos), weapon);
    //Entity* entity = new Player(game.getCurrentId(), 1920, 100, weapon); //posiciones? //era 300
    //game.addEntity(entity);
}

void IdHandler::setMoving(uint32_t client_id, int32_t x, int32_t y) {
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
