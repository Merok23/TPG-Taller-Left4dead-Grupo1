#include "position.h"
# pragma once

#define RADIUS 5 //se debe leer del config

class Movement {
    private:
        int8_t x_movement;
        int8_t y_movement;
        Position centre;
    public:
        Movement(int x, int y, double radius);
        int32_t getX();
        int32_t getY();
        double getRadius();
        void setX(int32_t x);
        void setY(int32_t y);
        void setDirection(int x, int y);
        void move();
        bool checkForCollision(const Movement &other);
        bool isAligned(Movement &other, const uint32_t &border);
        bool isLookingAt(Movement &other); //doesn't take into account looping map :l
        int32_t calculateDistance(Movement &other);
        
};