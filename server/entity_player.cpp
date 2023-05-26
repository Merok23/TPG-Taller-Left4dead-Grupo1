#include <string> 
#include <vector>
#include <utility>

#include "entity_player.h"
// la vida debe leerse de un config.
// el radio deberia leerse de un cofig.
Player::Player(int id, uint32_t positionX, uint32_t positionY, Weapon* weapon) : 
    Entity(id, CONFIG.soldier_health, positionX, positionY), 
    my_weapon(weapon){
    this->state = IDLE_SOLDIER;
}

//prepares for movement, it'll move when the update method is called.
void Player::move(int32_t x_movement, int32_t y_movement) {
    this->state = MOVING_SOLDIER;
    Movement* myMovement = this->getDirectionOfMovement();
    if (x_movement > 0) myMovement->lookRight();//looks to the direction
    if (x_movement < 0) myMovement->lookLeft();//but it doesn't move.
    myMovement->setDirection(x_movement * CONFIG.soldier_speed,
        y_movement * CONFIG.soldier_speed);
}

void Player::update(Map& map) {
    if (this->state == MOVING_SOLDIER) {
        map.move(this->getId());
    }
    if (this->state == RELOADING_SOLDIER) {
        this->my_weapon->reload();
        this->state = IDLE_SOLDIER;
    }
    int32_t hit_points = this->getHitPoints();
    hit_points -= this->getDamageForTheRound();
    this->setHitPoints(hit_points);
    this->resetDamageForTheRound();
}

void Player::shoot(std::vector<HitEntity>& entities_hit) {
    //if no ammo reloads
    if (this->my_weapon->emptyMagazine()) {
        this->setReload();
        return;
    }
    this->state = SHOOTING_SOLDIER;
    this->removeInfectedOutOfRange(entities_hit);
    this->orderByDistance(entities_hit);  
    uint32_t hit_count = 0;
    //this is extremely inefficient, (O(N) vs O(1)) but 
    //it's made this way because at the start I thought
    //EVERYWEAPON could get through enemies, but only the
    //"scout" can.
    for (auto entity_hit : entities_hit) {
        hit_count++;
        Entity* entity = entity_hit.getEntity();
        int32_t damage = this->my_weapon->calculateDamage(entity_hit.getDistance(), hit_count);
        entity->setDamageForTheRound(damage);
    }
    this->my_weapon->useAmmo();
}

void Player::orderByDistance(std::vector<HitEntity>& entities_hit) {
    std::sort(entities_hit.begin(), entities_hit.end(),
    [](HitEntity& entity_hit1, HitEntity& entity_hit2) {
        return entity_hit1.getDistance() < entity_hit2.getDistance();
    });
}

void Player::setReload() {
    this->state = RELOADING_SOLDIER;
}

void Player::removeInfectedOutOfRange(std::vector<HitEntity> & entities_hit) {
    auto iterator = std::remove_if(entities_hit.begin(), entities_hit.end(), [this](HitEntity& entity_hit) {
        return !this->my_weapon->inRange(entity_hit.getDistance());
    });
    entities_hit.erase(iterator, entities_hit.end());
}

bool Player::isInfected() {
    return false;
}

int32_t Player::getAmmoLeft() {
    return this->my_weapon->getAmmoLeft();
}

std::string Player::getEntityType() {
    std::string type = "player";
    return type; 
}

std::string Player::getWeaponType() {
    return this->my_weapon->getWeaponType();
}

Player::~Player() {
    delete this->my_weapon;
}
