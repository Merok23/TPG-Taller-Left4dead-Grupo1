#include <catch2/catch_all.hpp>
#include "../server/game.h"
#include "../server/entity_player.h"
#include "../server/entity_infected_common.h"
#include "../server/weapon_idf.h"

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

TEST_CASE("Survival mode test, common infected become stronger as time passes", "[survival]") {
    Game game(CONFIG.scenario_width, CONFIG.scenario_height);
    game.setSurvivalMode();
    for (int i = 0; i < CONFIG.survival_mode_timer * 2; i++) game.update();
    REQUIRE(game.getEntities().size() > 0);
    int health = game.getEntities()[1]->getHitPoints();
    for (int i = 0; i < CONFIG.survival_mode_timer * 2; i++) game.update();
    REQUIRE(game.getEntities()[1]->getHitPoints() > health);
}

TEST_CASE("Survival mode test, Common infected stay normal before the timer completes", "[surival]") {
    Game game(CONFIG.scenario_width, CONFIG.scenario_height);
    game.setSurvivalMode();
    game.addEntity(new CommonInfected(1, 5, 5));
    for (int i = 0; i < CONFIG.survival_mode_timer - 1; i++) game.update();
    REQUIRE(game.getEntities()[1]->getHitPoints() == CONFIG.infected_health);
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
