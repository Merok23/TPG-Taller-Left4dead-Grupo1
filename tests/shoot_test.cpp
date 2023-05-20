#include <catch2/catch_all.hpp>
#include "../server/game.h"
#include "../server/entity_player.h"
#include "../server/entity_infected.h"

TEST_CASE("Shooting test, one entity gets shot") {
    Game game(100, 100);
    Player newPlayer = Player(1, 5, 5);
    Entity* player = &newPlayer;
    Infected newInfected = Infected(2, 20, 5);
    Entity* some_infected = &newInfected;
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
    Player newPlayer = Player(1, 20, 5);
    Entity* player = &newPlayer;
    Infected newInfected = Infected(2, 5, 5);
    Entity* some_infected = &newInfected;
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
    Player newPlayer = Player(1, 5, 5);
    Entity* player = &newPlayer;
    Infected newInfected = Infected(2, 20, 5);
    Entity* infected = &newInfected;
    Infected newInfected2 = Infected(3, 25, 5);
    Entity* infected2 = &newInfected2;
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