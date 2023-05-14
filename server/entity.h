#include <cstdint>
#pragma once

class Entity {
    private:
        uint32_t id;
        int32_t hit_points;
    public:
        Entity(uint32_t id, int32_t hitP_points);
        uint32_t getId();
        int32_t getHitPoints();
        void setHitPoints(int32_t hit_points);
        //seguramente no sea necesario que sea virtual e = 0
        //pero lo dejo por ahora para aprender un poco de herencia.
        virtual void move(int32_t x_movement, int32_t y_movement) = 0; 
        ~Entity();
};
