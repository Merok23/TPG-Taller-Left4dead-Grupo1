#include <catch2/catch_all.hpp>
#include "../server/game.h"
#include "../server/entity_player.h"
#include "../server/weapon_idf.h"


TEST_CASE("Finish conditions test, game gets created without players and it's not over (Clear The Zone)", "[game_finish]") {
    Game game(CONFIG.scenario_width, CONFIG.scenario_height, GameMode::CLEAR_THE_ZONE);
    std::shared_ptr<GameStateForClient> game_state = game.update();
    REQUIRE(game_state->isGameOver() == false);
}

TEST_CASE("Finish conditions test, game gets created without players and it's not over (Survival mode)", "[game_finish]") {
    Game game(CONFIG.scenario_width, CONFIG.scenario_height, GameMode::SURVIVAL);
    std::shared_ptr<GameStateForClient> game_state = game.update();
    REQUIRE(game_state->isGameOver() == false);
}

TEST_CASE("Finish conditions test, game gets created with players and it's not over (Clear The Zone)", "[game_finish]") {
    Game game(CONFIG.scenario_width, CONFIG.scenario_height, GameMode::CLEAR_THE_ZONE);
    Weapon* weapon = new MachineGun();
    Entity* player = new Player(0, 0, CONFIG.soldier_radius, weapon);
    game.addEntity(player);
    std::shared_ptr<GameStateForClient> game_state = game.update();
    REQUIRE(game_state->isGameOver() == false);
}

TEST_CASE("Finish conditions test, game gets created with players and it's not over (Survival mode)", "[game_finish]") {
    Game game(CONFIG.scenario_width, CONFIG.scenario_height, GameMode::SURVIVAL);
    Weapon* weapon = new MachineGun();
    Entity* player = new Player(0, 0, CONFIG.soldier_radius, weapon);
    game.addEntity(player);
    std::shared_ptr<GameStateForClient> game_state = game.update();
    REQUIRE(game_state->isGameOver() == false);
}

TEST_CASE("Finish conditions test, Clear The Zone is won by the players", "[game_finish]") {
    Game game(CONFIG.scenario_width, CONFIG.scenario_height, GameMode::CLEAR_THE_ZONE);
    Weapon* weapon = new MachineGun();
    Entity* player = new Player(0, 0, CONFIG.soldier_radius, weapon);
    game.addEntity(player);
    //we update so the game adds the zombies:
    game.update();
    game.setCheat(0, Cheat::KILL_ALL_INFECTED);
    std::shared_ptr<GameStateForClient> game_state = game.update();
    REQUIRE(game_state->isGameOver() == true);
    REQUIRE(game_state->didPlayersWin() == true);
}

TEST_CASE("Player gets killed in survival and game is over", "[game_finish]") {
    Game game(CONFIG.scenario_width, CONFIG.scenario_height, GameMode::SURVIVAL);
    Weapon* weapon = new MachineGun();
    Entity* player = new Player(0, 0, CONFIG.soldier_radius, weapon);
    Entity* infected = new CommonInfected(1, CONFIG.common_infected_attack_range, CONFIG.soldier_radius);
    game.addEntity(player);
    game.addEntity(infected);
    int attacks_needed = ceil(CONFIG.soldier_health / CONFIG.common_infected_damage);
    //we wait for the soldier to be mauled to death, this time can vary depending
    //on the infected that spawn.
    for (int i = 0; i < attacks_needed * CONFIG.common_infected_attack_cooldown + CONFIG.soldier_max_time_until_dead; i++) game.update();

    game.update();
    REQUIRE(game.getEntities()[0]->isDead() == true);
    std::shared_ptr<GameStateForClient> game_state = game.update();
    REQUIRE(game_state->isGameOver() == true);
    REQUIRE(game_state->didPlayersWin() == false);
}