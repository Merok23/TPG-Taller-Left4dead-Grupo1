#include <catch2/catch_all.hpp>
#include "../server/game.h"
#include "../server/entity_player.h"
#include "../server/entity_infected_spear.h"
#include "../server/config.h"
#include "../server/weapon_scout.h"

TEST_CASE("Infected-Spear test, we can create and add an infected with a spear and kill it", "[spear]") {
    Game game(CONFIG.scenario_width, CONFIG.scenario_height);
    Weapon* weapon = new Scout();
    int radius_sum = CONFIG.spear_infected_radius + CONFIG.soldier_radius;
    Entity* player = new Player(1, radius_sum, CONFIG.soldier_radius, weapon);
    Entity* infected = 
    new SpearInfected(2, 0, CONFIG.soldier_radius);
    game.addEntity(player);
    game.addEntity(infected);
    REQUIRE(game.getEntities()[2]->isDead() == false);
    game.setShooting(1);
    game.update();
    REQUIRE(game.getEntities()[2]->isDead() == true);
}

TEST_CASE("infected-Spear test, spear attacks at specified range", "[spear]") {
    Game game(CONFIG.scenario_width, CONFIG.scenario_height);
    Weapon* weapon = new Scout();
    Entity* player = new Player(1, CONFIG.spear_infected_attack_range, CONFIG.spear_infected_radius, weapon);
    Entity* infected = new SpearInfected(2, 0, CONFIG.spear_infected_radius);
    game.addEntity(player);
    game.addEntity(infected);
    game.update();
    REQUIRE(game.getEntities()[1]->getHitPoints() < CONFIG.soldier_health);
}

TEST_CASE("Infected-Spear test, spear follows a soldier", "[spear]") {
    Game game(CONFIG.scenario_width, CONFIG.scenario_height);
    Weapon* weapon = new Scout();
    Entity* player = new Player(1, CONFIG.spear_infected_look_range, CONFIG.spear_infected_radius, weapon);
    Entity* infected = new SpearInfected(2, 0, CONFIG.spear_infected_radius);
    game.addEntity(player);
    game.addEntity(infected);
    game.update();
    REQUIRE(game.getEntities()[2]->getDirectionOfMovement()->getX() == CONFIG.spear_infected_speed);
}

TEST_CASE("Infected-Spear test, soldiers is far away from spear, so it doesn't move", "[spear]") {
    Game game(CONFIG.scenario_width, CONFIG.scenario_height);
    Weapon* weapon = new Scout();
    Entity* player = new Player(1, CONFIG.spear_infected_look_range + 1, CONFIG.spear_infected_radius, weapon);
    Entity* infected = new SpearInfected(2, 0, CONFIG.spear_infected_radius);
    game.addEntity(player);
    game.addEntity(infected);
    game.update();
    REQUIRE(game.getEntities()[2]->getDirectionOfMovement()->getX() == 0);
}
