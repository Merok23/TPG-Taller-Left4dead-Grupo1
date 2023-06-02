#include <catch2/catch_all.hpp>
#include "../server/game.h"
#include "../server/entity_player.h"
#include "../server/entity_infected_common.h"
#include "../server/config.h"
#include "../server/weapon_scout.h"
#include <iostream>

TEST_CASE("Dead state test, infected gets killed and it's dead", "[dying]") {
    Game game(100, 100);
    Weapon* weapon = new Scout();
    Entity* player = new Player(1, 5, 5, weapon);
    Entity* infected = new CommonInfected(2, 25, 5);
    game.addEntity(player);
    game.addEntity(infected);
    game.setMoving(1, 1, 0);
    game.update();
    game.setShooting(1);
    game.update();
    REQUIRE(game.getEntities()[2]->isDead() == true);
}

TEST_CASE("Dead state test, infected gets killed and you can walk over it", "[dying]") {
    Game game(100, 100);
    Weapon* weapon = new Scout();
    Entity* player = new Player(1, 5, 5, weapon);
    Entity* infected = new CommonInfected(2, 25, 5);
    game.addEntity(player);
    game.addEntity(infected);
    game.setMoving(1, 1, 0);
    game.update();
    game.setShooting(1);
    game.update();
    REQUIRE(game.getEntities()[2]->isDead() == true);
    game.setMoving(1, 1, 0);
    game.update();
    REQUIRE
    (game.getEntities()[1]->getDirectionOfMovement()->getX() == 5 + (CONFIG.soldier_speed * 2));
    game.update();
    REQUIRE
    (game.getEntities()[1]->getDirectionOfMovement()->getX() == 5 + (CONFIG.soldier_speed * 3));
}

TEST_CASE("Dead state test, infected can walk over dead infected", "[dying]") {
    Game game(10000, 100);
    Weapon* weapon = new Scout();
    Entity* player = new Player(1, 5, 5, weapon);
    Entity* infected = new CommonInfected(2, 25, 5);
    Entity* infected2 = new CommonInfected(3, 9995, 5);
    game.addEntity(player);
    game.addEntity(infected);
    game.addEntity(infected2);
    game.setMoving(1, 1, 0);
    game.update();
    game.setShooting(1);
    game.update();
    REQUIRE(game.getEntities()[2]->isDead() == true);
    REQUIRE(game.getEntities()[3]->isDead() == false);
    game.setMoving(1, 1, 0);
    game.update();
    game.update();
    //player it's at 35, 5
    REQUIRE
    (game.getEntities()[1]->getDirectionOfMovement()->getX() == 5 + (CONFIG.soldier_speed * 3));
    game.setMoving(1, 0, 0);
    game.update();
    game.update();
    //infected 2 should catch up with the player and walk over the dead infected
    REQUIRE(game.getEntities()[3]->getDirectionOfMovement()->getX() == 25);
}
