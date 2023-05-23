#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "../libs/Animation.h"

class Player {
public:
    Player(SdlTexture &texture_idle, SdlTexture &texture_run, SdlTexture &texture_shot, SdlTexture &texture_die);
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
    Animation an_idle;
    Animation an_run;
    Animation an_shoot;
    Animation an_die;
    bool facingLeft;
    bool facingUp;
    bool moving_x;
    bool moving_y;
    bool shooting;
    int x;
    int y;
    int health;
};

#endif // __PLAYER_H__