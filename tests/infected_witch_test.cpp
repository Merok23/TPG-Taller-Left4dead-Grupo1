#include <catch2/catch_all.hpp>
#include "../server/game.h"
#include "../server/entity_player.h"
#include "../server/entity_infected_witch.h"
#include "../server/config.h"
#include "../server/weapon_scout.h"


TEST_CASE("Witch test, witch can be created with it's stats being correct", "[witch]") {
    Game game(CONFIG.scenario_width, CONFIG.scenario_height);
    Entity* witch = new WitchInfected(0, 0, CONFIG.witch_infected_radius);
    game.addEntity(witch);
    REQUIRE(game.getEntities()[0]->getHitPoints() == CONFIG.witch_infected_health);
    REQUIRE(game.getEntities()[0]->isInfected() == true);
    REQUIRE(game.getEntities()[0]->isSoldier() == false);
    REQUIRE(game.getEntities()[0]->isDead() == false);
    REQUIRE(game.getEntities()[0]->getEntityType() == "witch");
}

TEST_CASE("Witch test, witch can move", "[witch]") {
    Game game(CONFIG.scenario_width, CONFIG.scenario_height);
    Entity* witch = new WitchInfected(0, 0, CONFIG.witch_infected_radius);
    game.addEntity(witch);
    game.getEntities()[0]->move(1, 0);
    REQUIRE(game.getEntities()[0]->getDirectionOfMovement()->getX() == CONFIG.witch_infected_speed);
}

TEST_CASE("Witch test, witch follows soldier when it's close enough", "[witch]") {
    Game game(CONFIG.scenario_width, CONFIG.scenario_height);
    Weapon* weapon = new Scout();
    Entity* soldier = new Player(0, CONFIG.witch_infected_look_range, CONFIG.witch_infected_radius, weapon);
    Entity* witch = new WitchInfected(1, 0, CONFIG.witch_infected_radius);
    game.addEntity(soldier);
    game.addEntity(witch);
    game.update();
    REQUIRE(game.getEntities()[1]->getDirectionOfMovement()->getX() == CONFIG.witch_infected_speed);
}

TEST_CASE("Witch test, after a lot of time, witch has shouted at least once and spawned common infected", "[witch]") {
    Game game(CONFIG.scenario_width, CONFIG.scenario_height);
    Entity* witch = new WitchInfected(0, 0, CONFIG.witch_infected_radius);
    game.addEntity(witch);
    for (int i = 0; i < CONFIG.witch_infected_shout_probability * 1000; i++) game.update();
    REQUIRE(game.getEntities().size() > 1);
}

TEST_CASE("Witch test, witch attacks if it's in range", "[witch]") {
    Game game(CONFIG.scenario_width, CONFIG.scenario_height);
    Weapon* weapon = new Scout();
    Entity* soldier = new Player(0, CONFIG.witch_infected_attack_range, CONFIG.witch_infected_radius, weapon);
    Entity* witch = new WitchInfected(1, 0, CONFIG.witch_infected_radius);
    game.addEntity(soldier);
    game.addEntity(witch);
    REQUIRE(game.getEntities()[0]->getHitPoints() < CONFIG.soldier_health);
}

TEST_CASE("Witch test, witch is shoot and dies", "[witch]") {
    Game game(CONFIG.scenario_width, CONFIG.scenario_height);
    Weapon* weapon = new Scout();
    Entity* soldier = new Player(0, CONFIG.witch_infected_attack_range, CONFIG.witch_infected_radius, weapon);
    Entity* witch = new WitchInfected(1, 0, CONFIG.witch_infected_radius);
    game.addEntity(soldier);
    game.addEntity(witch);
    game.setShooting(0);
    game.update();
    game.stopShooting(0);
    REQUIRE(game.getEntities()[1]->isDead() == true);
}
