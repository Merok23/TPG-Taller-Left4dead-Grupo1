#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Animation.h"
#include "game_state.h"
#include <memory>
#include <map>
#include "visual_bar.h"
#include "client_enum.h"

class Player {
public:
    Player(std::map<AnimationName, std::shared_ptr<SdlTexture>> &textures, const SdlWindow &window, 
            bool is_player, uint32_t id, int32_t x_position, int32_t y_position, int32_t hit_points);
    ~Player();
    void update(float dt, Entity* entity);
    void render();

    int32_t getX();
    int32_t getY();
    uint32_t getId();

    VisualBar &get_ammo();
    VisualBar &get_health_bar();

    bool is_dead();

    void update_x(int32_t x);

private:
    bool facingLeft;
    bool dead;
    bool is_player; //cambiar a clases con herencia
    uint32_t id;
    int32_t x;
    int32_t y;
    AnimationName current_animation;
    VisualBar health_bar;
    VisualBar ammo;
    std::map<AnimationName, std::unique_ptr<Animation>> animations;
};

#endif // __PLAYER_H__
