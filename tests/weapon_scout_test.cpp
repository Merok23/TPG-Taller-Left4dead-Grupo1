#include <catch2/catch_all.hpp>
#include "../server/game.h"
#include "../server/entity_player.h"
#include "../server/entity_infected_common.h"
#include "../server/weapon_scout.h"

TEST_CASE("Scout weapon test, it causes damage to the infected", "[scout]") {
    Game game(100, 100);
    Weapon* weapon = new Scout(); 
    Entity* player = new Player(1, 5, 5, weapon);
    Entity* some_infected = new CommonInfected(2, 20, 5);
    game.addEntity(player);
    game.addEntity(some_infected);
    game.setMoving(1, 1, 0);
    game.update();
    game.setShooting(1);
    game.update();
    std::map<uint32_t, Entity*> entities = game.getEntities();
    REQUIRE(entities[2]->getHitPoints() == 
    CONFIG.infected_health - CONFIG.weapon_scout_base_damage);
}

TEST_CASE("Scout damages three infected in a row", "[scout]") {
    Game game(100, 100);
    Weapon* weapon = new Scout(); 
    Entity* player = new Player(1, 5, 5, weapon);
    Entity* infected = new CommonInfected(2, 20, 5);
    Entity* infected2 = new CommonInfected(3, 25, 5);
    Entity* infected3 = new CommonInfected(4, 30, 5);
    game.addEntity(player);
    game.addEntity(infected);
    game.addEntity(infected2);
    game.addEntity(infected3);
    game.setMoving(1, 1, 0);
    game.update();
    game.setShooting(1);
    game.update();
    std::map<uint32_t, Entity*> entities = game.getEntities();
    REQUIRE(entities[2]->getHitPoints() < CONFIG.infected_health);
    REQUIRE(entities[3]->getHitPoints() < CONFIG.infected_health);
    REQUIRE(entities[4]->getHitPoints() < CONFIG.infected_health);
}

TEST_CASE("Scout damage falls off for each zombie hit", "[scout]") {
    Game game(100, 100);
    Weapon* weapon = new Scout(); 
    Entity* player = new Player(1, 5, 5, weapon);
    Entity* infected = new CommonInfected(2, 20, 5);
    Entity* infected2 = new CommonInfected(3, 25, 5);
    Entity* infected3 = new CommonInfected(4, 30, 5);
    game.addEntity(player);
    game.addEntity(infected);
    game.addEntity(infected2);
    game.addEntity(infected3);
    game.setMoving(1, 1, 0);
    game.update();
    game.setShooting(1);
    game.update();
    std::map<uint32_t, Entity*> entities = game.getEntities();
    REQUIRE(entities[2]->getHitPoints() > entities[3]->getHitPoints());
    REQUIRE(entities[3]->getHitPoints() > entities[4]->getHitPoints());
}

TEST_CASE("Scout reloads after it's out of rounds", "[scout]") {
    Game game(100, 100);
    Weapon* weapon = new Scout(); 
    Entity* player = new Player(1, 5, 5, weapon);
    game.addEntity(player);
    game.setShooting(1);
    for(int i = 0; i < CONFIG.weapon_scout_magazine_size; i++) {
        game.update();
    }
    int ammo_left = weapon->getAmmoLeft();       
    REQUIRE(ammo_left == 0);
    game.update();
    ammo_left = weapon->getAmmoLeft();
    REQUIRE(ammo_left == CONFIG.weapon_scout_base_damage);
}
