#include <catch2/catch_all.hpp>
#include "../server/game.h"
#include "../server/entity_player.h"
#include "../server/weapon_idf.h"
#include "../server/config.h"
#include "../server/entity_crater.h"

TEST_CASE("Crater test, crater can't move", "[crater]") {
    Game game(CONFIG.scenario_width, CONFIG.scenario_height);
    Entity* crater = new Crater(1, 5, 5);
    game.addEntity(crater);
    game.setMoving(1, 1, 1);
    game.update();
    REQUIRE(game.getEntities()[1]->getDirectionOfMovement()->getX() == 5);
    REQUIRE(game.getEntities()[1]->getDirectionOfMovement()->getY() == 5);
}

TEST_CASE("Crater test, crater can be collided with", "[crater]") {
    Game game(CONFIG.scenario_width, CONFIG.scenario_height);
    Entity* crater = new Crater(1, 5, 5);
    Entity* player = new Player(2, CONFIG.crater_radius, 5, new MachineGun());
    game.addEntity(crater);
    game.addEntity(player);
    game.setMoving(2, -1, 0);
    game.update();
    REQUIRE(game.getEntities()[2]->getDirectionOfMovement()->getX() == CONFIG.crater_radius);
    REQUIRE(game.getEntities()[2]->getDirectionOfMovement()->getY() == 5);
}

TEST_CASE("Crater test, crater is collided with even from the bound of the map(crater start)", "[crater]") {
    Game game(CONFIG.scenario_width, CONFIG.scenario_height);
    Entity* crater = new Crater(1, 0, 5);
    Entity* player = new Player(2, CONFIG.scenario_width - CONFIG.crater_radius, 5, new MachineGun());
    game.addEntity(crater);
    game.addEntity(player);
    game.setMoving(2, 1, 0);
    game.update();
    REQUIRE(game.getEntities()[2]->getDirectionOfMovement()->getX() == CONFIG.scenario_width - CONFIG.crater_radius);
    REQUIRE(game.getEntities()[2]->getDirectionOfMovement()->getY() == 5);
}

TEST_CASE("Crater test, crater is collided with even from the bound of the map (crater end)", "[crater]") {
    Game game(CONFIG.scenario_width, CONFIG.scenario_height);
    Entity* crater = new Crater(1, CONFIG.scenario_width, 5);
    Entity* player = new Player(2, CONFIG.crater_radius, 5, new MachineGun());
    game.addEntity(crater);
    game.addEntity(player);
    game.setMoving(2, -1, 0);
    game.update();
    REQUIRE(game.getEntities()[2]->getDirectionOfMovement()->getX() == CONFIG.crater_radius);
    REQUIRE(game.getEntities()[2]->getDirectionOfMovement()->getY() == 5);
}