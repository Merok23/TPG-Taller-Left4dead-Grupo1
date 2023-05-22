#include <map>
#include <cstdint>
#include <mutex>
#include "game.h"
#pragma once

class IdHandler {
    private:
        Game &game;
        std::map<uint32_t, uint32_t> my_ids;
        std::mutex m;
    public:
        explicit IdHandler(Game &game);
        void createPlayer(uint32_t client_id);
        void setMoving(uint32_t client_id, int32_t x, int32_t y);
        //SHOOTING IS NOT FULLY IMPLEMENTED YET
        void shoot(uint32_t client_id);
};