#include "player.h"
// la vida debe leerse de un config.
// el radio deberia leerse de un cofig.
Player::Player(int id, Map &map) : Entity(id, 100, map){
    this->state = IDLE;
}

//prepares for movement, it'll move when the update method is called.
void Player::move(int x, int y) {
    this->state = MOVING;
    this->getDirectionOfMovement()->setDirection(x, y);
}

void Player::update() {
    if (this->state == MOVING) {
        this->map.move(this->getId());
    }
}
