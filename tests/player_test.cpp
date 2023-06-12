#include <catch2/catch_all.hpp>
#include "../server/game.h"
#include "../server/entity_player.h"
#include "../server/config.h"
#include "../server/weapon_idf.h"

TEST_CASE("Player test, player moves 10 units", "[player]") {
    Game game(CONFIG.scenario_width, CONFIG.scenario_height);
    Weapon* weapon = new MachineGun(); 
    Entity* player = new Player(1, 0, CONFIG.soldier_radius, weapon);
    game.addEntity(player);
    game.setMoving(1, 1, 1);
    game.update();
    std::map<uint32_t, Entity*> entities = game.getEntities();
    REQUIRE(entities[1]->getDirectionOfMovement()->getX() == (1 * CONFIG.soldier_speed));
    REQUIRE(entities[1]->getDirectionOfMovement()->getY() == CONFIG.soldier_radius + (1 * CONFIG.soldier_speed));
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

TEST_CASE("Player test, tries to get far away from the other soldier and can't (centre of mass)", "[player]") {
    Game game(CONFIG.scenario_width, CONFIG.scenario_height);
    Weapon* weapon = new MachineGun(); 
    Weapon* weapon2 = new MachineGun(); 
    Entity* player = new Player(1, 0, CONFIG.soldier_radius, weapon);
    Entity* player2 = new Player(2, CONFIG.soldier_max_distance_from_mass_centre * 2, CONFIG.soldier_radius, weapon2);
    game.addEntity(player);
    game.addEntity(player2);
    game.setMoving(2, 1, 0);
    game.update();
    game.update();
    REQUIRE(game.getEntities()[2]->getDirectionOfMovement()->getX() == CONFIG.soldier_max_distance_from_mass_centre * 2);
}

TEST_CASE("Player test, if the other player is dead, it doesn't influence the centre of mass", "[player]") {
    Game game(CONFIG.scenario_width, CONFIG.scenario_height);
    Weapon* weapon = new MachineGun(); 
    Weapon* weapon2 = new MachineGun(); 
    Entity* player = new Player(1, 0, CONFIG.soldier_radius, weapon);
    Entity* player2 = new Player(2, CONFIG.soldier_max_distance_from_mass_centre * 2, CONFIG.soldier_radius, weapon2);
    game.addEntity(player);
    game.addEntity(player2);
    game.update();
    game.getEntities()[1]->setDamageForTheRound(CONFIG.soldier_health);
    game.update();
    for (int i = 0; i < CONFIG.soldier_max_time_until_dead; i++) game.update();
    //soldier dies:
    game.update();
    REQUIRE(game.getEntities()[1]->isDead() == true);
    game.setMoving(2, 1, 0);
    game.update();
    int final_x = CONFIG.soldier_max_distance_from_mass_centre * 2 + CONFIG.soldier_speed;
    REQUIRE(game.getEntities()[2]->getDirectionOfMovement()->getX() == final_x);
}
