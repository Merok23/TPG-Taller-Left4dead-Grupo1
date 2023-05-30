#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Animation.h"
#include <memory>
#include <map>

enum AnimationName {
    AN_IDLE,
    AN_RUN,
    AN_SHOOT,
    AN_DIE
};

class Player {
public:
    Player(std::map<AnimationName, std::shared_ptr<SdlTexture>> textures, int32_t x_position, int32_t y_position, int32_t hit_points);
    ~Player();
    void update(float dt);
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

    int getX();
    int getY();

private:
    bool facingLeft;
    bool facingUp;
    bool moving_x;
    bool moving_y;
    bool shooting;
    int32_t x;
    int32_t y;
    int32_t health;
    int32_t max_health;
    std::map<AnimationName, std::unique_ptr<Animation>> animations;
};

#endif // __PLAYER_H__
