#include <catch2/catch_all.hpp>
#include "../server/game.h"
#include "../server/entity_player.h"
#include "../server/entity_infected_common.h"

TEST_CASE("Shooting test, one entity gets shot") {
    Game game(100, 100);
    Entity* player = new Player(1, 5, 5);
    Entity* some_infected = new CommonInfected(2, 20, 5);
    game.addEntity(player);
    game.addEntity(some_infected);
    game.setMoving(1, 1, 0);
    game.update();
    game.setShooting(1);
    game.update();
    std::map<uint32_t, Entity*> entities = game.getEntities();
    REQUIRE(entities[2]->getHitPoints() < CONFIG.infected_health);
}

TEST_CASE("Shooting test, entity shoots the otherway and doesn't damage the infected") {
    Game game(100, 100);
    Entity* player = new Player(1, 20, 5);
    Entity* some_infected = new CommonInfected(2, 5, 5);
    game.addEntity(player);
    game.addEntity(some_infected);
    game.setMoving(1, 1, 0);
    game.update();
    game.setShooting(1);
    game.update();
    game.setShooting(1);
    game.update();
    std::map<uint32_t, Entity*> entities = game.getEntities();
    REQUIRE(entities[2]->getHitPoints() == CONFIG.infected_health);
}

TEST_CASE("Shooting test, two entitites get shoot") {
    Game game(100, 100);
    Entity* player = new Player(1, 5, 5);
    Entity* infected = new CommonInfected(2, 20, 5);
    Entity* infected2 = new CommonInfected(3, 25, 5);
    game.addEntity(player);
    game.addEntity(infected);
    game.addEntity(infected2);
    game.setMoving(1, 1, 0);
    game.update();
    game.setShooting(1);
    game.update();
    std::map<uint32_t, Entity*> entities = game.getEntities();
    REQUIRE(entities[2]->getHitPoints() < CONFIG.infected_health);
    REQUIRE(entities[3]->getHitPoints() < CONFIG.infected_health);
}
