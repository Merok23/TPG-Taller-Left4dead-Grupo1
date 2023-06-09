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
    GraphicsEntity(const std::map<AnimationName, std::shared_ptr<SdlTexture>> &textures, 
                   uint32_t id, int32_t x_position, int32_t y_position, int width, int height);
    ~GraphicsEntity();
    virtual void update(float dt, Entity* entity);
    virtual void render();

    int32_t getX();
    int32_t getY();
    uint32_t getId();
    bool is_moving() {
        return (current_animation == AN_RUN || current_animation == AN_WALK);
    }

    bool is_dead();

    void update_x(int32_t x);
    void update_y(int32_t y);

protected:
    bool facingLeft;
    bool dead;
    uint32_t id;
    int32_t x;
    int32_t y;
    int width;
    int height;
    AnimationName current_animation;
    std::map<AnimationName, std::unique_ptr<Animation>> animations;
};


#endif //GRAPHICS_ENTITY_H
