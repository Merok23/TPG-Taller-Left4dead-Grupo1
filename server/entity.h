#include <cstdint>
#include <functional>
#include "map.h"
#include "movement.h"

#pragma once

class Entity {
    private:
        uint32_t id;
        int32_t hit_points;
        Movement direction_of_movement;
        
    public:
        Entity(uint32_t id, int32_t hit_points);
        uint32_t getId();
        int32_t getHitPoints();
        void setHitPoints(int32_t hit_points);
        Movement* getDirectionOfMovement();
        //seguramente no sea necesario que sea virtual e = 0
        //pero lo dejo por ahora para aprender un poco de herencia.
        virtual void move(int32_t x_movement, int32_t y_movement) = 0; 
        virtual void update(Map& map) = 0;
};
