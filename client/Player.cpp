#include "visual_bar.h"
#include "Player.h"
#include "SdlTexture.h"

#include <iostream>

Player::Player(std::map<AnimationName, std::shared_ptr<SdlTexture>> &textures, const SdlWindow &window, uint32_t id, int32_t x_position, int32_t y_position, int32_t hit_points, int32_t ammo, uint8_t lives) :
    GraphicsEntity(textures, id, x_position, y_position),
    health_bar(hit_points, window, 67, 2, 7, 107, 4, 14), ammo(ammo, window, 204, 119, 34, 254, 190, 0), lives(lives)
{
    Color color_key = {0xFF, 0xFF, 0xFF};
    std::shared_ptr<SdlTexture> tex_life = std::make_shared<SdlTexture>("../../assets/Mis/heart.jpg", window, color_key);
    life_an = std::unique_ptr<Animation>(new Animation(tex_life));
}

/*
 * Notar que el manejo de eventos y la actualización de modelo ocurren en momentos distintos.
 * Esto les va a resultar muy util en un juego multiplaforma. 
 */
void Player::update(float dt, Entity* entity) {
    GraphicsEntity::update(dt, entity);
    
    if (entity) {
        health_bar.update(entity->getHitPoints());
        ammo.update(entity->getAmmoLeft());
        lives = entity->getLives();
    }
}


void Player::render() {
    GraphicsEntity::render();
    health_bar.render(50, 200); //estas posiciones me las tendria que haber dicho el graphics_entity_holder
    ammo.render(50, 300); //estas posiciones me las tendria que haber dicho el graphics_entity_holder
    
    for (int i = 0; i < lives; i++) {
        Area destArea(50 + i * 35, 100, 30, 30);
        life_an->render(destArea, SDL_FLIP_NONE);
    }
}

VisualBar& Player::get_ammo() {
    return this->ammo;
}
VisualBar& Player::get_health_bar() {
    return this->health_bar;
}
