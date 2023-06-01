#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Animation.h"
#include "game_state.h"
#include <memory>
#include <map>
#include "health_bar.h"

enum AnimationName {
    AN_IDLE,
    AN_RUN,
    AN_SHOOT,
    AN_DIE
};

class Player {
public:
    Player(std::map<AnimationName, std::shared_ptr<SdlTexture>> textures, const SdlWindow &window, uint32_t id, int32_t x_position, int32_t y_position, int32_t hit_points);
    ~Player();
    void update(float dt, GameState *gs);
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

    int32_t getX();
    int32_t getY();
    uint32_t getId();


private:
    bool facingLeft;
    bool facingUp;
    bool moving_x;
    bool moving_y;
    bool shooting;
    uint32_t id;
    int32_t x;
    int32_t y;
    HealthBar health_bar;
    std::map<AnimationName, std::unique_ptr<Animation>> animations;
};

#endif // __PLAYER_H__
