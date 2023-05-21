#include <cstdint>
#include <functional>
#include "map.h"
#include "movement.h"
#include "hit_entity.h"
#include "config.h"
#include <vector>

#pragma once

class Entity {
    private:
        uint32_t id;
        int32_t hit_points;
        Movement direction_of_movement;
        int32_t damage_for_the_round;
        
    public:
        Entity(uint32_t id, int32_t hit_points, uint32_t x, uint32_t y);
        uint32_t getId();
        int32_t getHitPoints();
        int32_t getDamageForTheRound();
        void setHitPoints(int32_t hit_points);
        void setDamageForTheRound(int32_t damage);
        Movement* getDirectionOfMovement();
        virtual std::string getEntityType(); 
        //seguramente no sea necesario que sea virtual e = 0
        //pero lo dejo por ahora para aprender un poco de herencia.
        virtual void move(int32_t x_movement, int32_t y_movement) = 0; 
        virtual void update(Map& map) = 0;
        virtual void shoot(std::vector<HitEntity>& entities_hit) = 0;
        virtual bool isInfected() = 0;
        virtual ~Entity() = 0;
        
};
