#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Animation.h"
#include "game_state.h"
#include <memory>
#include <map>
#include "visual_bar.h"

enum AnimationName {
    AN_IDLE,
    AN_WALK,
    AN_RUN,
    AN_RUN_ATTACK,
    AN_JUMP,

    AN_ATTACK1,
    AN_ATTACK2,
    AN_ATTACK3,
    AN_BITE,
    AN_SCREAM,
    AN_SHOOT,

    AN_FALL,
    AN_EATING,
    AN_PROTECT,

    AN_RELOAD,
    AN_HURT,
    AN_DIE,

};

class Player {
public:
    Player(std::map<AnimationName, std::shared_ptr<SdlTexture>> &textures, const SdlWindow &window, 
            uint32_t id, int32_t x_position, int32_t y_position, int32_t hit_points);
    ~Player();
    void update(float dt, Entity *entity);
    void render();
    void moveRigth();
    void moveLeft();
    void moveUp();
    void moveDown();
    void stopMovingX();
    void stopMovingY();
    void shoot();
    void stopShooting();
    void hurt();
    void recharge();

    int32_t getX();
    int32_t getY();
    uint32_t getId();


private:
    bool facingLeft;
    bool facingUp;
    bool moving_x;
    bool moving_y;
    bool shooting;
    bool recharging;
    uint32_t id;
    int32_t x;
    int32_t y;
    AnimationName current_animation;
    VisualBar health_bar;
    VisualBar ammo;
    std::map<AnimationName, std::unique_ptr<Animation>> animations;
};

#endif // __PLAYER_H__
