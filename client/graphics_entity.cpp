#include "graphics_entity.h"

GraphicsEntity::GraphicsEntity(std::map<AnimationName, std::shared_ptr<SdlTexture>> &textures, 
                                uint32_t id, int32_t x_position, int32_t y_position) :
    facingLeft(false), dead(false), id(id),
    x(x_position), y(y_position), width(200), height(200) //despues podemos hacer que el tamanio venga de un archivo
{
    for (const auto &pair : textures)
        animations[pair.first] = std::unique_ptr<Animation>(new Animation(pair.second));

    current_animation = AN_IDLE;
}


void GraphicsEntity::update(float dt, Entity *entity) {
        
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

void GraphicsEntity::render() {
    SDL_RendererFlip flip = facingLeft ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
    Area destArea(x, y, width, height); //200 200 es que tan grande es el rect'angulo para el elemento
    
    auto it_current = animations.find(current_animation);
    if (it_current != animations.end())
            it_current->second->render(destArea, flip);
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


