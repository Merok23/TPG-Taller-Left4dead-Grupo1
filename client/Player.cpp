#include "visual_bar.h"
#include "Player.h"
#include "SdlTexture.h"

#include <iostream>

Player::Player(std::map<AnimationName, std::shared_ptr<SdlTexture>> &textures, const SdlWindow &window, uint32_t id, int32_t x_position, int32_t y_position, int32_t hit_points, int32_t ammo) :
    GraphicsEntity(textures, id, x_position, y_position),
    health_bar(hit_points, window, 67, 2, 7, 107, 4, 14), ammo(ammo, window, 204, 119, 34, 254, 190, 0)
{}

/*
 * Notar que el manejo de eventos y la actualización de modelo ocurren en momentos distintos.
 * Esto les va a resultar muy util en un juego multiplaforma. 
 */
void Player::update(float dt, Entity* entity) {
    GraphicsEntity::update(dt, entity);
    
    if (entity) {
        health_bar.update(entity->getHitPoints());
        ammo.update(entity->getAmmoLeft());
    }
}


void Player::render() {
    GraphicsEntity::render();
    ammo.render(50, 300); //estas posiciones me las tendria que haber dicho el graphics_entity_holder
    health_bar.render(50, 200); //estas posiciones me las tendria que haber dicho el graphics_entity_holder
}

VisualBar& Player::get_ammo() {
    return this->ammo;
}
VisualBar& Player::get_health_bar() {
    return this->health_bar;
}
