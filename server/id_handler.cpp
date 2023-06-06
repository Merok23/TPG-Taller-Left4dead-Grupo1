#include "id_handler.h"

IdHandler::IdHandler(Game &game) : game(game), my_ids(), m() {}

void IdHandler::createPlayer(uint32_t client_id, Weapon* weapon) {
    std::unique_lock<std::mutex> lock(m);
    my_ids[client_id] = game.getCurrentId();
    Entity* entity = new Player(game.getCurrentId(), (1080)/2, 600, weapon); //posiciones? //era 300
    game.addEntity(entity);
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