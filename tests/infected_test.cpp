#include <catch2/catch_all.hpp>
#include "../server/game.h"
#include "../server/entity_player.h"
#include "../server/entity_infected_common.h"
#include "../server/config.h"
#include "../server/weapon_scout.h"

TEST_CASE("Infected don't follow dead soldier", "[infected]") {
    Game game(CONFIG.scenario_width, CONFIG.scenario_height);
    Weapon* weapon = new Scout();
    Entity* player = new Player(1, 0, CONFIG.common_infected_radius, weapon);
    int radius_sum = CONFIG.soldier_radius + CONFIG.common_infected_radius;
    Entity* infected = new CommonInfected(2, radius_sum, CONFIG.common_infected_radius);
    Weapon* weapon2 = new Scout();
    Entity* player2 = new Player(3, CONFIG.common_infected_range, CONFIG.common_infected_radius, weapon2);
    game.addEntity(player);
    game.addEntity(player2);
    game.addEntity(infected);
    int attacks_needed = CONFIG.soldier_health / CONFIG.common_infected_damage;
    int player_lives = CONFIG.soldier_lives;
    for (int i = 0; i < attacks_needed * player_lives * CONFIG.soldier_max_time_until_dead; i++) {
        game.update();
    }
    REQUIRE(game.getEntities()[1]->isDead() == true);
    //infected should chase the other soldier
    game.update();
    
    REQUIRE(game.getEntities()[2]->getDirectionOfMovement()->getX() != radius_sum);
}