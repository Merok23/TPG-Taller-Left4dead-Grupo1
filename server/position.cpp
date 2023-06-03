#include <utility>

#include "position.h"

Position::Position(int x, int y, double radius) : x(x), y(y), radius(radius){}

int32_t Position::getX() {
    return this->x;
}

int32_t Position::getY() {
    return this->y;
}

double Position::getRadius() {
    return this->radius;
}

void Position::setX(int32_t x) {
    this->x = x;
}

void Position::setY(int32_t y) {
    this->y = y;
}

void Position::move(int x, int y) {
    this->x += x;
    this->y += y;
}

bool Position::checkForCollision(const Position& other_position) {
    //create copies, one because of const, two because we need them to be signed.
    int32_t x = std::abs(this->x - other_position.x);
    int32_t y = this->y - other_position.y;
    if (x > CONFIG.scenario_width / 2) x = CONFIG.scenario_width - x;
    long double distance = sqrt(pow(x, 2) + pow(y, 2));
    return distance < this->radius + other_position.radius;
}
