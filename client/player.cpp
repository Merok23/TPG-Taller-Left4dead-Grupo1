#include "player.h"

Player::Player(int id, int x, int y, int health) : Entity(id, health), id(id), x_position(x), y_position(y){
    this->x_position = x; 
    this->y_position = y; 
}   

int Player::get_X_position() {
    return this->x_position; 
}

int Player::get_Y_position() {
    return this->y_position;
}
