#include "player.h"
// la vida debe leerse de un config.
// el radio deberia leerse de un cofig.
Player::Player(int id) : Entity(id, 100), direction_of_movement(0, 0, RADIUS){
    this->state = IDLE;
}

void Player::move(int x, int y) {
    this->state = MOVING;
    this->direction_of_movement.move(x, y);
}

Movement Player::getDirectionOfMovement() {
    return this->direction_of_movement;
}
