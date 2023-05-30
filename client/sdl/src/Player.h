#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "../libs/Animation.h"
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
    Player(std::map<AnimationName, SdlTexture*> &textures);
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
    int x;
    int y;
    int health;
    std::unique_ptr<Animation> an_idle;
    std::unique_ptr<Animation> an_run;
    std::unique_ptr<Animation> an_shoot;
    std::unique_ptr<Animation> an_die;
};

#endif // __PLAYER_H__