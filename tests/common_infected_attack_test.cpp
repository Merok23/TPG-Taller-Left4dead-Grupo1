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
}
