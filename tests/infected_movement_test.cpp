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
    Entity* player = new Player(1, CONFIG.scenario_width - 10, 5, weapon);
    Entity* infected = new CommonInfected(2, 0, 5);
    game.addEntity(player);
    game.addEntity(infected);
    game.update();
    std::map<uint32_t, Entity*> entities = game.getEntities();
    REQUIRE
    (entities[2]->getDirectionOfMovement()->getX() == 
    CONFIG.scenario_width - (1 * CONFIG.common_infected_speed));
}

TEST_CASE
("Infected test, infected collides with another infected and stays behind it",
 "[common_infected]") {
    Game game(CONFIG.scenario_width, CONFIG.scenario_height);
    Weapon* weapon = new MachineGun();
    Entity* player = new Player(1, 5, 5, weapon);
    Entity* infected1 = new CommonInfected(2, 15, 5);
    Entity* infected2 = new CommonInfected(3, 35, 5);
    game.addEntity(player);
    game.addEntity(infected1);
    game.addEntity(infected2);
    game.update();
    REQUIRE(game.getEntities()[1]->getDirectionOfMovement()->getX() == 5);
    REQUIRE(game.getEntities()[1]->getDirectionOfMovement()->getY() == 5);
    REQUIRE(game.getEntities()[2]->getDirectionOfMovement()->getX() == 15);
    REQUIRE(game.getEntities()[2]->getDirectionOfMovement()->getY() == 5);
    //infected 2 moved to player but got stuck behind infected 1
    REQUIRE(game.getEntities()[3]->getDirectionOfMovement()->getX() == 25);
    REQUIRE(game.getEntities()[3]->getDirectionOfMovement()->getY() == 5);
    game.update();
    //everyone stays the same
    REQUIRE(game.getEntities()[1]->getDirectionOfMovement()->getX() == 5);
    REQUIRE(game.getEntities()[1]->getDirectionOfMovement()->getY() == 5);
    REQUIRE(game.getEntities()[2]->getDirectionOfMovement()->getX() == 15);
    REQUIRE(game.getEntities()[2]->getDirectionOfMovement()->getY() == 5);
    REQUIRE(game.getEntities()[3]->getDirectionOfMovement()->getX() == 25);
    REQUIRE(game.getEntities()[3]->getDirectionOfMovement()->getY() == 5);
}
