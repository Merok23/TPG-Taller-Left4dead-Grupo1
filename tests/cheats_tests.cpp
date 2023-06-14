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

TEST_CASE("Cheat test, player gets infinite hitpoints and it doens't affect other player", "[cheats]") {
    Game game(CONFIG.scenario_width, CONFIG.scenario_height);
    Weapon* weapon = new MachineGun();
    Entity* player = new Player(0, 0, CONFIG.soldier_radius, weapon);
    game.addEntity(player);
    Weapon* weapon2 = new MachineGun();
    Entity* player2 = new Player(1, CONFIG.soldier_radius * 2, CONFIG.soldier_radius, weapon2);
    game.addEntity(player2);
    game.setCheat(0, Cheat::INFINITE_HITPOINTS);
    game.update();
    std::map<uint32_t, Entity*> entities = game.getEntities();
    REQUIRE(entities[0]->getHitPoints() == CONFIG.cheat_infinite_hitpoints);
    REQUIRE(entities[1]->getHitPoints() == CONFIG.soldier_health);
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

TEST_CASE("Cheat test, kill all infected kills all the infected", "[cheats]") {
    Game game(CONFIG.scenario_width, CONFIG.scenario_height, GameMode::CLEAR_THE_ZONE);
    //we wait for the game to add the zombies:
    game.update();
    game.setCheat(0, Cheat::KILL_ALL_INFECTED);
    std::shared_ptr<GameStateForClient> game_state = game.update();
    std::map<uint32_t, Entity*> entities = game_state->getEntities();
    for (auto infected : entities) {
        if (infected.second->isInfected()){
            REQUIRE(infected.second->isDead() == true);
        }
    }
}
