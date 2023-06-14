#include <catch2/catch_all.hpp>
#include "../server/game.h"
#include "../server/entity_player.h"
#include "../server/entity_infected_common.h"
#include "../server/entity_infected_spear.h"
#include "../server/weapon_idf.h"

TEST_CASE("Clear the zone test, game gets created with a fixed ammount of infected in it", "[clear the zone]") {
    Game game(CONFIG.scenario_width, CONFIG.scenario_height, GameMode::CLEAR_THE_ZONE);
    long unsigned int total = CONFIG.clear_the_zone_infected_total + CONFIG.crater_ammount;
    game.update();
    REQUIRE(game.getEntities().size() == total);
}
