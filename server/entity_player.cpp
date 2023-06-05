#include <string> 
#include <vector>
#include <utility>
#include <algorithm>
#include <chrono>
#include <unordered_map>

#include "entity_player.h"
// la vida debe leerse de un config.
// el radio deberia leerse de un cofig.
Player::Player(int id, uint32_t positionX, uint32_t positionY, Weapon* weapon) : 
    Entity(id, CONFIG.soldier_health, positionX, positionY), 
    my_weapon(weapon){
    this->state = IDLE_SOLDIER;
    this->lives = 4;
    this->revival_countdown = 0;
    this->time_until_dead = 0;
}

//prepares for movement, it'll move when the update method is called.
void Player::move(int32_t x_movement, int32_t y_movement) {
    if (this->state == DEAD_SOLDIER) return;
    this->state = MOVING_SOLDIER;
    Movement* myMovement = this->getDirectionOfMovement();
    if (x_movement > 0) myMovement->lookRight();//looks to the direction
    if (x_movement < 0) myMovement->lookLeft();//but it doesn't move.
    myMovement->setDirection(x_movement * CONFIG.soldier_speed,
        y_movement * CONFIG.soldier_speed);
}

void Player::update(Map& map) {
    if (this->state == DEAD_SOLDIER) return;
    if (this->state == MOVING_SOLDIER) {
        map.move(this->getId());
    }
    if (this->state == RELOADING_SOLDIER) {
        this->my_weapon->reload();
        this->state = IDLE_SOLDIER;
    }
    if (this->state == REVIVING_SOLDIER) {
        if (revival_countdown == CONFIG.soldier_time_to_revive - 1 && this->lives > 0) {
            this->state = IDLE_SOLDIER;
            this->setHitPoints(CONFIG.soldier_health / 2); 
            this->revival_countdown = 0;
        } else {
            revival_countdown++;
        }
    }
    if (this->state == DOWN_SOLDIER) {
        if (time_until_dead == CONFIG.soldier_max_time_until_dead) {
            this->state = DEAD_SOLDIER;
            this->time_until_dead = 0;
            this->lives = 0;
            return;
        } else {
            time_until_dead++;
        }
    }
    this->resolveDamage();
    if (this->getHitPoints() <= 0 && !this->isDown() && !this->isReviving()) {
        this->state = DOWN_SOLDIER;
        this->lives--;
    }
    if (this->lives <= 0) {
        this->state = DEAD_SOLDIER;
    }
}

void Player::resolveDamage() {
    int32_t hit_points = this->getHitPoints();
    hit_points -= this->getDamageForTheRound();
    this->setHitPoints(hit_points);
    this->resetDamageForTheRound();
}

bool Player::isDead() {
    return (this->state == DEAD_SOLDIER);
}

bool Player::isDown() {
    return (this->state == DOWN_SOLDIER);
}

bool Player::isReviving() {
    return (this->state == REVIVING_SOLDIER);
}

uint8_t Player::getLives() {
    return this->lives;
}

void Player::shoot(std::vector<HitEntity>& entities_hit) {
    if (this->state == DEAD_SOLDIER) return;
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

void Player::setReviving() {
    this->state = REVIVING_SOLDIER;
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
    auto iterator = std::remove_if
    (entities_hit.begin(), entities_hit.end(), [this](HitEntity& entity_hit) {
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
    return "player"; 
}

std::string Player::getWeaponType() {
    return this->my_weapon->getWeaponType();
}

std::string Player::getState() {
     std::unordered_map<int, std::string> stateMap = { //creo que puede ser un atributo? 
        {IDLE_SOLDIER, "idle"},
        {MOVING_SOLDIER, "moving"},
        {SHOOTING_SOLDIER, "shooting"},
        {RELOADING_SOLDIER, "reloading"},
        {DOWN_SOLDIER, "down"},
        {REVIVING_SOLDIER, "reviving"},
        {DEAD_SOLDIER, "dead"}
    };
    return stateMap[this->state];
}

Player::~Player() {
    delete this->my_weapon;
}

