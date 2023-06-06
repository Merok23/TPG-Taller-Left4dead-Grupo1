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
    Game game(CONFIG.scenario_width, CONFIG.scenario_height);
    Weapon* weapon = new Scout();
    int suma_radios = CONFIG.soldier_radius + CONFIG.common_infected_radius;
    Entity* player = new Player(1, 0, CONFIG.soldier_radius, weapon);
    Entity* infected = new CommonInfected(2, suma_radios, CONFIG.soldier_radius);
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
    (game.getEntities()[1]->getDirectionOfMovement()->getX() == CONFIG.soldier_speed);
    game.update();
    REQUIRE
    (game.getEntities()[1]->getDirectionOfMovement()->getX() == (CONFIG.soldier_speed * 2));
}

TEST_CASE("Dead state test, infected can walk over dead infected", "[dying]") {
    Game game(CONFIG.scenario_width, CONFIG.scenario_height);
    Weapon* weapon = new Scout();
    int suma_radios = CONFIG.common_infected_radius + CONFIG.soldier_radius;
    Entity* player = new Player(1, CONFIG.common_infected_radius, CONFIG.soldier_radius, weapon);
    Entity* infected = new CommonInfected(2, suma_radios, CONFIG.soldier_radius);
    Entity* infected2 = new CommonInfected(3, 0, CONFIG.soldier_radius);
    game.addEntity(player);
    game.addEntity(infected);
    game.setMoving(1, 1, 0);
    game.update();
    game.setShooting(1);
    game.update();
    REQUIRE(game.getEntities()[2]->isDead() == true);

    game.setMoving(1, 1, 0);
    game.update();
    game.update();
    game.update();
    //player it's at 45, 5
    REQUIRE
    (game.getEntities()[1]->getDirectionOfMovement()->getX() == 
        CONFIG.common_infected_radius + (CONFIG.soldier_speed * 3));
    game.addEntity(infected2);
    REQUIRE(game.getEntities()[3]->isDead() == false);
    game.setMoving(1, 0, 0);
    //at some point, the infected attacked the soldier(in the start), so we wait for him to be able
    //to move again.
    for (int i = 0; i < CONFIG.common_infected_attack_cooldown; i++) game.update();
    game.update();
    game.update();
    game.update();
    REQUIRE(game.getEntities()[1]->isDead() == false);
    //infected 2 should catch up with the player and walk over the dead infected
    REQUIRE(game.getEntities()[3]->getDirectionOfMovement()->getX() == (CONFIG.soldier_speed * 3) - CONFIG.common_infected_attack_range);
}
