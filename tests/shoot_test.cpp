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

TEST_CASE("Shooting test, no movement is done and it shoots to the left", "[shooting]") {
    Game game(100, 100);
    Entity* player = new Player(1, 5, 5);
    Entity* infected = new CommonInfected(2, 20, 5);
    game.addEntity(player);
    game.addEntity(infected);
    game.setShooting(1);
    game.update();
    std::map<uint32_t, Entity*> entities = game.getEntities();
    REQUIRE(entities[2]->getHitPoints() == CONFIG.infected_health);
}

TEST_CASE("Shooting test, soldier doesn't shoot friendlies", "[shooting]") {
    Game game(100, 100);
    Entity* player = new Player(1, 5, 5);
    Entity* player2 = new Player(2, 20, 5);
    game.addEntity(player);
    game.addEntity(player2);
    game.setShooting(2);
    game.update();
    std::map<uint32_t, Entity*> entities = game.getEntities();
    REQUIRE(entities[1]->getHitPoints() == CONFIG.soldier_health);
}

TEST_CASE("Shooting test, soldier shoots infected and doesn't damage friendly unit", "[shooting]") {
    Game game(100, 100);
    Entity* player = new Player(1, 5, 5);
    Entity* player2 = new Player(2, 20, 5);
    Entity* infected = new CommonInfected(3, 30, 5);
    game.addEntity(player);
    game.addEntity(player2);
    game.addEntity(infected);
    game.setMoving(1, 1, 0);
    game.setShooting(1);
    game.update();
    std::map<uint32_t, Entity*> entities = game.getEntities();
    REQUIRE(entities[2]->getHitPoints() == CONFIG.soldier_health);
    REQUIRE(entities[3]->getHitPoints() < CONFIG.infected_health);
}


TEST_CASE("Shooting test, soldier stops shooting by moving", "[shooting]") {
    Game game(100, 100);
    Entity* player = new Player(1, 5, 5);
    Entity* infected = new CommonInfected(2, 20, 5);
    game.addEntity(player);
    game.addEntity(infected);
    game.setShooting(1);
    game.setMoving(1, 1, 0);
    game.update();
    std::map<uint32_t, Entity*> entities = game.getEntities();
    REQUIRE(entities[2]->getHitPoints() == CONFIG.infected_health);
}

TEST_CASE("Shooting test, soldier stops shooting on command", "[shooting]") {
    Game game(100, 100);
    Entity* player = new Player(1, 5, 5);
    Entity* infected = new CommonInfected(2, 20, 5);
    game.addEntity(player);
    game.addEntity(infected);
    game.setMoving(1, 1, 0);
    game.update();
    game.addShootingEntity(1);
    game.update();
    game.removeShootingEntity(1);
    game.update();
    std::map<uint32_t, Entity*> entities = game.getEntities();
    REQUIRE(entities[2]->getHitPoints() == CONFIG.infected_health - 50);
}
