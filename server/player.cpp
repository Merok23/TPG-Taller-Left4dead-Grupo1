#include "player.h"
// la vida debe leerse de un config.
// el radio deberia leerse de un cofig.
Player::Player(int id, uint32_t positionX, uint32_t positionY) : Entity(id, 100, positionX, positionY){
    this->state = IDLE;
}

//prepares for movement, it'll move when the update method is called.
void Player::move(int x, int y) {
    this->state = MOVING;
    this->getDirectionOfMovement()->setDirection(x, y);
}

void Player::update(Map& map) {
    if (this->state == MOVING) {
        map.move(this->getId());
    }
}
