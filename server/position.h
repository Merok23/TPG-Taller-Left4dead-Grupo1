#include <math.h>
#include <cstdint>
# pragma once


class Position {
    private:
        uint32_t x;
        uint32_t y;
        double radius;
    public:
        Position(int x, int y, double radius);
        uint32_t getX();
        uint32_t getY();
        double getRadius();
        void move(int x, int y);
        bool checkForCollision(const Position &other_position);
};
