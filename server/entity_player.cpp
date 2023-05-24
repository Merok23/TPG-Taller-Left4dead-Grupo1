#include <string> 
#include <vector>
#include <utility>

#include "entity_player.h"
// la vida debe leerse de un config.
// el radio deberia leerse de un cofig.
Player::Player(int id, uint32_t positionX, uint32_t positionY) : 
    Entity(id, CONFIG.soldier_health, positionX, positionY){
    this->state = IDLE_SOLDIER;
}

//prepares for movement, it'll move when the update method is called.
void Player::move(int32_t x_movement, int32_t y_movement) {
    this->state = MOVING_SOLDIER;
    this->getDirectionOfMovement()->setDirection(x_movement * CONFIG.soldier_speed,
        y_movement * CONFIG.soldier_speed);
}

void Player::update(Map& map) {
    if (this->state == MOVING_SOLDIER) {
        map.move(this->getId());
    }
}

void Player::shoot(std::vector<HitEntity>& entities_hit) {
    for (auto entity_hit : entities_hit) {
        Entity* entity = entity_hit.getEntity();
        entity->setDamageForTheRound(50);
    }
}

bool Player::isInfected() {
    return false;
}

std::string Player::getEntityType() {
    std::string type = "player"; 
    return type; 
}

Player::~Player() {}
