#include <catch2/catch_all.hpp>
#include "../server/game.h"
#include "../server/entity_player.h"
#include "../server/config.h"
#include "../server/entity_projectile_venom.h"
#include "../server/entity_infected_venom.h"
#include "../server/weapon_scout.h"

TEST_CASE("Venom Projectile test, a projectile is created and it moves on update", "[projectile]") {
    Game game(CONFIG.scenario_width, CONFIG.scenario_height);
    uint32_t id_projectile = game.getCurrentId();
    Projectile* projectile = new VenomProjectile(id_projectile, 0, CONFIG.venom_infected_radius);
    projectile->move(1, 0);
    game.addEntity(projectile);
    game.update();
    REQUIRE(game.getEntities()[id_projectile]->getDirectionOfMovement()->getX() == CONFIG.venom_infected_projectile_speed);
} 

TEST_CASE("Venom Projectile Test, a projectile hits a target, causes damage, and dissapears", "[projectile]") {
    Game game(CONFIG.scenario_width, CONFIG.scenario_height);
    uint32_t id_venom = game.getCurrentId();
    Entity* venom = new VenomInfected(id_venom, 0, CONFIG.venom_infected_radius);
    game.addEntity(venom);
    uint32_t id_soldier = game.getCurrentId();
    Weapon* weapon = new Scout();
    Entity* player = new Player(id_soldier, CONFIG.venom_infected_shoot_range, CONFIG.venom_infected_radius, weapon);
    game.addEntity(player);
    //we wait for the projectile to hit, this may be an infinite loop, so we set a limit
    int i = 0;
    while(game.getEntities()[id_soldier]->getHitPoints() == CONFIG.soldier_health && i < 100) {
        game.update();
        i++;
    }
    REQUIRE(i < 100);
    REQUIRE(game.getEntities()[id_soldier]->getHitPoints() == CONFIG.soldier_health - CONFIG.venom_infected_shoot_damage);
    for (i = 0; i < CONFIG.venom_infected_projectile_explosion_counter; i++) {
        game.update();
    }
    //after a lot of time, the projectiles dissapears
    for (i = 0; i < 1000; i++) game.update();
    REQUIRE(game.getEntities().size() ==  2);
}

