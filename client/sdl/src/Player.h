#ifndef __WORM_H__
#define __WORM_H__

#include "Animation.h"

class Player {
public:
    Player(SdlTexture &texture_idle, SdlTexture &texture_run, SdlTexture &texture_shot);
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

private:
    Animation an_idle;
    Animation an_run;
    Animation an_shoot;
    bool facingLeft;
    bool facingUp;
    bool moving_x;
    bool moving_y;
    bool shooting;
    int x;
    int y;
};

#endif // __WORM_H__