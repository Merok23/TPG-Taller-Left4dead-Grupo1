#include <catch2/catch_all.hpp>
#include "../server/game.h"
#include "../server/entity_player.h"
#include "../server/entity_infected_common.h"
#include "../server/config.h"
#include "../server/weapon_scout.h"

TEST_CASE("Common infected attack, infected is out of range", "[common infected attack]") {
    Game game(CONFIG.scenario_width, CONFIG.scenario_height);
    Weapon* weapon = new Scout();
    Entity* player = new Player(1, CONFIG.common_infected_attack_range + 1 + 5, 5, weapon);
    Entity* infected = new CommonInfected(2, 5, 5);
    game.addEntity(player);
    game.addEntity(infected);
    game.update();
    REQUIRE(game.getEntities()[1]->getHitPoints() == CONFIG.soldier_health);
}

TEST_CASE
("Common infected attack, infected is in range so player loses health", "[common infected attack]") {
    Game game(CONFIG.scenario_width, CONFIG.scenario_height);
    Weapon* weapon = new Scout();
    Entity* player = new Player(1, CONFIG.common_infected_attack_range + 5, 5, weapon);
    Entity* infected = new CommonInfected(2, 5, 5);
    game.addEntity(player);
    game.addEntity(infected);
    game.update();
    REQUIRE(game.getEntities()[1]->getHitPoints() == CONFIG.soldier_health - CONFIG.common_infected_damage);
}

TEST_CASE("Common infected attack, infected attacks and has a cooldown", "[common infected attack]") {
    Game game(CONFIG.scenario_width, CONFIG.scenario_height);
    Weapon* weapon = new Scout();
    Entity* player = new Player(1, CONFIG.common_infected_attack_range + 5, 5, weapon);
    Entity* infected = new CommonInfected(2, 5, 5);
    game.addEntity(player);
    game.addEntity(infected);
    game.update();
    REQUIRE(game.getEntities()[1]->getHitPoints() == CONFIG.soldier_health - CONFIG.common_infected_damage);
    game.update();
    REQUIRE(game.getEntities()[1]->getHitPoints() == CONFIG.soldier_health - CONFIG.common_infected_damage);
}

TEST_CASE
("Common infected attack, after some time, the infected can attack again",
 "[common infected attack]") {
    Game game(CONFIG.scenario_width, CONFIG.scenario_height);
    Weapon* weapon = new Scout();
    Entity* player = new Player(1, CONFIG.common_infected_attack_range, 5, weapon);
    Entity* infected = new CommonInfected(2, 5, 5);
    game.addEntity(player);
    game.addEntity(infected);
    game.update();

    REQUIRE
        (game.getEntities()[1]->getHitPoints() == 
            CONFIG.soldier_health - CONFIG.common_infected_damage);

    for (int i = 1; i < CONFIG.common_infected_attack_cooldown; i++) {
        game.update();
    }
    REQUIRE
        (game.getEntities()[1]->getHitPoints() == 
            CONFIG.soldier_health - CONFIG.common_infected_damage);    
    game.update();

    REQUIRE
        (game.getEntities()[1]->getHitPoints() == 
            CONFIG.soldier_health - 2 * CONFIG.common_infected_damage);
}

TEST_CASE("Common infected attack, infected kills a soldier.", "[common infected attack]") {
    Game game(CONFIG.scenario_width, CONFIG.scenario_height);
    Weapon* weapon = new Scout();
    Entity* player = new Player(1, CONFIG.common_infected_attack_range, 5, weapon);
    Entity* infected = new CommonInfected(2, 5, 5);
    game.addEntity(player);
    game.addEntity(infected);
    game.update();
    int hp_after_attack = CONFIG.soldier_health - CONFIG.common_infected_damage;
    int attacks_needed = hp_after_attack / CONFIG.common_infected_damage;
    REQUIRE(game.getEntities()[1]->getHitPoints() == hp_after_attack);

    for (int i = 1; i < CONFIG.common_infected_attack_cooldown * attacks_needed; i++) {
        game.update();
    }
    game.update();
    REQUIRE(game.getEntities()[1]->getHitPoints() == 0);
    Player *player_cast = dynamic_cast<Player*>(game.getEntities()[1]);
    REQUIRE(player_cast->isDown());
    //bonus, we try to move the soldier and it doesn't move:
    game.setMoving(1, 1, 1);
    game.update();
    REQUIRE(game.getEntities()[1]->getDirectionOfMovement()->getX() == CONFIG.common_infected_attack_range);
    REQUIRE(game.getEntities()[1]->getDirectionOfMovement()->getY() == 5);
}

TEST_CASE("Common infected attack, multiple infected are spawned and only the closest one attacks", "[common infected attack]") {
    Game game(CONFIG.scenario_width, CONFIG.scenario_height);
    Weapon* weapon = new Scout();
    uint32_t soldier_id = game.getCurrentId();
    Entity* player = new Player(soldier_id, 0, CONFIG.common_infected_radius, weapon);
    game.addEntity(player);
    uint32_t closest_infected_id = game.getCurrentId();
    Entity* closest_infected = new CommonInfected(closest_infected_id, CONFIG.common_infected_radius + CONFIG.soldier_radius, CONFIG.common_infected_radius);
    game.addEntity(closest_infected);
    uint32_t x_position = CONFIG.common_infected_attack_range;
    uint32_t zombies = 100;
    for (uint32_t i = 0; i < zombies; i++) {
        x_position += x_position;
        Entity* infected_i = new CommonInfected(game.getCurrentId(), x_position, CONFIG.common_infected_radius);
        game.addEntity(infected_i);
    } 
    game.setCheat(soldier_id, Cheat::INFINITE_HITPOINTS);
    int counter = 1;
    game.update();
    for (int i = 0; i < 100000000000; i++) {
        REQUIRE(game.getEntities()[soldier_id]->isDead() == false);
        for (uint32_t j = 0; j < zombies; j++) {
            if (j != closest_infected_id) {
                if(game.getEntities()[j]->getState() == "attacking") counter++;
            }
            REQUIRE(counter == 2);
        }
    }
}
