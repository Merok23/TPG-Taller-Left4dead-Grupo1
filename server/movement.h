#ifndef SERVER_MOVEMENT_H
#define SERVER_MOVEMENT_H

#include "position.h"
#include <cmath>
#include <vector>
#include <tuple>
#include <limits>
#include "config.h"
# pragma once

/**
 * @class Movement
 * @brief Has all the movement logic
 */
class Movement {
    private:
        int8_t x_movement;
        int8_t y_movement;
        Position centre;
        bool facing_left;
        
    public:
        Movement(int x, int y, double radius);
        int32_t getX();
        int32_t getY();
        double getRadius();
        void setX(int32_t x);
        void setY(int32_t y);
        void setDirection(int x, int y);
        void lookRight();
        void lookLeft();
        void move();
        bool checkForCollision(const Movement &other);
        bool movementExceedsDistanceFromX(const int32_t &positionX,const double &distance);
        bool isFacingLeft();
        bool isMovingUp(); 
        bool isAligned(Movement &other, const uint32_t &border);
        bool isLookingAt(Movement &other); //doesn't take into account looping map :l
        int32_t calculateDistance(Movement &other);
        void setChase(Movement &other, int speed);

    private:
        std::tuple<int32_t, int32_t> getBestDirection(double normalized_x,
            double normalized_y);
        double distance(std::tuple<double, double> direction1,
            std::tuple<int32_t, int32_t> direction2);
};
#endif
