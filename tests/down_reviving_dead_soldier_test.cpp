#include <catch2/catch_all.hpp>
#include <chrono>
#include <iostream>
#include "../server/game.h"
#include "../server/entity_player.h"
#include "../server/entity_infected_common.h"
#include "../server/config.h"
#include "../server/weapon_scout.h"
// Incluye las definiciones y modificaciones anteriores de las clases Game y EntityPlayer

TEST_CASE("Soldier is down after an attack", "[Game]") {
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
    game.update(); // no esta entrando a que un player esta down 
    REQUIRE(game.getEntities()[1]->getHitPoints() == 0);
    Player *player_cast = dynamic_cast<Player*>(game.getEntities()[1]);
    REQUIRE(player_cast->isDown() == true);

}

 TEST_CASE("Reviving nearby fallen soldier", "[Game]") {
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
    Player *player_cast = dynamic_cast<Player*>(game.getEntities()[1]);
    Weapon* weapon2 = new Scout();
    Entity* player2 = new Player(3, CONFIG.common_infected_attack_range, 3, weapon2);
    game.addEntity(player2);
    game.update();
    REQUIRE(player_cast->isReviving() == true);
    REQUIRE(player_cast->getLives() == 2);

} 

 TEST_CASE("Dead soldier because nobody saved him", "[Game]") {
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
    game.update(); // DOWN
    infected->move(150,150); // para que no este en rango de ataque
    Player *player_cast = dynamic_cast<Player*>(game.getEntities()[1]);
    for (int i = 0; i < CONFIG.max_time_until_dead; i++) {
        game.update();
    } 
    game.update(); //pasa el tiempo sin ayuda para morir
    REQUIRE(player_cast->isDead() == true);
} 

TEST_CASE("Alive soldier after reviving him, with less lives", "[Game]") {
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
    game.update();// down
    infected->move(150,150); // para que no este en rango de ataque
    Player *player_cast = dynamic_cast<Player*>(game.getEntities()[1]);
    Weapon* weapon2 = new Scout();
    Entity* player2 = new Player(3, CONFIG.common_infected_attack_range, 3, weapon2);
    game.addEntity(player2);
    game.update();
    REQUIRE(player_cast->isReviving() == true);
    for (int i = 0; i < CONFIG.time_to_revive; i++) {
        game.update();
    } 
    REQUIRE(player_cast->isReviving() == false);
    REQUIRE(player_cast->getLives() == 2);
    REQUIRE(player_cast->getHitPoints() == CONFIG.soldier_health / 2);
} 

TEST_CASE("Dead soldier because it was saved 3 times before", "[Game]") {
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
    std::cout << "attacks needed: " << CONFIG.common_infected_attack_cooldown * attacks_needed << std::endl;
    // FIRST TIME
    for (int i = 1; i < CONFIG.common_infected_attack_cooldown * attacks_needed; i++) {
        game.update();
    }
    game.update();// down
    infected->move(1000,1000); // para que no este en rango de ataque
    Player *player_cast = dynamic_cast<Player*>(game.getEntities()[1]);
    Weapon* weapon2 = new Scout();
    Entity* player2 = new Player(3, CONFIG.common_infected_attack_range, 3, weapon2);
    game.addEntity(player2);
    game.update();
    REQUIRE(player_cast->isReviving() == true);
    for (int i = 0; i < CONFIG.time_to_revive; i++) {
        game.update();
    } 
    REQUIRE(player_cast->isReviving() == false);
    REQUIRE(player_cast->getLives() == 2);
    REQUIRE(player_cast->getHitPoints() == CONFIG.soldier_health / 2); 

    // SECOND TIME
    infected->move(5,5);
    for (int i = 0; i < CONFIG.common_infected_attack_cooldown * attacks_needed / 2  + 5; i++) {
        game.update();
    }
    game.update();
    infected->move(1000,1000); // para que no este en rango de ataque
    REQUIRE(player_cast->isReviving() == true);
    for (int i = 0; i < CONFIG.time_to_revive; i++) {
        game.update();
    } 
    REQUIRE(player_cast->isReviving() == false);
    REQUIRE(player_cast->getLives() == 1);

    // THIRD TIME
    infected->move(5,5);
    for (int i = 0; i < CONFIG.common_infected_attack_cooldown * attacks_needed / 2  + 5; i++) {
        game.update();
    }
    REQUIRE(player_cast->isDead() == true);
    REQUIRE(player_cast->getLives() == 0);
}   