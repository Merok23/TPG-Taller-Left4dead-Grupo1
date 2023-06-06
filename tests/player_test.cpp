#include <catch2/catch_all.hpp>
#include "../server/game.h"
#include "../server/entity_player.h"
#include "../server/config.h"
#include "../server/weapon_idf.h"

TEST_CASE("Player test, player moves 10 units", "[player]") {
    Game game(CONFIG.scenario_width, CONFIG.scenario_height);
    Weapon* weapon = new MachineGun(); 
    Entity* player = new Player(1, 5, 5, weapon);
    game.addEntity(player);
    game.setMoving(1, 1, 1);
    game.update();
    std::map<uint32_t, Entity*> entities = game.getEntities();
    REQUIRE(entities[1]->getDirectionOfMovement()->getX() == 5 + (1 * CONFIG.soldier_speed));
    REQUIRE(entities[1]->getDirectionOfMovement()->getY() == 5 + (1 * CONFIG.soldier_speed));
}

TEST_CASE("Player test, tries to move through other player and can't", "[player]") {
    Game game(CONFIG.scenario_width, CONFIG.scenario_height);
    Weapon* weapon = new MachineGun(); 
    Weapon* weapon2 = new MachineGun(); 
    Entity* player = new Player(1, 0, CONFIG.soldier_radius, weapon);
    Entity* player2 = new Player(2, CONFIG.soldier_radius * 2, CONFIG.soldier_radius, weapon2);
    game.addEntity(player);
    game.addEntity(player2);
    game.setMoving(1, 1, 0);
    game.update();
    std::map<uint32_t, Entity*> entities = game.getEntities();
    REQUIRE(entities[1]->getDirectionOfMovement()->getX() == 0);
    REQUIRE(entities[1]->getDirectionOfMovement()->getY() == CONFIG.soldier_radius);
}

TEST_CASE
("Player test, tries to move beyond a player and is stopped by the other player", "[player]") {
    Game game(CONFIG.scenario_width, CONFIG.scenario_height);
    Weapon* weapon = new MachineGun(); 
    Weapon* weapon2 = new MachineGun(); 
    Entity* player = new Player(1, 0, CONFIG.soldier_radius, weapon);
    Entity* player2 = new Player(2, CONFIG.soldier_radius * 2, CONFIG.soldier_radius, weapon2);
    game.addEntity(player);
    game.addEntity(player2);
    game.setMoving(1, 1, 0);
    game.update();
    game.update();
    std::map<uint32_t, Entity*> entities = game.getEntities();
    REQUIRE(entities[1]->getDirectionOfMovement()->getX() == 0);
    REQUIRE(entities[1]->getDirectionOfMovement()->getY() == CONFIG.soldier_radius);
}
