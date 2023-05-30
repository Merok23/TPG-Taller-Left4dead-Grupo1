#include "Area.h"
#include "Player.h"
#include "SdlTexture.h"

#include <iostream>

Player::Player(std::map<AnimationName, std::shared_ptr<SdlTexture>> textures): 
    facingLeft(false), facingUp(false), 
    moving_x(false), moving_y(false), shooting(false), 
    x(270), y(670), health(100)
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

    } //esta x e y son relativas a la imagen actual en el background --> si el background empieza en el pixel 300, x(50) es dentro de la pantalla, no tenes que moverte 250 pixeles

Player::~Player() {}

int Player::getX() {
    return x;
}

int Player::getY() {
    return y;
}

/*
 * Notar que el manejo de eventos y la actualización de modelo ocurren en momentos distintos.
 * Esto les va a resultar muy util en un juego multiplaforma. 
 */
void Player::update(float dt) {
    auto it_die = animations.find(AN_DIE);
    if (moving_x) {
        auto it = animations.find(AN_RUN);
        if (it != animations.end())
            it->second->update(dt);
        if (facingLeft) {
            if (x >= -100)
                x -= 10; //me dice cu'antos pixeles me muevo
        }
        else {
            if (x <= 1220)
                x += 10;
        }
            
    } else if (moving_y) {
        auto it = animations.find(AN_RUN);
        if (it != animations.end())
            it->second->update(dt);
        if (facingUp)
            y -= 10; //me dice cu'antos pixeles me muevo
        else
            y += 10;
    } else if (shooting) {
        auto it = animations.find(AN_SHOOT);
        if (it != animations.end())
            it->second->update(dt);
    } else if (it_die != animations.end()) {
        if (health <= 0 && it_die->second->amountPlayed() == 0) {
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
    else if (health <= 0 && it_die != animations.end() && it_die->second->amountPlayed() == 0)
            it_die->second->render(destArea, flip);
    else {
        auto it = animations.find(AN_IDLE);
        if (it != animations.end())
            it->second->render(destArea, flip);
    }
}

void Player::hurt() {
    health = health-50;
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
