#include "movement.h"
//x and y is the starting position
Movement::Movement(int x, int y, double radius) 
    : x_movement(0), y_movement(0), centre(x, y, radius) {}

int Movement::getX() {
    return this->centre.getX();
}

int Movement::getY() {
    return this->centre.getY();
}

double Movement::getRadius() {
    return this->centre.getRadius();
}
//x and y is the movement 
void Movement::move(int x, int y) {
    this->x_movement = x;
    this->y_movement = y;
    this->centre.move(x, y);
}
//Checks if the movement collides with another movement after moving
//The idea being that you call this before doing the movement.
bool Movement::collision(Movement movement) {
    Position aux = Position(this->centre.getX(), this->centre.getY(), this->centre.getRadius());
    aux.move(this->x_movement, this->y_movement);
    return aux.checkForCollision(movement.centre);
}
