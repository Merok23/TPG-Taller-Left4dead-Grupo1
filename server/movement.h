#include "position.h"

#define RADIUS 5 //se debe leer del config

class Movement {
    private:
        int x_movement;
        int y_movement;
        Position centre;
    public:
        Movement(int x, int y, double radius);
        int getX();
        int getY();
        double getRadius();
        void move(int x, int y);
        bool collision(Movement movement);
};