#ifndef CLIENT_ENTITY_H
#define CLIENT_ENTITY_H
#include <cstdint>
#include <functional>

#pragma once

class Entity {
    private:
        uint32_t id;
        std::string type;
        int32_t hit_points;
        int32_t x_position;
        int32_t y_position;
        bool is_facing_left;
        bool is_moving_up;
        
    public:
        Entity(uint32_t id, const std::string& type, int32_t hit_points, uint32_t x, uint32_t y, bool facing_left, bool moving_up);
        uint32_t getId();
        int32_t getHitPoints();
        std::string getType(); 
        int32_t getPositionX();
        int32_t getPositionY();
        bool isFacingLeft();
        bool isMovingUp();
};
#endif