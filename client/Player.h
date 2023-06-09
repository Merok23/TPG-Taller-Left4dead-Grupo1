#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "graphics_entity.h"

class Player : public GraphicsEntity{
public:
    Player(std::map<AnimationName, std::shared_ptr<SdlTexture>> &textures, const SdlWindow &window, 
            uint32_t id, int32_t x_position, int32_t y_position, 
            int32_t hit_points, int32_t ammo);
    VisualBar &get_ammo();
    VisualBar &get_health_bar();

    void update(float dt, Entity* entity) override;
    void render() override;

private:
    VisualBar health_bar;
    VisualBar ammo;
};

#endif // __PLAYER_H__
