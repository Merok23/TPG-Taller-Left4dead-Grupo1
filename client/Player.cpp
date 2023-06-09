#include "visual_bar.h"
#include "Player.h"
#include "SdlTexture.h"

#include <iostream>

Player::Player(std::map<AnimationName, std::shared_ptr<SdlTexture>> &textures, const SdlWindow &window, uint32_t id, int32_t x_position, int32_t y_position, int32_t hit_points, int32_t ammo) :
    GraphicsEntity(textures, id, x_position, y_position),
    health_bar(hit_points, window, 67, 2, 7, 107, 4, 14), ammo(ammo, window, 204, 119, 34, 254, 190, 0)
{
    for (const auto &pair : textures)
        animations[pair.first] = std::unique_ptr<Animation>(new Animation(pair.second));

    current_animation = AN_IDLE;
}

/*
 * Notar que el manejo de eventos y la actualización de modelo ocurren en momentos distintos.
 * Esto les va a resultar muy util en un juego multiplaforma. 
 */
void Player::update(float dt, Entity* entity) {
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
        
        case DOWN:
            current_animation = AN_HURT;
            break;
        
        case REVIVING:
            current_animation = AN_IDLE;
            break;
        } 
        x = entity->getPositionX();
        y = entity->getPositionY();

        health_bar.update(entity->getHitPoints());
        ammo.update(entity->getAmmoLeft());
        
        facingLeft = entity->isFacingLeft();
    }

    auto it_current = animations.find(current_animation);
    if (it_current != animations.end()) {
        if (current_animation == AN_DIE) {
            if (it_current->second->amountPlayed() == 0)
                it_current->second->update(dt, 3);
            else
                it_current->second->update(0, 0);
        }
        
        else if (current_animation == AN_IDLE)
            it_current->second->update(dt, 5);
        else
            it_current->second->update(dt, 1);
    }
}


void Player::render() {
    SDL_RendererFlip flip = facingLeft ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
    Area destArea(x, y, 200, 200); //200 200 es que tan grande es el rect'angulo para el elemento
    
    auto it_current = animations.find(current_animation);
    if (it_current != animations.end())
            it_current->second->render(destArea, flip);
    
    ammo.render(50, 300);
    health_bar.render(50, 200);
}


VisualBar& Player::get_ammo() {
    return this->ammo;
}
VisualBar& Player::get_health_bar() {
    return this->health_bar;
}
