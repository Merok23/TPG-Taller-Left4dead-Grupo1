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

bool Position::checkForCollision(const Position& other_position) {
    //create copies, one because of const, two because we need them to be signed.
    int64_t x_signed = this->x;
    int64_t y_signed = this->y;
    int64_t other_x_signed = other_position.x;
    int64_t other_y_signed = other_position.y;
    int64_t x = x_signed - other_x_signed;
    int64_t y = y_signed - other_y_signed;
    long double distance = sqrt(pow(x, 2) + pow(y, 2));
    return distance < this->radius + other_position.radius;
}
