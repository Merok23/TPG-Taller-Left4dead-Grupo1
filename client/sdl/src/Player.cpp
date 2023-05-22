#include "Area.h"
#include "Player.h"

Player::Player(SdlTexture &texture_idle, SdlTexture &texture_run, SdlTexture &texture_shoot): 
    an_idle(&texture_idle), 
    an_run(&texture_run),
    an_shoot(&texture_shoot),
    facingLeft(false), facingUp(false), 
    moving_x(false), moving_y(false), shooting(false), 
    x(100), y(870) {}

Player::~Player() {}

/*
 * Notar que el manejo de eventos y la actualización de modelo ocurren en momentos distintos.
 * Esto les va a resultar muy util en un juego multiplaforma. 
 */
void Player::update(float dt) {
    if (moving_x) {
        an_run.update(dt);
        if (facingLeft)
            x -= 10; //me dice cu'antos pixeles me muevo
        else
            x += 10;
    } else if (moving_y) {
        an_run.update(dt);
        if (facingUp)
            y -= 10; //me dice cu'antos pixeles me muevo
        else
            y += 10;
    } else if (shooting) {
        an_shoot.update(dt);
    } else 
        an_idle.update(0);
}

void Player::render() {
    SDL_RendererFlip flip = facingLeft ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
    Area destArea(x, y, 100, 100); //100 100 es que tan grande es el rect'angulo para el elemento
    if (moving_x || moving_y)
        an_run.render(destArea, flip);
    else  if (shooting)
        an_shoot.render(destArea, flip);
    else
        an_idle.render(destArea, flip);
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
