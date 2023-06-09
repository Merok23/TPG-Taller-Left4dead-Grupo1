#ifndef GRAPHICS_ENTITY_H
#define GRAPHICS_ENTITY_H

#include "Animation.h"
#include "game_state.h"
#include <memory>
#include <map>
#include "visual_bar.h"
#include "client_enum.h"

class GraphicsEntity {
   public:
    GraphicsEntity(std::map<AnimationName, std::shared_ptr<SdlTexture>> &textures, 
                   uint32_t id, int32_t x_position, int32_t y_position);
    ~GraphicsEntity();
    virtual void update(float dt, Entity* entity) = 0;
    virtual void render() = 0;

    int32_t getX();
    int32_t getY();
    uint32_t getId();

    bool is_dead();

    void update_x(int32_t x);

protected:
    bool facingLeft;
    bool dead;
    uint32_t id;
    int32_t x;
    int32_t y;
    AnimationName current_animation;
    std::map<AnimationName, std::unique_ptr<Animation>> animations;
};


#endif //GRAPHICS_ENTITY_H
