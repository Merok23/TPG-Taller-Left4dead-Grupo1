#include "position.h"

using namespace std;

Position::Position(int x, int y, double radius) : x(x), y(y), radius(radius){}

uint32_t Position::getX() {
    return this->x;
}

uint32_t Position::getY() {
    return this->y;
}

double Position::getRadius() {
    return this->radius;
}

void Position::move(int x, int y) {
    this->x += x;
    this->y += y;
}

bool Position::checkForCollision(Position other_position) {
    uint32_t x = this->x - other_position.getX();
    uint32_t y = this->y - other_position.getY();
    double distance = sqrt(pow(x, 2) + pow(y, 2));
    return distance <= this->radius + other_position.radius;
}

