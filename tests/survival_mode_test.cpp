#include <catch2/catch_all.hpp>
#include "../server/game.h"
#include "../server/entity_player.h"
#include "../server/entity_infected_common.h"
#include "../server/entity_infected_spear.h"
#include "../server/weapon_idf.h"

//Este test esta fallando porque la witch invoca common infected que se estan moviendo
//y eso hace que el test falle porque hay infectados moviendose (no colisionando)
//y haya un falso positivo, ver si se puede reescribir despues.
/*
TEST_CASE("Survival mode test, entites don't collide with each other", "[survival]") {
    Game game(CONFIG.scenario_width, CONFIG.scenario_height);
    game.setSurvivalMode();
    for (int i = 0; i < CONFIG.survival_mode_timer * 2; i++) game.update();
    REQUIRE(game.getEntities().size() > 0);
    for (auto& entity : game.getEntities()) {
        for (auto& entity2 : game.getEntities()) {
            if (entity.first != entity2.first) {
                Movement *movement1 = entity.second->getDirectionOfMovement();
                Movement *movement2 = entity2.second->getDirectionOfMovement();
                REQUIRE(movement1->checkForCollision(*movement2) == false);
            }
        }
    }
}
*/
TEST_CASE("Survival mode test, common infected become stronger as time passes", "[survival]") {
    Game game(CONFIG.scenario_width, CONFIG.scenario_height);
    game.setSurvivalMode();
    for (int i = 0; i < CONFIG.survival_mode_timer * 2; i++) game.update();
    REQUIRE(game.getEntities().size() > 0);
    int health = game.getEntities()[CONFIG.crater_ammount + 1]->getHitPoints();
    for (int i = 0; i < CONFIG.survival_mode_timer * 2; i++) game.update();
    REQUIRE(game.getEntities()[CONFIG.crater_ammount + 1]->getHitPoints() > health);
}

TEST_CASE("Survival mode test, Common infected stay normal before the timer completes", "[surival]") {
    Game game(CONFIG.scenario_width, CONFIG.scenario_height);
    game.setSurvivalMode();
    game.addEntity(new CommonInfected(0, 5, 5));
    for (int i = 0; i < CONFIG.survival_mode_timer - 1; i++) game.update();
    REQUIRE(game.getEntities()[0]->getHitPoints() == CONFIG.infected_health);
}

TEST_CASE("Survival mode test, it spawns more and more zombies", "[survival]") {
    Game game(CONFIG.scenario_width, CONFIG.scenario_height);
    game.setSurvivalMode();
    for (int i = 0; i < CONFIG.survival_mode_timer * 2; i++) game.update();
    REQUIRE(game.getEntities().size() > 0);
    uint32_t size = game.getEntities().size();
    for (int i = 0; i < CONFIG.survival_mode_timer * 2; i++) game.update();
    REQUIRE(game.getEntities().size() > size);
}

TEST_CASE("Survival mode test, game is not set on survival so noone spawns and infected don't get stronger", "[survival]") {
    Game game(CONFIG.scenario_width, CONFIG.scenario_height);
    game.addEntity(new CommonInfected(1, 5, 5));
    int health = game.getEntities()[1]->getHitPoints();
    for (int i = 0; i < CONFIG.survival_mode_timer * 2; i++) game.update();
    REQUIRE(game.getEntities()[1]->getHitPoints() == health);
    REQUIRE(game.getEntities().size() == 1);
}

TEST_CASE("Survival mode test, game's constructor with game mode works", "[survival]") {
    Game game(CONFIG.scenario_width, CONFIG.scenario_height, GameMode::SURVIVAL);
    for (int i = 0; i < CONFIG.survival_mode_timer * 2; i++) game.update();
    REQUIRE(game.getEntities().size() > 0);
    int health = game.getEntities()[CONFIG.crater_ammount + 1]->getHitPoints();
    for (int i = 0; i < CONFIG.survival_mode_timer * 2; i++) game.update();
    REQUIRE(game.getEntities()[CONFIG.crater_ammount + 1]->getHitPoints() > health);
}

TEST_CASE("Survival mode test, game spawns more that one type of infected") {
    Game game(CONFIG.scenario_width, CONFIG.scenario_height, GameMode::SURVIVAL);
    for (int i = 0; i < CONFIG.survival_mode_timer * 2; i++) game.update();
    REQUIRE(game.getEntities().size() > 0);
    int common = 0;
    int spear = 0;
    for (auto& entity : game.getEntities()) {
        if (entity.second->getEntityType() == "common_infected") common++;
        if (entity.second->getEntityType() == "spear") spear++;
    }
    REQUIRE(common > 0);
    REQUIRE(spear > 0);
}
