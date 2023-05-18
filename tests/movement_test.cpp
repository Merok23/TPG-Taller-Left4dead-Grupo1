#include <catch2/catch_all.hpp>
#include "../server/movement.h"


TEST_CASE("Movement test, make one move", "[movement]") {
    Movement movement(5, 5, 10);
    movement.setDirection(1,1);
    movement.move();
    REQUIRE(movement.getX() == 6);
    REQUIRE(movement.getY() == 6);
}