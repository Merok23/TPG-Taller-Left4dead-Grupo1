#include "health_bar.h"
#include "Player.h"
#include "SdlTexture.h"

#include <iostream>

Player::Player(std::map<AnimationName, std::shared_ptr<SdlTexture>> textures, const SdlWindow &window, uint32_t id, int32_t x_position, int32_t y_position, int32_t hit_points) :
    facingLeft(false), facingUp(false), 
    moving_x(false), moving_y(false), shooting(false),  id(id),
    x(x_position), y(y_position), health_bar(hit_points, window)
    {
        auto it = textures.find(AN_IDLE);
        if (it != textures.end())
            animations[AN_IDLE] = std::unique_ptr<Animation>(new Animation(it->second));

        it = textures.find(AN_RUN);
        if (it != textures.end())
            animations[AN_RUN] = std::unique_ptr<Animation>(new Animation(it->second));
        
        it = textures.find(AN_SHOOT);
        if (it != textures.end())
            animations[AN_SHOOT] = std::unique_ptr<Animation>(new Animation(it->second));

        it = textures.find(AN_DIE);
        if (it != textures.end())
            animations[AN_DIE] = std::unique_ptr<Animation>(new Animation(it->second));

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

/*
 * Notar que el manejo de eventos y la actualización de modelo ocurren en momentos distintos.
 * Esto les va a resultar muy util en un juego multiplaforma. 
 */
void Player::update(float dt, GameState *gs) {
    if (gs) {
        auto it = gs->entities.find(id);
        if (it != gs->entities.end()) { //mi personaje debe ser actualizado
            moving_x = (x != it->second->getPositionX());
            x = it->second->getPositionX();

            moving_y = (y != it->second->getPositionY());
            y = it->second->getPositionY();
            
            //health_bar.update(it->second->getHitPoints()); //aca recibo la nueva data del server y la funcion damage dejaria de existir
            
            facingLeft = it->second->isFacingLeft();
            facingUp = it->second->isMovingUp();
        }
    }

    auto it_die = animations.find(AN_DIE);
    if (moving_x) {
        auto it = animations.find(AN_RUN);
        if (it != animations.end())
            it->second->update(dt);
            
    } else if (moving_y) {
        auto it = animations.find(AN_RUN);
        if (it != animations.end())
            it->second->update(dt);
    } else if (shooting) {
        auto it = animations.find(AN_SHOOT);
        if (it != animations.end())
            it->second->update(dt);
    } else if (it_die != animations.end()) {
        if (health_bar.get_health() <= 0 && it_die->second->amountPlayed() == 0) {
            it_die->second->update(dt); //buscar como controlar el speed y como hacer que una vez muerto, quede muerto
        }
    } else {
        auto it = animations.find(AN_IDLE);
        if (it != animations.end())
            it->second->update(0); //buscar como controlar el speed de idle si le paso dt
    }
}

void Player::render() {
    SDL_RendererFlip flip = facingLeft ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
    Area destArea(x, y, 200, 200); //100 100 es que tan grande es el rect'angulo para el elemento
    auto it_die = animations.find(AN_DIE);
    
    if (moving_x || moving_y) {
        auto it = animations.find(AN_RUN);
        if (it != animations.end())
            it->second->render(destArea, flip);
    }
    else  if (shooting) {
        auto it = animations.find(AN_SHOOT);
        if (it != animations.end())
            it->second->render(destArea, flip);
    }
    else if (health_bar.get_health() <= 0 && it_die != animations.end() && it_die->second->amountPlayed() == 0)
            it_die->second->render(destArea, flip);
    else {
        auto it = animations.find(AN_IDLE);
        if (it != animations.end())
            it->second->render(destArea, flip);
    }

    health_bar.render();
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
