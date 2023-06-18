#include <catch2/catch_all.hpp>
#include "../server/game.h"
#include "../server/entity_player.h"
#include "../server/entity_infected_venom.h"
#include "../server/config.h"
#include "../server/weapon_scout.h"

TEST_CASE("Venom test, he gets added and has all his correct stats", "[venom]") {
    Game game(CONFIG.scenario_width, CONFIG.scenario_height);
    uint32_t id = game.getCurrentId();
    Entity* infected = new VenomInfected(id, 0, CONFIG.venom_infected_radius);
    game.addEntity(infected);
    REQUIRE(game.getEntities()[id]->getHitPoints() == CONFIG.venom_infected_health);
    REQUIRE(game.getEntities()[id]->isInfected() == true);
    REQUIRE(game.getEntities()[id]->isSoldier() == false);
    REQUIRE(game.getEntities()[id]->isDead() == false);
    REQUIRE(game.getEntities()[id]->getEntityType() == "venom");
    REQUIRE(game.getEntities()[id]->getState() == "idle");
}

TEST_CASE("Venom test, when he is aligned with a player, he tries to shoot", "[venom]") {
    Game game(CONFIG.scenario_width, CONFIG.scenario_height);
    uint32_t id_venom = game.getCurrentId();
    Entity* infected = new VenomInfected(id_venom, 0, CONFIG.venom_infected_radius);
    game.addEntity(infected);
    uint32_t id_soldier = game.getCurrentId();
    Weapon* weapon = new Scout();
    Entity* player = new Player(id_soldier, CONFIG.venom_infected_shoot_range, CONFIG.venom_infected_radius, weapon);
    game.addEntity(player);
    game.update();
    REQUIRE(game.getEntities()[id_venom]->getState() == "shooting");
}

TEST_CASE("Venom test, when player is aligned but far from venom, he follows him", "[venom]") {
    Game game(CONFIG.scenario_width, CONFIG.scenario_height);
    uint32_t id_venom = game.getCurrentId();
    Entity* infected = new VenomInfected(id_venom, 0, CONFIG.venom_infected_radius);
    game.addEntity(infected);
    uint32_t id_soldier = game.getCurrentId();
    Weapon* weapon = new Scout();
    Entity* player = new Player(id_soldier, CONFIG.venom_infected_look_range, CONFIG.venom_infected_radius, weapon);
    game.addEntity(player);
    game.update();
    REQUIRE(game.getEntities()[id_venom]->getState() == "moving");
    REQUIRE(game.getEntities()[id_venom]->getDirectionOfMovement()->getX() == CONFIG.venom_infected_speed);
}

TEST_CASE("Venom test, when player is far way from venom, he's idle", "[venom]") {
    Game game(CONFIG.scenario_width, CONFIG.scenario_height);
    uint32_t id_venom = game.getCurrentId();
    Entity* infected = new VenomInfected(id_venom, 0, CONFIG.venom_infected_radius);
    game.addEntity(infected);
    uint32_t id_soldier = game.getCurrentId();
    Weapon* weapon = new Scout();
    Entity* player = new Player(id_soldier, CONFIG.venom_infected_look_range + 1, CONFIG.venom_infected_radius, weapon);
    game.addEntity(player);
    game.update();
    REQUIRE(game.getEntities()[id_venom]->getState() == "idle");
}

TEST_CASE("Venom test, when player is not aligned, but he is in range, venom is moving", "[venom]") {
    Game game(CONFIG.scenario_width, CONFIG.scenario_height);
    uint32_t id_venom = game.getCurrentId();
    Entity* infected = new VenomInfected(id_venom, 0, CONFIG.venom_infected_radius);
    game.addEntity(infected);
    uint32_t id_soldier = game.getCurrentId();
    Weapon* weapon = new Scout();
    Entity* player = new Player(id_soldier, CONFIG.venom_infected_shoot_range, CONFIG.venom_infected_radius * 3, weapon);
    game.addEntity(player);
    game.update();
    REQUIRE(game.getEntities()[id_venom]->getState() == "moving"); 
}

TEST_CASE("Venom test, when player is in range for the blast move, venom blasts and player loses hp", "[venom]") {
    Game game(CONFIG.scenario_width, CONFIG.scenario_height);
    uint32_t id_venom = game.getCurrentId();
    Entity* infected = new VenomInfected(id_venom, 0, CONFIG.venom_infected_radius);
    game.addEntity(infected);
    uint32_t id_soldier = game.getCurrentId();
    Weapon* weapon = new Scout();
    Entity* player = new Player(id_soldier, CONFIG.venom_infected_blast_range, CONFIG.venom_infected_radius, weapon);
    game.addEntity(player);
    //---------------------end setup---------------------//

    game.update();
    REQUIRE(game.getEntities()[id_venom]->getState() == "blasting");
    for (int i = 0; i < CONFIG.venom_infected_blast_incapacitated_time; i++) {
        game.update();
        REQUIRE(game.getEntities()[id_venom]->getState() == "blasting");
    }
    REQUIRE(game.getEntities()[id_soldier]->getHitPoints() == CONFIG.soldier_health - CONFIG.venom_infected_blast_damage);
}

TEST_CASE("Venom test, when player is hit by the blast move, he recieves damage in the 7th turn (or whatever the config says)", "[venom]") {
    Game game(CONFIG.scenario_width, CONFIG.scenario_height);
    uint32_t id_venom = game.getCurrentId();
    Entity* infected = new VenomInfected(id_venom, 0, CONFIG.venom_infected_radius);
    game.addEntity(infected);
    uint32_t id_soldier = game.getCurrentId();
    Weapon* weapon = new Scout();
    Entity* player = new Player(id_soldier, CONFIG.venom_infected_blast_range, CONFIG.venom_infected_radius, weapon);
    game.addEntity(player);
    //---------------------end setup---------------------//

    game.update();
    REQUIRE(game.getEntities()[id_venom]->getState() == "blasting");
    for (int i = 1; i < CONFIG.venom_infected_blast_damage_timing; i++) {
        game.update();
        REQUIRE(game.getEntities()[id_venom]->getState() == "blasting");
        REQUIRE(game.getEntities()[id_soldier]->getHitPoints() == CONFIG.soldier_health);
    }
    // 7th turn
    game.update();
    REQUIRE(game.getEntities()[id_venom]->getState() == "blasting");
    REQUIRE(game.getEntities()[id_soldier]->getHitPoints() == CONFIG.soldier_health - CONFIG.venom_infected_blast_damage);
}

TEST_CASE("Venom test, after blast, if player moves away, venom uses projectile (shoots)", "[venom]") {
    Game game(CONFIG.scenario_width, CONFIG.scenario_height);
    uint32_t id_venom = game.getCurrentId();
    Entity* infected = new VenomInfected(id_venom, 0, CONFIG.venom_infected_radius);
    game.addEntity(infected);
    uint32_t id_soldier = game.getCurrentId();
    Weapon* weapon = new Scout();
    Entity* player = new Player(id_soldier, CONFIG.venom_infected_blast_range, CONFIG.venom_infected_radius, weapon);
    game.addEntity(player);
    //---------------------end setup---------------------//

    game.update();
    REQUIRE(game.getEntities()[id_venom]->getState() == "blasting");
    game.setMoving(id_soldier, 1, 0); // carefu with the radius, if venom is lesser then it won't move
    for (int i = 1; i < CONFIG.venom_infected_blast_incapacitated_time; i++) {
        game.update();
        REQUIRE(game.getEntities()[id_venom]->getState() == "blasting");
    }
    game.update();
    //this may be out of range, so it may fail depending on the config values.
    REQUIRE(game.getEntities()[id_venom]->getState() == "shooting");
}

TEST_CASE("Venom test blast hits multiple soldiers", "[venom]") {
    Game game(CONFIG.scenario_width, CONFIG.scenario_height);
    uint32_t id_venom = game.getCurrentId();
    Entity* infected = new VenomInfected(id_venom, 0, CONFIG.venom_infected_radius);
    game.addEntity(infected);
    uint32_t id_soldier1 = game.getCurrentId();
    Weapon* weapon = new Scout();
    Entity* player1 = new Player(id_soldier1, CONFIG.venom_infected_blast_range, CONFIG.venom_infected_radius, weapon);
    game.addEntity(player1);
    uint32_t id_soldier2 = game.getCurrentId();
    Weapon* weapon2 = new Scout();
    Entity* player2 = new Player(id_soldier2, CONFIG.venom_infected_blast_range, CONFIG.venom_infected_radius, weapon2);
    game.addEntity(player2);
    //---------------------end setup---------------------//

    game.update();
    REQUIRE(game.getEntities()[id_venom]->getState() == "blasting");
    for (int i = 1; i < CONFIG.venom_infected_blast_incapacitated_time; i++) {
        game.update();
        REQUIRE(game.getEntities()[id_venom]->getState() == "blasting");
    }
    REQUIRE(game.getEntities()[id_soldier1]->getHitPoints() == CONFIG.soldier_health - CONFIG.venom_infected_blast_damage);
    REQUIRE(game.getEntities()[id_soldier2]->getHitPoints() == CONFIG.soldier_health - CONFIG.venom_infected_blast_damage);
}

TEST_CASE("Venom test, venom is killed and it doesn't seg fault :(", "[venom]") {
    Game game(CONFIG.scenario_width, CONFIG.scenario_height);
    uint32_t id_venom = game.getCurrentId();
    Entity* infected = new VenomInfected(id_venom, 0, CONFIG.venom_infected_radius);
    game.addEntity(infected);
    uint32_t id_soldier = game.getCurrentId();
    Weapon* weapon = new Scout();
    Entity* player = new Player(id_soldier, CONFIG.venom_infected_shoot_range, CONFIG.venom_infected_radius, weapon);
    game.addEntity(player);
    //---------------------end setup---------------------//

    //we let venom shoot some projectiles
    game.update();
    game.update();

    //we kill him
    game.setShooting(id_soldier);
    game.update();
    game.update();
    REQUIRE(game.getEntities()[id_venom]->isDead() == true);    
    //hopefully game didn't crash :)
}
