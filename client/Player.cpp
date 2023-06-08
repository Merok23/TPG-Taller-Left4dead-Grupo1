#include "visual_bar.h"
#include "Player.h"
#include "SdlTexture.h"

#include <iostream>

Player::Player(std::map<AnimationName, std::shared_ptr<SdlTexture>> &textures, const SdlWindow &window, bool is_player, uint32_t id, int32_t x_position, int32_t y_position, int32_t hit_points) :
    facingLeft(false), facingUp(false), 
    moving_x(false), moving_y(false), shooting(false), dead(false), is_player(is_player), id(id),
    x(x_position), y(y_position), health_bar(hit_points, window), ammo(200, window)
{
    for (const auto &pair : textures)
        animations[pair.first] = std::unique_ptr<Animation>(new Animation(pair.second));

    current_animation = AN_IDLE;
}

Player::~Player() {}

int32_t Player::getX() {
    return x;
}

int32_t Player::getY() {
    return y;
}


uint32_t Player::getId() {
    return id;
}


void Player::recharge() {
    ammo.max();
}

/*
 * Notar que el manejo de eventos y la actualización de modelo ocurren en momentos distintos.
 * Esto les va a resultar muy util en un juego multiplaforma. 
 */
void Player::update(float dt, std::shared_ptr<Entity> entity) {
    if (entity) {
        switch (entity->state)
        {
        case IDLE:
            current_animation = AN_IDLE;
            break;
        
        case RUN:
            current_animation = AN_RUN;
            break;
        
        case SHOOT:
            current_animation = AN_SHOOT;
            break;
        
        case DIE:
            current_animation = AN_DIE;
            break;
        
        case RELOAD: 
            current_animation = AN_RELOAD;
            break;
        
        case ATTACKING:
            current_animation = AN_ATTACK1;
            break;
        
        }
        x = entity->getPositionX();
        y = entity->getPositionY();

        if (is_player) {
            health_bar.update(entity->getHitPoints());
            ammo.update(entity->getAmmoLeft());
        }
        
        facingLeft = entity->isFacingLeft();
        facingUp = entity->isMovingUp();
    }

    auto it_current = animations.find(current_animation);
    if (it_current != animations.end()) {
        if (current_animation == AN_DIE)
            if (it_current->second->amountPlayed() == 0)
                it_current->second->update(dt, 3);
            else
                it_current->second->update(0, 0);
        
        else if (current_animation == AN_IDLE)
            it_current->second->update(dt, 5);
        else
            it_current->second->update(dt, 1);
    }
}

bool Player::is_dead() {
    return dead;
}

void Player::render() {
    SDL_RendererFlip flip = facingLeft ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
    Area destArea(x, y, 200, 200); //200 200 es que tan grande es el rect'angulo para el elemento
    
    auto it_current = animations.find(current_animation);
    if (it_current != animations.end())
            it_current->second->render(destArea, flip);
    
    if (is_player) {
        ammo.render(50, 300);
        health_bar.render(50, 200);
    }
}

void Player::update_x(int32_t x) {
    this->x = x;
}

VisualBar& Player::get_ammo() {
    return this->ammo;
}
VisualBar& Player::get_health_bar() {
    return this->health_bar;
}

void Player::hurt() {
    health_bar.damage(20); //esto es para probar, mas adelante lo tengo que recibir del server
}

void Player::moveRigth() {
    moving_x = true;
    facingLeft = false;
    shooting = false;
}

void Player::moveLeft() {
    moving_x = true;
    facingLeft = true;
    shooting = false;
}

void Player::moveUp() {
    moving_y = true;
    facingUp = true;
    shooting = false;
}

void Player::moveDown() {
    moving_y = true;
    facingUp = false;
    shooting = false;
}

void Player::shoot() {
    moving_x = false;
    moving_y = false;
    shooting = true;
    ammo.damage(5);
}

void Player::stopMovingX() {
    moving_x = false;
}

void Player::stopMovingY() {
    moving_y = false;
}

void Player::stopShooting() {
    shooting = false;
}
