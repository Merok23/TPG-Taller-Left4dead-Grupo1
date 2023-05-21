#include <catch2/catch_all.hpp>
#include "../server/game.h"
#include "../server/entity_player.h"
#include "../server/config.h"

TEST_CASE("Player test, player moves 10 units", "[player]") {
    Game game(100, 100);
    Entity* player = new Player(1, 5, 5);
    game.addEntity(player);
    game.setMoving(1, 1, 1);
    game.update();
    std::map<uint32_t, Entity*> entities = game.getEntities();
    REQUIRE(entities[1]->getDirectionOfMovement()->getX() == 5 + (1 * CONFIG.soldier_speed));
    REQUIRE(entities[1]->getDirectionOfMovement()->getY() == 5 + (1 * CONFIG.soldier_speed));
}

TEST_CASE("Player test, tries to move through other player and can't", "[player]") {
    Game game(100, 100);
    Entity* player = new Player(1, 5, 5);
    Entity* player2 = new Player(2, 15, 5);
    game.addEntity(player);
    game.addEntity(player2);
    game.setMoving(1, 1, 0);
    game.update();
    std::map<uint32_t, Entity*> entities = game.getEntities();
    REQUIRE(entities[1]->getDirectionOfMovement()->getX() == 5);
    REQUIRE(entities[1]->getDirectionOfMovement()->getY() == 5);
}

TEST_CASE("Player test, tries to move beyond a player and is stopped by the other player", "[player]") {
    Game game(100, 100);
    Entity* player = new Player(1, 5, 5);
    Entity* player2 = new Player(2, 25, 5);
    game.addEntity(player);
    game.addEntity(player2);
    game.setMoving(1, 1, 0);
    game.update();
    game.update();
    std::map<uint32_t, Entity*> entities = game.getEntities();
    REQUIRE(entities[1]->getDirectionOfMovement()->getX() == 25 -(2 * CONFIG.soldier_radius));
    REQUIRE(entities[1]->getDirectionOfMovement()->getY() == 5);
}
