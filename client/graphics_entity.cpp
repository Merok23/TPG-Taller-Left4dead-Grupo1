#include "graphics_entity.h"

GraphicsEntity::GraphicsEntity(std::map<AnimationName, std::shared_ptr<SdlTexture>> &textures, 
                                uint32_t id, int32_t x_position, int32_t y_position) :
    facingLeft(false), dead(false), id(id),
    x(x_position), y(y_position)
{
    for (const auto &pair : textures)
        animations[pair.first] = std::unique_ptr<Animation>(new Animation(pair.second));

    current_animation = AN_IDLE;
}

GraphicsEntity::~GraphicsEntity() {}

int32_t GraphicsEntity::getX() {
    return x;
}

int32_t GraphicsEntity::getY() {
    return y;
}


uint32_t GraphicsEntity::getId() {
    return id;
}

bool GraphicsEntity::is_dead() {
    return dead;
}

void GraphicsEntity::update_x(int32_t x) {
    this->x = x;
}


