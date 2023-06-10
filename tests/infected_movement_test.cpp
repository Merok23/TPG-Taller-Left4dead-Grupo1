#include <catch2/catch_all.hpp>
#include "../server/game.h"
#include "../server/entity_player.h"
#include "../server/entity_infected_common.h"
#include "../server/config.h"
#include "../server/weapon_idf.h"

TEST_CASE("Infected test, infected follows a soldier on the X axis", "[common_infected]") {
    Game game(CONFIG.scenario_width, CONFIG.scenario_height);
    Weapon* weapon = new MachineGun(); 
    Entity* player = new Player(1, CONFIG.common_infected_range, CONFIG.common_infected_radius, weapon);
    Entity* infected = new CommonInfected(2, 0, CONFIG.common_infected_radius);
    game.addEntity(player);
    game.addEntity(infected);
    game.update();
    std::map<uint32_t, Entity*> entities = game.getEntities();
    REQUIRE(entities[2]->getDirectionOfMovement()->getX() == (1 * CONFIG.common_infected_speed));
}

TEST_CASE("Infected test, infected follows a soldier on the Y axis", "[common_infected]") {
    Game game(CONFIG.scenario_width, CONFIG.scenario_height);
    Weapon* weapon = new MachineGun(); 
    Entity* player = new Player(1, 5, CONFIG.common_infected_range, weapon);
    Entity* infected = new CommonInfected(2, 5, CONFIG.common_infected_radius);
    game.addEntity(player);
    game.addEntity(infected);
    game.update();
    std::map<uint32_t, Entity*> entities = game.getEntities();
    REQUIRE(entities[2]->getDirectionOfMovement()->getY() == CONFIG.common_infected_radius + (1 * CONFIG.common_infected_speed));
}

TEST_CASE
("Infected test, soldiers is far away from infected so he doesn't follow", "[common_infected]") {
    Game game(CONFIG.scenario_width, CONFIG.scenario_height);
    Weapon* weapon = new MachineGun();
    Entity* player = new Player(1, CONFIG.common_infected_range * 2, 5, weapon);
    Entity* infected = new CommonInfected(2, 0, CONFIG.common_infected_radius);
    game.addEntity(player);
    game.addEntity(infected);
    game.update();
    std::map<uint32_t, Entity*> entities = game.getEntities();
    REQUIRE(entities[2]->getDirectionOfMovement()->getX() == 0);
    REQUIRE(entities[2]->getDirectionOfMovement()->getY() == CONFIG.common_infected_radius);
}

TEST_CASE("Infected test, infected follows a soldier on the X and Y axis", "[common_infected]") {
    Game game(CONFIG.scenario_width, CONFIG.scenario_height);
    Weapon* weapon = new MachineGun();
    Entity* player = 
    new Player(1, CONFIG.common_infected_range/2, CONFIG.common_infected_range/2, weapon);
    Entity* infected = new CommonInfected(2, 0,  CONFIG.common_infected_radius);
    game.addEntity(player);
    game.addEntity(infected);
    game.update();
    std::map<uint32_t, Entity*> entities = game.getEntities();
    REQUIRE(entities[2]->getDirectionOfMovement()->getX() ==  (1 * CONFIG.common_infected_speed));
    REQUIRE(entities[2]->getDirectionOfMovement()->getY() ==  CONFIG.common_infected_radius + (1 * CONFIG.common_infected_speed));
}

TEST_CASE
("Infected test, infected follows a soldier through the X border soldier start, infected end.",
     "[common_infected]") {
    Game game(CONFIG.scenario_width, CONFIG.scenario_height);
    Weapon* weapon = new MachineGun();
    int radius_sum = CONFIG.soldier_radius + CONFIG.common_infected_radius;
    Entity* player = new Player(1, radius_sum + CONFIG.common_infected_attack_range + 1, CONFIG.common_infected_radius, weapon);
    Entity* infected = new CommonInfected(2, CONFIG.scenario_width, CONFIG.common_infected_radius);
    game.addEntity(player);
    game.addEntity(infected);
    game.update();
    std::map<uint32_t, Entity*> entities = game.getEntities();
    REQUIRE(entities[2]->getDirectionOfMovement()->getX() == (1 * CONFIG.common_infected_speed));
}

TEST_CASE
("Infected test, infected follos soldier through the X border, soldier end infected start",
     "[common_infected]") {
    Game game(CONFIG.scenario_width, CONFIG.scenario_height);
    Weapon* weapon = new MachineGun();
    int suma_radios = CONFIG.soldier_radius + CONFIG.common_infected_radius;
    int posicion_x = CONFIG.scenario_width - suma_radios - CONFIG.common_infected_attack_range - 1;
    Entity* player = new Player(1, posicion_x, CONFIG.common_infected_radius, weapon);
    Entity* infected = new CommonInfected(2, 0, CONFIG.common_infected_radius);
    game.addEntity(player);
    game.addEntity(infected);
    game.update();
    std::map<uint32_t, Entity*> entities = game.getEntities();
    REQUIRE
    (entities[2]->getDirectionOfMovement()->getX() == 
    CONFIG.scenario_width - CONFIG.common_infected_speed);
}

TEST_CASE
("Infected test, infected collides with another infected and stays behind it",
 "[common_infected]") {
    Game game(CONFIG.scenario_width, CONFIG.scenario_height);
    Weapon* weapon = new MachineGun();
    Entity* player = new Player(1, 0, CONFIG.soldier_radius, weapon);
    int suma_radios = CONFIG.soldier_radius + CONFIG.common_infected_radius;
    Entity* infected1 = new CommonInfected(2, suma_radios, CONFIG.soldier_radius);
    Entity* infected2 = new CommonInfected(3, suma_radios + CONFIG.common_infected_radius, CONFIG.common_infected_radius);
    game.addEntity(player);
    game.addEntity(infected1);
    game.addEntity(infected2);
    game.update();
    REQUIRE(game.getEntities()[1]->getDirectionOfMovement()->getX() == 0);
    REQUIRE(game.getEntities()[1]->getDirectionOfMovement()->getY() == CONFIG.soldier_radius);
    REQUIRE(game.getEntities()[2]->getDirectionOfMovement()->getX() == suma_radios);
    REQUIRE(game.getEntities()[2]->getDirectionOfMovement()->getY() == CONFIG.soldier_radius);
    //infected 2 moved to player but got stuck behind infected 1
    REQUIRE(game.getEntities()[3]->getDirectionOfMovement()->getX() == suma_radios + CONFIG.common_infected_radius);
    REQUIRE(game.getEntities()[3]->getDirectionOfMovement()->getY() == CONFIG.common_infected_radius);
    game.update();
    //everyone stays the same
    REQUIRE(game.getEntities()[1]->getDirectionOfMovement()->getX() == 0);
    REQUIRE(game.getEntities()[1]->getDirectionOfMovement()->getY() == CONFIG.soldier_radius);
    REQUIRE(game.getEntities()[2]->getDirectionOfMovement()->getX() == suma_radios);
    REQUIRE(game.getEntities()[2]->getDirectionOfMovement()->getY() == CONFIG.soldier_radius);
    REQUIRE(game.getEntities()[3]->getDirectionOfMovement()->getX() == suma_radios + CONFIG.common_infected_radius);
    REQUIRE(game.getEntities()[3]->getDirectionOfMovement()->getY() == CONFIG.common_infected_radius);
}
