#include <catch2/catch_all.hpp>
#include "../server/map.h"

TEST_CASE("Map test, add entity", "[map]") {
    Map map(100, 100);
    Movement movement(5, 5, 5);
    map.addEntity(1, &movement);
    REQUIRE(map.getEntities().size() == 1);
}

TEST_CASE("Map test, remove entity", "[map]") {
    Map map(100, 100);
    Movement movement(5, 5, 5);
    map.addEntity(1, &movement);
    REQUIRE(map.getEntities().size() == 1);
    map.removeEntity(1);
    REQUIRE(map.getEntities().size() == 0);
}

TEST_CASE("Map test, move entity", "[map]") {
    Map map(100, 100);
    Movement movement(5, 5, 5);
    movement.setDirection(1,1);
    map.addEntity(1, &movement);
    map.move(1);
    REQUIRE(map.getEntities()[1]->getX() == 6);
    REQUIRE(map.getEntities()[1]->getY() == 6);
}

TEST_CASE("Map test, entitiy doesn't move because of collision", "[map]") {
    Map map(100, 100);
    Movement movement(5, 5, 5);
    Movement movement2(15, 5, 5);
    movement.setDirection(1,0);
    map.addEntity(1, &movement);
    map.addEntity(2, &movement2);
    REQUIRE(map.move(1) == false);
    REQUIRE(map.getEntities()[1]->getX() == 5);
    REQUIRE(map.getEntities()[1]->getY() == 5);
}

TEST_CASE("Map test, two entities don't move because of collision", "[map]") {
    Map map(100, 100);
    Movement movement(5, 5, 5);
    Movement movement2(15, 5, 5);
    movement.setDirection(1,0);
    movement2.setDirection(-1,0);
    map.addEntity(1, &movement);
    map.addEntity(2, &movement2);
    REQUIRE(map.move(1) == false);
    REQUIRE(map.move(2) == false);
    REQUIRE(map.getEntities()[1]->getX() == 5);
    REQUIRE(map.getEntities()[1]->getY() == 5);
    REQUIRE(map.getEntities()[2]->getX() == 15);
    REQUIRE(map.getEntities()[2]->getY() == 5);
}

TEST_CASE("Map test, entity colides with the border of the map Y axis", "[map]") {
    Map map(100, 100);
    Movement movement(5, 5, 5);
    movement.setDirection(0,-1);
    map.addEntity(1, &movement);
    REQUIRE(map.move(1) == false);
    REQUIRE(map.getEntities()[1]->getX() == 5);
    REQUIRE(map.getEntities()[1]->getY() == 5);
}