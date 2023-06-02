#include "movement.h"
//x and y is the starting position
Movement::Movement(int x, int y, double radius) 
    : x_movement(0), 
    y_movement(0), 
    centre(x, y, radius), 
    facing_left(true) {}

int32_t Movement::getX() {
    return this->centre.getX();
}

int32_t Movement::getY() {
    return this->centre.getY();
}

void Movement::setX(int32_t x) {
    this->centre.setX(x);
}

void Movement::setY(int32_t y) {
    this->centre.setY(y);
}

double Movement::getRadius() {
    return this->centre.getRadius();
}
//x and y is the movement 
void Movement::setDirection(int x, int y) {
    this->x_movement = x;
    this->y_movement = y;
    if (x < 0) this->facing_left = true;
    else if (x > 0) this->facing_left = false;
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

void Movement::lookLeft() {
    this->facing_left = true;
}

void Movement::lookRight() {
    this->facing_left = false;
}

bool Movement::isFacingLeft() {
    return this->facing_left;
}

bool Movement::isMovingUp() {
    return (this->y_movement > 0);
}

bool Movement::isAligned(Movement &other, const uint32_t &border) {
    int64_t y = other.getY();
    int64_t my_y = this->getY();
    int64_t difference = y - my_y;
    int64_t bigger_radius = this->getRadius();
    if (other.getRadius() > bigger_radius) bigger_radius = other.getRadius();
    if (difference < 0) difference *= -1;
    if (difference <= bigger_radius) {
        return true;
    } else {
        return false;
    }
}

bool Movement::isLookingAt(Movement &other) {
    int64_t x = other.getX();
    int64_t my_x = this->getX();
    int64_t x_difference = x - my_x;
    if (x_difference < 0 && this->facing_left)  {
        return true; 
    } else if (x_difference > 0 && !this->facing_left) {
        return true; 
    } else {
        return false;
    }
}

int32_t Movement::calculateDistance(Movement &other) {
    int32_t x_difference = this->getX() - other.getX();
    int32_t y_difference = this->getY() - other.getY();
    int32_t distance = sqrt(pow(x_difference, 2) + pow(y_difference, 2));
    //its rounded down, but it doesn't matter
    return distance;
}

void Movement::setChase(Movement &other, int speed) {
    int32_t x_difference = other.getX() - this->getX();
    int32_t y_difference = other.getY() - this->getY();
    int32_t distance = sqrt(pow(x_difference, 2) + pow(y_difference, 2));
    if (distance == 0) return;
    double x_difference_double = x_difference;
    double y_difference_double = y_difference;
    double distance_double = distance;
    double normalized_x = x_difference_double / distance_double;
    double normalized_y = y_difference_double / distance_double;
    std::tuple<int32_t, int32_t> direction = getBestDirection(normalized_x, normalized_y);
    if (std::get<0>(direction) != 0) {
        if (std::abs(CONFIG.scenario_width - std::abs(x_difference)) < std::abs(x_difference)) {
            std::get<0>(direction) *= -1;
        }
    }
    this->setDirection(std::get<0>(direction) * speed, std::get<1>(direction) * speed);
}

std::tuple<int32_t, int32_t> Movement::getBestDirection(double normalized_x, double normalized_y) {
    //made with chatGPT
    std::vector<std::tuple<int32_t, int32_t>> options = {
        std::make_tuple(-1, -1),
        std::make_tuple(-1, 0),
        std::make_tuple(-1, 1),
        std::make_tuple(0, -1),
        std::make_tuple(0, 1),
        std::make_tuple(1, 0),
        std::make_tuple(1, 1),
        std::make_tuple(1, -1)
    };

    std::tuple<double, double> normalizedInput(normalized_x, normalized_y);
    double minDistance = std::numeric_limits<double>::max();
    std::tuple<int32_t, int32_t> closestVector;

    for (const auto& option : options) {
        double dist = distance(normalizedInput, option);
        if (dist < minDistance) {
            minDistance = dist;
            closestVector = option;
        }
    }
    return closestVector;
}


double Movement::distance(std::tuple<double, double> direction1, 
    std::tuple<int32_t, int32_t> direction2) {
    double x1 = std::get<0>(direction1);
    double y1 = std::get<1>(direction1);
    double x2 = std::get<0>(direction2);
    double y2 = std::get<1>(direction2);
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}
