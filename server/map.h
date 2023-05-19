#include <cstdint>
#include <map>
#include <vector>
#include "movement.h"
# pragma once

class Map {
    private:
        uint32_t width;
        uint32_t height;
        std::map<uint32_t, Movement*> entities;
    public:
        Map(uint32_t width, uint32_t height);
        uint32_t getWidth();
        uint32_t getHeight();
        std::map<uint32_t, Movement*> getEntities();
        bool move(const uint32_t &id);
        std::vector<uint32_t[2]>& shoot(uint32_t id);
        void addEntity(const uint32_t &id, Movement *entity);
        void removeEntity(const uint32_t &id);
        ~Map();
    private:
        //intentionally recieves a copy
        bool checkForBorderCollision(Movement entity);
};
