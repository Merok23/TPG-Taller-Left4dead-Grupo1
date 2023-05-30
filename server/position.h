#ifndef SERVER_POSITION_H
#define SERVER_POSITION_H

#include <math.h>
#include <cstdint>
#include <utility>
# pragma once


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

