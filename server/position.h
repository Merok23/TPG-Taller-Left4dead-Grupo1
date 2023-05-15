#include <math.h>

class Position {
    private:
        int x;
        int y;
        double radius;
    public:
        Position(int x, int y, double radius);
        int getX();
        int getY();
        double getRadius();
        void move(int x, int y);
        bool checkForCollision(Position other_position);
};
