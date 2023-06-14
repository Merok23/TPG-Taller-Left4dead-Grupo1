#include <catch2/catch_all.hpp>
#include "../server/game.h"
#include "../server/entity_player.h"
#include "../server/config.h"
#include "../server/weapon_idf.h"

TEST_CASE("Spawn test, We spawn like 25 players and they don't collide", "[spawn test]") {
    Game game(CONFIG.scenario_width, CONFIG.scenario_height);
    for (int i = 0; i < 25; i++) {
        std::tuple<int, int> spawn = game.getPlayerSpawnPoint();
        Entity* player = new Player(game.getCurrentId(), std::get<0>(spawn), std::get<1>(spawn), new MachineGun());
        game.addEntity(player);
    }

    for (auto &&entity : game.getEntities()) {
        Movement* soldier_mov = entity.second->getDirectionOfMovement();
        for (auto &&entity2 : game.getEntities()) {
            if (entity.first != entity2.first) {
                Movement* soldier_mov2 = entity2.second->getDirectionOfMovement();
                REQUIRE(soldier_mov->checkForCollision(*soldier_mov2) == false);
            }            
        }
    }
}