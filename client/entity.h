#ifndef CLIENT_ENTITY_H
#define CLIENT_ENTITY_H
#include <cstdint>
#include <functional>

#pragma once

class Entity {
    private:
        uint32_t id;
        int32_t hit_points;
        
    public:
        Entity(uint32_t id, int32_t hit_points);
        uint32_t getId();
        int32_t getHitPoints();
        virtual std::string getEntityType(); 
};
#endif