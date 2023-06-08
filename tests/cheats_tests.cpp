#include <catch2/catch_all.hpp>
#include "../server/game.h"
#include "../server/entity_player.h"
#include "../server/config.h"
#include "../server/weapon_idf.h"

TEST_CASE("Cheat test, player can be set to have infinite hitpoints", "[cheats]") {
    Game game(CONFIG.scenario_width, CONFIG.scenario_height);
    Weapon* weapon = new MachineGun(); 
    Entity* player = new Player(0, 0, CONFIG.soldier_radius, weapon);
    game.addEntity(player);
    game.setCheat(0, Cheat::INFINITE_HITPOINTS);
    game.update();
    std::map<uint32_t, Entity*> entities = game.getEntities();
    REQUIRE(entities[0]->getHitPoints() == CONFIG.cheat_infinite_hitpoints);
}

TEST_CASE("Cheat test, player can spawn a common_infected", "[cheats]") {
    Game game(CONFIG.scenario_width, CONFIG.scenario_height);
    Weapon* weapon = new MachineGun();
    Entity* player = new Player(0, 0, CONFIG.soldier_radius, weapon);
    game.addEntity(player);
    //we move the player so it's facing right.
    game.setMoving(0, 1, 0);
    game.update();
    game.setMoving(0, 0, 0);
    //we set the cheat to spawn a common infected
    game.setCheat(0, Cheat::SPAWN_COMMON_INFECTED);
    game.update();
    REQUIRE(game.getEntities().size() == 2);
    REQUIRE(game.getEntities()[1]->getHitPoints() == CONFIG.infected_health);
}

TEST_CASE("Cheat test, player can't spawn an infected because there is something in the way", "[cheats]") {
    Game game(CONFIG.scenario_width, CONFIG.scenario_height);
    Weapon* weapon = new MachineGun();
    Entity* player = new Player(0, 0, CONFIG.soldier_radius, weapon);
    game.addEntity(player);
    //we move the player so it's facing right.
    game.setMoving(0, 1, 0);
    game.update();
    game.setMoving(0, 0, 0);
    //we set the cheat to spawn a common infected
    game.setCheat(0, Cheat::SPAWN_COMMON_INFECTED);
    game.update();
    //we set the cheat to spawn a common infected
    game.setCheat(0, Cheat::SPAWN_COMMON_INFECTED);
    game.update();
    //infected didn't spawn because there was another one in the way.
    REQUIRE(game.getEntities().size() == 2);
    REQUIRE(game.getEntities()[1]->getHitPoints() == CONFIG.infected_health);
}
