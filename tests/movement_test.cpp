#include <catch2/catch_all.hpp>
#include "../server/movement.h"


TEST_CASE("Movement test, make one move", "[movement]") {
    Movement movement(5, 5, 10);
    movement.setDirection(1,1);
    movement.move();
    REQUIRE(movement.getX() == 6);
    REQUIRE(movement.getY() == 6);
}

TEST_CASE("Movement test, make more than one move in succesion", "[movement]") {
    Movement movement(5, 5, 10);
    movement.setDirection(1,1);
    movement.move();
    movement.move();
    REQUIRE(movement.getX() == 7);
    REQUIRE(movement.getY() == 7);
}

TEST_CASE("Movement test, change direction", "[movement]") {
    Movement movement(5, 5, 10);
    movement.setDirection(1,1);
    movement.move();
    movement.setDirection(1,0);
    movement.move();
    REQUIRE(movement.getX() == 7);
    REQUIRE(movement.getY() == 6);
}

TEST_CASE("Movement test, collision between two movements", "[movement]") {
    Movement movement(5, 5, 5);
    Movement movement2(15, 5, 5);
    movement.setDirection(0, 0);
    REQUIRE(movement.checkForCollision(movement2) == false);
    movement.setDirection(1,0);
    REQUIRE(movement.checkForCollision(movement2) == true);
}

TEST_CASE("Movement test, three way collision", "[movement]") {
    Movement movement(5, 5, 5);
    Movement movement2(20, 5, 5);
    Movement movement3(15, 5, 5);
    movement.setDirection(1,0);
    movement2.setDirection(-1,0);
    REQUIRE(movement.checkForCollision(movement2) == false);
    REQUIRE(movement.checkForCollision(movement3) == true);
    REQUIRE(movement2.checkForCollision(movement3) == true);
}
