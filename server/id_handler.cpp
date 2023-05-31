#include "id_handler.h"

IdHandler::IdHandler(Game &game) : game(game), my_ids(), m() {}

void IdHandler::createPlayer(uint32_t client_id, Weapon* weapon) {
    std::unique_lock<std::mutex> lock(m);
    my_ids[client_id] = game.getCurrentId();
    Entity* entity = new Player(game.getCurrentId(), 910, 300, weapon); //posiciones?
    game.addEntity(entity);
}

void IdHandler::setMoving(uint32_t client_id, int32_t x, int32_t y) {
    uint32_t id = my_ids[client_id];
    game.setMoving(id, x, y);
}

void IdHandler::shoot(uint32_t client_id) {
    uint32_t id = my_ids[client_id];
    game.setShooting(id);
}
