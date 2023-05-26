#include <catch2/catch_all.hpp>
#include "../server/game.h"
#include "../server/entity_player.h"
#include "../server/entity_infected_common.h"
#include "../server/config.h"
#include "../server/weapon_scout.h"

TEST_CASE("Dead state test, infected gets killed and it's dead") {
    Game game(100, 100);
    Weapon* weapon = new Scout();
    Entity* player = new Player(1, 5, 5, weapon);
    Entity* infected = new CommonInfected(2, 25, 5);
    game.addEntity(player);
    game.addEntity(infected);
    game.setMoving(1, 1, 0);
    game.update();
    game.setShooting(1);
    game.update();
    REQUIRE(game.getEntities()[2]->isDead() == true);
}






