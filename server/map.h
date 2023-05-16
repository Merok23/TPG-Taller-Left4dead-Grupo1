#include <cstdint>
#include <map>
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
        bool move(uint32_t id);
        void addEntity(uint32_t id, Movement *entity);
        void removeEntity(uint32_t id);
        ~Map();
    private:
        bool checkForBorderCollision(Movement &entity);
};
