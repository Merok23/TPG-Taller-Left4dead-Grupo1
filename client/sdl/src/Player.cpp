#include "../libs/Area.h"
#include "Player.h"

#include <iostream>

Player::Player(SdlTexture &texture_idle, SdlTexture &texture_run, SdlTexture &texture_shoot, SdlTexture &texture_die): 
    an_idle(&texture_idle), 
    an_run(&texture_run),
    an_shoot(&texture_shoot),
    an_die(&texture_die),
    facingLeft(false), facingUp(false), 
    moving_x(false), moving_y(false), shooting(false), 
    x(270), y(670), health(100) {} //esta x e y son relativas a la imagen actual en el background --> si el background empieza en el pixel 300, x(50) es dentro de la pantalla, no tenes que moverte 250 pixeles

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
    if (health <= 0 && an_die.amountPlayed() == 0) {
        an_die.update(dt); //buscar como controlar el speed y como hacer que una vez muerto, quede muerto
    } else if (moving_x) {
        an_run.update(dt);
        if (facingLeft) {
            if (x >= -100)
                x -= 10; //me dice cu'antos pixeles me muevo
        }
        else {
            if (x <= 1220)
                x += 10;
        }
            
    } else if (moving_y) {
        an_run.update(dt);
        if (facingUp)
            y -= 10; //me dice cu'antos pixeles me muevo
        else
            y += 10;
    } else if (shooting) {
        an_shoot.update(dt);
    } else 
        an_idle.update(0); //buscar como controlar el speed de idle si le paso dt
}

void Player::render() {
    SDL_RendererFlip flip = facingLeft ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
    Area destArea(x, y, 200, 200); //100 100 es que tan grande es el rect'angulo para el elemento
    if (moving_x || moving_y)
        an_run.render(destArea, flip);
    else  if (shooting)
        an_shoot.render(destArea, flip);
    else if (health <= 0 && an_die.amountPlayed() == 0)
        an_die.render(destArea, flip);
    else
        an_idle.render(destArea, flip);
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
