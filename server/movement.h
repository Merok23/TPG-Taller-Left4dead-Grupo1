#include "position.h"
# pragma once

#define RADIUS 5 //se debe leer del config

class Movement {
    private:
        uint32_t x_movement;
        uint32_t y_movement;
        Position centre;
    public:
        Movement(int x, int y, double radius);
        uint32_t getX();
        uint32_t getY();
        double getRadius();
        void setDirection(int x, int y);
        void move();
        bool checkForCollision(const Movement &movement);
};