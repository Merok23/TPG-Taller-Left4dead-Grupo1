#include <catch2/catch_all.hpp>
#include "../server/game.h"
#include "../server/entity_player.h"
#include "../server/entity_infected_common.h"
#include "../server/config.h"
#include "../server/weapon_idf.h"

TEST_CASE("Infected test, infected follows a soldier on the X axis", "[common_infected]") {
    Game game(100, 100);
    Weapon* weapon = new MachineGun(); 
    Entity* player = new Player(1, CONFIG.common_infected_range, 5, weapon);
    Entity* infected = new CommonInfected(2, 5, 5);
    game.addEntity(player);
    game.addEntity(infected);
    game.update();
    std::map<uint32_t, Entity*> entities = game.getEntities();
    REQUIRE(entities[2]->getDirectionOfMovement()->getX() == 5 + (1 * CONFIG.infected_speed));
}

TEST_CASE("Infected test, infected follows a soldier on the Y axis", "[common_infected]") {
    Game game(100, 100);
    Weapon* weapon = new MachineGun(); 
    Entity* player = new Player(1, 5, CONFIG.common_infected_range, weapon);
    Entity* infected = new CommonInfected(2, 5, 5);
    game.addEntity(player);
    game.addEntity(infected);
    game.update();
    std::map<uint32_t, Entity*> entities = game.getEntities();
    REQUIRE(entities[2]->getDirectionOfMovement()->getY() == 5 + (1 * CONFIG.infected_speed));
}

TEST_CASE
("Infected test, soldiers is far away from infected so he doesn't follow", "[common_infected]") {
    Game game(1000, 1000); 
    Weapon* weapon = new MachineGun();
    Entity* player = new Player(1, CONFIG.common_infected_range * 2, 5, weapon);
    Entity* infected = new CommonInfected(2, 5, 5);
    game.addEntity(player);
    game.addEntity(infected);
    game.update();
    std::map<uint32_t, Entity*> entities = game.getEntities();
    REQUIRE(entities[2]->getDirectionOfMovement()->getX() == 5);
    REQUIRE(entities[2]->getDirectionOfMovement()->getY() == 5);
}

TEST_CASE("Infected test, infected follows a soldier on the X and Y axis", "[common_infected]") {
    Game game(100, 100);
    Weapon* weapon = new MachineGun();
    Entity* player = 
    new Player(1, CONFIG.common_infected_range/2, CONFIG.common_infected_range/2, weapon);
    Entity* infected = new CommonInfected(2, 5, 5);
    game.addEntity(player);
    game.addEntity(infected);
    game.update();
    std::map<uint32_t, Entity*> entities = game.getEntities();
    REQUIRE(entities[2]->getDirectionOfMovement()->getX() == 5 + (1 * CONFIG.infected_speed));
    REQUIRE(entities[2]->getDirectionOfMovement()->getY() == 5 + (1 * CONFIG.infected_speed));
}

TEST_CASE
("Infected test, infected follows a soldier through the X border soldier start, infected end.",
     "[common_infected]") {
    Game game(CONFIG.scenario_width, CONFIG.scenario_height);
    Weapon* weapon = new MachineGun();
    Entity* player = new Player(1,CONFIG.common_infected_range - 10, 5, weapon);
    Entity* infected = new CommonInfected(2, CONFIG.scenario_width, 5);
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
    int posicion_x = CONFIG.scenario_width - suma_radios - CONFIG.common_infected_speed;
    Entity* player = new Player(1, posicion_x, 5, weapon);
    Entity* infected = new CommonInfected(2, 0, 5);
    game.addEntity(player);
    game.addEntity(infected);
    game.update();
    std::map<uint32_t, Entity*> entities = game.getEntities();
    REQUIRE
    (entities[2]->getDirectionOfMovement()->getX() == 
    posicion_x + suma_radios);
}

TEST_CASE
("Infected test, infected collides with another infected and stays behind it",
 "[common_infected]") {
    Game game(CONFIG.scenario_width, CONFIG.scenario_height);
    Weapon* weapon = new MachineGun();
    Entity* player = new Player(1, 0, CONFIG.soldier_radius, weapon);
    int suma_radios = CONFIG.soldier_radius + CONFIG.common_infected_radius;
    Entity* infected1 = new CommonInfected(2, suma_radios, CONFIG.soldier_radius);
    Entity* infected2 = new CommonInfected(3, suma_radios + CONFIG.common_infected_radius, CONFIG.soldier_radius);
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
    REQUIRE(game.getEntities()[3]->getDirectionOfMovement()->getY() == CONFIG.soldier_radius);
    game.update();
    //everyone stays the same
    REQUIRE(game.getEntities()[1]->getDirectionOfMovement()->getX() == 0);
    REQUIRE(game.getEntities()[1]->getDirectionOfMovement()->getY() == CONFIG.soldier_radius);
    REQUIRE(game.getEntities()[2]->getDirectionOfMovement()->getX() == suma_radios);
    REQUIRE(game.getEntities()[2]->getDirectionOfMovement()->getY() == CONFIG.soldier_radius);
    REQUIRE(game.getEntities()[3]->getDirectionOfMovement()->getX() == suma_radios + CONFIG.common_infected_radius);
    REQUIRE(game.getEntities()[3]->getDirectionOfMovement()->getY() == CONFIG.soldier_radius);
}
