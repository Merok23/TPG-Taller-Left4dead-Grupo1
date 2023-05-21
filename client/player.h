#ifndef CLIENT_PLAYER_H
#define CLIENT_PLAYER_H
#include "entity.h"

class Player : public Entity {
    private:
    int id;
    int x_position; 
    int y_position;

    public: 
    Player(int id, int x, int y, int health);
    int get_X_position(); 
    int get_Y_position();
};

#endif