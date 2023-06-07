#include <catch2/catch_all.hpp>
#include "../server/game.h"
#include "../server/entity_player.h"
#include "../server/entity_infected_common.h"
#include "../server/weapon_idf.h"

TEST_CASE("Shooting test, one entity gets shot") {
    Game game(100, 100);
    Weapon* weapon = new MachineGun(); 
    Entity* player = new Player(1, 5, 5, weapon);
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
    Weapon* weapon = new MachineGun(); 
    Entity* player = new Player(1, 20, 5, weapon);
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

TEST_CASE("Shooting test, two entitites get shoot, the second one isn't damaged") {
    Game game(100, 100);
    Weapon* weapon = new MachineGun(); 
    Entity* player = new Player(1, 5, 5, weapon);
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
    REQUIRE(entities[3]->getHitPoints() == CONFIG.infected_health);
}

TEST_CASE("Shooting test, no movement is done and it shoots to the left", "[shooting]") {
    Game game(100, 100);
    Weapon* weapon = new MachineGun(); 
    Entity* player = new Player(1, 5, 5, weapon);
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
    Weapon* weapon = new MachineGun(); 
    Weapon* weapon2 = new MachineGun(); 
    Entity* player = new Player(1, 5, 5, weapon);
    Entity* player2 = new Player(2, 20, 5, weapon2);
    game.addEntity(player);
    game.addEntity(player2);
    game.setShooting(2);
    game.update();
    std::map<uint32_t, Entity*> entities = game.getEntities();
    REQUIRE(entities[1]->getHitPoints() == CONFIG.soldier_health);
}

TEST_CASE("Shooting test, soldier shoots infected and doesn't damage friendly unit", "[shooting]") {
    Game game(CONFIG.scenario_height, CONFIG.scenario_width);
    Weapon* weapon = new MachineGun(); 
    Weapon* weapon2 = new MachineGun(); 
    //they were so closed that the infected attacked the soldier with id 1
    Entity* player = new Player(1, 0, CONFIG.soldier_radius, weapon);
    Entity* player2 = new Player(2, CONFIG.soldier_radius * 2, CONFIG.soldier_radius, weapon2);
    int radius_summ = CONFIG.soldier_radius + CONFIG.common_infected_radius;
    Entity* infected = new CommonInfected(3, radius_summ * 2, CONFIG.soldier_radius);
    game.addEntity(player);
    game.addEntity(player2);
    game.addEntity(infected);
    game.setMoving(1, 1, 0);
    game.update();
    game.setShooting(1);
    game.update();
    std::map<uint32_t, Entity*> entities = game.getEntities();
    //the infected will attack once
    REQUIRE(entities[2]->getHitPoints() == CONFIG.soldier_health - CONFIG.common_infected_damage);
    REQUIRE(entities[3]->getHitPoints() < CONFIG.infected_health);
}

TEST_CASE("Shooting test, soldier stops shooting by moving", "[shooting]") {
    Game game(100, 100);
    Weapon* weapon = new MachineGun(); 
    Entity* player = new Player(1, 5, 5, weapon);
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
    Weapon* weapon = new MachineGun(); 
    Entity* player = new Player(1, 5, 5, weapon);
    Entity* infected = new CommonInfected(2, 20, 5);
    game.addEntity(player);
    game.addEntity(infected);
    game.setMoving(1, 1, 0);
    game.update();
    game.setShooting(1);
    game.update();
    std::map<uint32_t, Entity*> initialEntities = game.getEntities();
    game.stopShooting(1);
    game.update();
    std::map<uint32_t, Entity*> entities = game.getEntities();
    REQUIRE(entities[2]->getHitPoints() == initialEntities[2]->getHitPoints());
}

TEST_CASE("Shooting test, soldier hits infected that is not aligned dead centre", "[shooting]") {
    Game game(100, 100);
    Weapon* weapon = new MachineGun(); 
    Entity* player = new Player(1, 5, 5, weapon);
    Entity* infected = new CommonInfected(2, 20, 10);
    game.addEntity(player);
    game.addEntity(infected);
    game.setMoving(1, 1, 0);
    game.update();
    game.setShooting(1);
    game.update();
    std::map<uint32_t, Entity*> entities = game.getEntities();
    REQUIRE(entities[2]->getHitPoints() < CONFIG.infected_health);
}

TEST_CASE("Shooting test, soldier reloads on command", "[shooting]") {
    Game game(100, 100);
    Weapon* weapon = new MachineGun(); 
    Entity* player = new Player(1, 5, 5, weapon);
    game.addEntity(player);
    game.setShooting(1);
    game.update();
    game.setReloading(1);
    game.update();
    int ammo_left = weapon->getAmmoLeft();
    REQUIRE(ammo_left == CONFIG.weapon_idf_magazine_size);
}

TEST_CASE("Shooting test, soldier stops shooting when it moves", "[shooting]") {
    Game game(100, 100);
    Weapon* weapon = new MachineGun();
    Entity* player = new Player(1, 5, 5, weapon);
    game.addEntity(player);
    game.setShooting(1);
    game.update();
    game.setMoving(1, 1, 0);
    game.update();
    int ammo_left = weapon->getAmmoLeft();
    REQUIRE(ammo_left == CONFIG.weapon_idf_magazine_size - CONFIG.weapon_idf_burst_size);
}

TEST_CASE("Shooting test, soldier stops shooting when it reloads", "[shooting]") {
    Game game(100, 100);
    Weapon* weapon = new MachineGun();
    Entity* player = new Player(1, 5, 5, weapon);
    game.addEntity(player);
    game.setShooting(1);
    game.update();
    game.setReloading(1);
    game.update();
    game.update();
    int ammo_left = weapon->getAmmoLeft();
    REQUIRE(ammo_left == CONFIG.weapon_idf_magazine_size);
}
