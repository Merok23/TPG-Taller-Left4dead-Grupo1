#include <catch2/catch_all.hpp>
#include "../server/game.h"
#include "../server/entity_player.h"
#include "../server/weapon_idf.h"

TEST_CASE("Game test, add player", "[game]") {
    Game game(100, 100);
    Weapon* weapon = new MachineGun(); 
    Entity* player = new Player(1, 5, 5, weapon);
    game.addEntity(player);
    REQUIRE(game.getEntities().size() == 1);
}

TEST_CASE("Game test, set a direction and the player DOESN'T move", "[game]") {
    Game game(100, 100);
    Weapon* weapon = new MachineGun(); 
    Entity* player = new Player(1, CONFIG.soldier_radius, CONFIG.soldier_radius, weapon);
    game.addEntity(player);
    game.setMoving(1, 1, 1);
    REQUIRE(game.getEntities()[1]->getDirectionOfMovement()->getX() == CONFIG.soldier_radius);
    REQUIRE(game.getEntities()[1]->getDirectionOfMovement()->getX() == CONFIG.soldier_radius);
}

TEST_CASE("Game test, set a direction and then update, so the player MOVES", "[game]") {
    Game game(100, 100);
    Weapon* weapon = new MachineGun(); 
    Entity* player = new Player(1, 5, CONFIG.soldier_radius, weapon);
    game.addEntity(player);
    game.setMoving(1, 1, 1);
    game.update();
    REQUIRE(game.getEntities()[1]->getDirectionOfMovement()->getX() == 5 
        + (1 * CONFIG.soldier_speed));
    REQUIRE(game.getEntities()[1]->getDirectionOfMovement()->getY() == CONFIG.soldier_radius 
        + (1 * CONFIG.soldier_speed));
}

TEST_CASE("Game test, player doesn't move after update because of colition", "[game]") {
    Game game(100, 100);
    Weapon* weapon = new MachineGun(); 
    Weapon* weapon2 = new MachineGun(); 
    Entity* player = new Player(1, 0, CONFIG.soldier_radius, weapon);
    Entity* player2 = new Player(2, CONFIG.soldier_radius * 2, CONFIG.soldier_radius, weapon2);
    game.addEntity(player);
    game.addEntity(player2);
    game.setMoving(1, 1, 0);
    game.update();
    REQUIRE(game.getEntities()[1]->getDirectionOfMovement()->getX() == 0);
}
