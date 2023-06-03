#ifndef SERVER_POSITION_H
#define SERVER_POSITION_H

#include <math.h>
#include <cstdint>
#include <utility>
# pragma once

//This is here so it can check for the torus effect
//when colliding, it would be best if it was not here
#include "config.h"


class Position {
    private:
        int32_t x;
        int32_t y;
        double radius;
    public:
        Position(int x, int y, double radius);
        int32_t getX();
        int32_t getY();
        void setX(int32_t x);
        void setY(int32_t y);
        double getRadius();
        void move(int x, int y);
        bool checkForCollision(const Position &other_position);
};
#endif

