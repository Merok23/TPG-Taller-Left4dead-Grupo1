#include <catch2/catch_all.hpp>
#include "../server/game.h"
#include "../server/entity_player.h"
#include "../server/entity_infected_common.h"
#include "../server/config.h"

TEST_CASE("Infected test, infected follows a soldier on the X axis", "[common_infected]") {
    Game game(100, 100);
    Entity* player = new Player(1, CONFIG.common_infected_range, 5);
    Entity* infected = new CommonInfected(2, 5, 5);
    game.addEntity(player);
    game.addEntity(infected);
    game.update();
    std::map<uint32_t, Entity*> entities = game.getEntities();
    REQUIRE(entities[2]->getDirectionOfMovement()->getX() == 5 + (1 * CONFIG.infected_speed) - (CONFIG.default_radius * 2));
}

TEST_CASE("Infected test, infected follows a soldier on the Y axis", "[common_infected]") {
    Game game(100, 100);
    Entity* player = new Player(1, 5, CONFIG.common_infected_range);
    Entity* infected = new CommonInfected(2, 5, 5);
    game.addEntity(player);
    game.addEntity(infected);
    game.update();
    std::map<uint32_t, Entity*> entities = game.getEntities();
    REQUIRE(entities[2]->getDirectionOfMovement()->getY() == 5 + (1 * CONFIG.infected_speed) - (CONFIG.default_radius * 2));
}

TEST_CASE("Infected test, soldiers is far away from infected so he doesn't follow", "[common_infected]") {
    Game game(100,100); 
    Entity* player = new Player(1, CONFIG.common_infected_range + 1, 5);
    Entity* infected = new CommonInfected(2, 5, 5);
    game.addEntity(player);
    game.addEntity(infected);
    game.update();
    std::map<uint32_t, Entity*> entities = game.getEntities();
    REQUIRE(entities[2]->getDirectionOfMovement()->getX() == 5);
}

TEST_CASE("Infected test, infected follows a soldier on the X and Y axis", "[common_infected]") {
    Game game(100, 100);
    Entity* player = new Player(1, CONFIG.common_infected_range, CONFIG.common_infected_range);
    Entity* infected = new CommonInfected(2, 5, 5);
    game.addEntity(player);
    game.addEntity(infected);
    game.update();
    std::map<uint32_t, Entity*> entities = game.getEntities();
    REQUIRE(entities[2]->getDirectionOfMovement()->getX() == 5 + (1 * CONFIG.infected_speed) - (CONFIG.default_radius * 2));
    REQUIRE(entities[2]->getDirectionOfMovement()->getY() == 5 + (1 * CONFIG.infected_speed) - (CONFIG.default_radius * 2));
}

TEST_CASE("Infected test, infected follows a soldier through the X border", "[common_infected]") {
    Game game(100, 100);
    Entity* player = new Player(1,CONFIG.common_infected_range - 10, 5);
    Entity* infected = new CommonInfected(2, 90, 5);
    game.addEntity(player);
    game.addEntity(infected);
    game.update();
    std::map<uint32_t, Entity*> entities = game.getEntities();
    REQUIRE(entities[2]->getDirectionOfMovement()->getX() == 100);
}
