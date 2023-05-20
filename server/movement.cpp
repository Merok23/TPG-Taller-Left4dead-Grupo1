#include "movement.h"
//x and y is the starting position
Movement::Movement(int x, int y, double radius) 
    : x_movement(0), y_movement(0), centre(x, y, radius) {}

int32_t Movement::getX() {
    return this->centre.getX();
}

int32_t Movement::getY() {
    return this->centre.getY();
}

void Movement::setX(int32_t x) {
    this->centre.setX(x);
}

double Movement::getRadius() {
    return this->centre.getRadius();
}
//x and y is the movement 
void Movement::setDirection(int x, int y) {
    this->x_movement = x;
    this->y_movement = y;
}

void Movement::move() {
    this->centre.move(this->x_movement, this->y_movement);
}
//Checks if the movement collides with another movement after moving
//The idea being that you call this before doing the movement.
bool Movement::checkForCollision(const Movement &other) {
    Position aux = Position(this->centre.getX(), this->centre.getY(), this->centre.getRadius());
    aux.move(this->x_movement, this->y_movement);
    return aux.checkForCollision(other.centre);
}

bool Movement::isAligned(Movement &other, const uint32_t &border) {
    int64_t y = other.getY();
    int64_t my_y = this->getY();
    int64_t difference = y - my_y;
    int64_t bigger_radius = this->getRadius();
    if (other.getRadius() > bigger_radius) bigger_radius = other.getRadius();
    if (difference < 0) difference *= -1;
    if (difference <= bigger_radius) return true;
    else return false;
}

bool Movement::isLookingAt(Movement &other) {
    int64_t x = other.getX();
    int64_t my_x = this->getX();
    int64_t x_difference = x - my_x;
    if (x_difference < 0 && this->x_movement < 0) return true;
    else if (x_difference > 0 && this->x_movement > 0) return true;
    else return false;
}

int32_t Movement::calculateDistance(Movement &other) {
    int32_t x_difference = this->getX() - other.getX();
    int32_t y_difference = this->getY() - other.getY();
    int32_t distance = sqrt(pow(x_difference, 2) + pow(y_difference, 2));
    //its rounded down, but it doesn't matter
    return distance;
}
