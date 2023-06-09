#include "graphics_entity.h"

GraphicsEntity::GraphicsEntity(const std::map<AnimationName, std::shared_ptr<SdlTexture>> &textures, 
                                uint32_t id, int32_t x_position, int32_t y_position, int width, int height) :
    facingLeft(false), dead(false), id(id),
    x(x_position), y(y_position), width(width), height(height) //despues podemos hacer que el tamanio venga de un archivo
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
            current_animation = AN_DOWN;
            break;
        
        case REVIVING:
            current_animation = AN_IDLE;
            break;

        case SCREAMING:
            current_animation = AN_SCREAM;
            break;    
        
        case BLASTING:
            current_animation = AN_ATTACK2;
            break;
        
        case FLYING:
            current_animation = AN_PROJECTILE_FLYING;
            break;

        case EXPLODING:
            current_animation = AN_PROJECTILE_EXPLODING;
            break;
        
        case DESTROYED:
            current_animation = AN_IDLE;
            break;
        }
        
        x = entity->getPositionX() - width/2;
        y = entity->getPositionY() - height/2;
        
        facingLeft = entity->isFacingLeft();
    }

    auto it_current = animations.find(current_animation);
    if (it_current != animations.end()) {
        if (current_animation == AN_DIE || current_animation == AN_DOWN) {
            if (it_current->second->amountPlayed() == 0)
                it_current->second->update(dt, 3);
            else
                it_current->second->update(0, 0);
        }
        else if (current_animation == AN_SHOOT && entity && entity->getEntityType() == VENOM)
            it_current->second->update(dt, 4);
        else if (current_animation == AN_IDLE)
            it_current->second->update(dt, 5);
        else
            it_current->second->update(dt, 1);
    }
}

void GraphicsEntity::render() {
    SDL_RendererFlip flip = facingLeft ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
    Area destArea(x, y, width, height);
    
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


void GraphicsEntity::update_y(int32_t y) {
    this->y = y;
}


