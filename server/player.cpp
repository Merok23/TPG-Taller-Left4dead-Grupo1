#include "player.h"
// la vida debe leerse de un config.
// el radio deberia leerse de un cofig.
Player::Player(int id) : Entity(id, 100){
    this->state = IDLE;
}

//prepares for movement, it'll move when the update method is called.
void Player::move(int x, int y) {
    this->state = MOVING;
    Entity::move(x,y);
}

void Player::update() {
    
}
