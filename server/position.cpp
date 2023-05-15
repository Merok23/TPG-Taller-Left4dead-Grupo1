#include "position.h"

using namespace std;

Position::Position(int x, int y, double radius) : x(x), y(y), radius(radius){}

int Position::getX() {
    return this->x;
}

int Position::getY() {
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
    int x = this->x - other_position.getX();
    int y = this->y - other_position.getY();
    double distance = sqrt(pow(x, 2) + pow(y, 2));
    return distance <= this->radius + other_position.radius;
}

