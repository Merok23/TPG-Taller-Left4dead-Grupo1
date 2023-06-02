#include <catch2/catch_all.hpp>
#include "../server/game.h"
#include "../server/entity_player.h"
#include "../server/entity_infected_common.h"
#include "../server/weapon_p90.h"

TEST_CASE("P90 weapon test, it causes damage to the infected", "[p90]") {
    Game game(100, 100);
    Weapon* weapon = new AssaultRifle(); 
    Entity* player = new Player(1, 5, 5, weapon);
    Entity* some_infected = new CommonInfected(2, 20, 5);
    game.addEntity(player);
    game.addEntity(some_infected);
    game.setMoving(1, 1, 0);
    game.update();
    game.setShooting(1);
    game.update();
    std::map<uint32_t, Entity*> entities = game.getEntities();
    Movement* mov = entities[1]->getDirectionOfMovement();
    Movement* mov2 = entities[2]->getDirectionOfMovement();
    uint32_t distance_mov = mov->calculateDistance(*mov2);
    double distance = distance_mov;
    double damage = CONFIG.weapon_p90_base_damage - CONFIG.weapon_p90_distance_modifier * distance;
    int32_t damage_int = damage;
    REQUIRE(entities[2]->getHitPoints() == CONFIG.infected_health - damage_int);
}

TEST_CASE
("IDF weapon test, it doesn't cause damage to the infected because he is out of range.", 
    "[p90]") {
    Game game(100, 100);
    Weapon* weapon = new AssaultRifle(); 
    Entity* player = new Player(1, 5, 5, weapon);
    Entity* some_infected = new CommonInfected(2, CONFIG.weapon_p90_range + 10, 5);
    game.addEntity(player);
    game.addEntity(some_infected);
    //move left
    game.setMoving(1, -1, 0);
    game.update();
    //move right so we are looking at it.
    game.setMoving(1, 1, 0);
    game.update();
    //shoot
    game.setShooting(1);
    game.update();
    std::map<uint32_t, Entity*> entities = game.getEntities();
    REQUIRE(entities[2]->getHitPoints() == CONFIG.infected_health);
}


TEST_CASE("P90 weapon test, weapon reduces ammo as expected", "[p90]") {
    Game game(100, 100);
    Weapon* weapon = new AssaultRifle(); 
    Entity* player = new Player(1, 5, 5, weapon);
    game.addEntity(player);
    game.setShooting(1);
    game.update();
    int ammo_left = weapon->getAmmoLeft();
    REQUIRE(ammo_left == CONFIG.weapon_p90_magazine_size - CONFIG.weapon_p90_burst_size);
}


TEST_CASE("P90 weapon test, has to recharge ammo as expected", "[p90]") {
    Game game(100, 100);
    Weapon* weapon = new AssaultRifle(); 
    Entity* player = new Player(1, 5, 5, weapon);
    game.addEntity(player);
    game.setShooting(1);
    for (int i = 0; i < (CONFIG.weapon_p90_magazine_size / CONFIG.weapon_p90_burst_size); i++) {
        game.update();
    }
    int ammo_left = weapon->getAmmoLeft();
    REQUIRE(ammo_left == 0);
    game.update();
    ammo_left = weapon->getAmmoLeft();
    REQUIRE(ammo_left == CONFIG.weapon_p90_magazine_size);
}

TEST_CASE
("P90 weapon test, only damage an infected out of two, the second is out of range",
 "[scout]") {
    Game game(100, 100);
    Weapon* weapon = new AssaultRifle(); 
    Entity* player = new Player(1, 5, 5, weapon);
    Entity* infected = new CommonInfected(2, 20, 5);
    Entity* infected2 = new CommonInfected(3, 200, 5);
    game.addEntity(player);
    game.addEntity(infected);
    game.addEntity(infected2);
    game.setMoving(1, 1, 0);
    game.update();
    game.setShooting(1);
    game.update();
    std::map<uint32_t, Entity*> entities = game.getEntities();
    REQUIRE(entities[2]->getHitPoints() < CONFIG.infected_health);
    REQUIRE(entities[3]->getHitPoints() == CONFIG.infected_health);
}
