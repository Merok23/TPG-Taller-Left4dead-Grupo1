#include <catch2/catch_all.hpp>
#include "../server/game.h"
#include "../server/entity_player.h"
#include "../server/weapon_scout.h"
#include "../server/weapon_idf.h"
#include "../server/weapon_p90.h"

TEST_CASE("Reloading test, scout reloads after it's magazine is empty and incapacitates the soldier until the reload is complete.", "[reloading]") {
    Game game(CONFIG.scenario_width, CONFIG.scenario_height);
    Weapon* weapon = new Scout();
    Entity* player = new Player(1, 5, 5, weapon);
    game.addEntity(player);
    game.setShooting(1);
    for (int i = 0; i < CONFIG.weapon_scout_magazine_size; i++) {
        game.update();
    }
    REQUIRE(weapon->emptyMagazine());
    game.update();
    game.setMoving(1, 1, 0);
    game.update();
    REQUIRE(game.getEntities()[1]->getDirectionOfMovement()->getX() == 5);
} 

TEST_CASE("Reloading test, idf reloads after it's magazine is empty and incapacitates the soldier until the reload is complete.", "[reloading]") {
    Game game(CONFIG.scenario_width, CONFIG.scenario_height);
    Weapon* weapon = new MachineGun();
    Entity* player = new Player(1, 5, 5, weapon);
    game.addEntity(player);
    game.setShooting(1);
    for (int i = 0; i < (CONFIG.weapon_idf_magazine_size / CONFIG.weapon_idf_burst_size); i++) {
        game.update();
    }
    REQUIRE(weapon->emptyMagazine());
    game.update();
    game.setMoving(1, 1, 0);
    game.update();
    REQUIRE(game.getEntities()[1]->getDirectionOfMovement()->getX() == 5);
}

TEST_CASE("Reloading test, p90 reloads after it's magazine is empty and incapacitates the soldier until the reload is complete.", "[reloading]") {
    Game game(CONFIG.scenario_width, CONFIG.scenario_height);
    Weapon* weapon = new AssaultRifle();
    Entity* player = new Player(1, 5, 5, weapon);
    game.addEntity(player);
    game.setShooting(1);
    for (int i = 0; i < (CONFIG.weapon_p90_magazine_size / CONFIG.weapon_p90_burst_size); i++) {
        game.update();
    }
    REQUIRE(weapon->emptyMagazine());
    game.update();
    game.setMoving(1, 1, 0);
    game.update();
    REQUIRE(game.getEntities()[1]->getDirectionOfMovement()->getX() == 5);
}

TEST_CASE("Reloading test, soldier tries to shoot and can't because he is reloading", "[reloading]") {
    Game game(CONFIG.scenario_width, CONFIG.scenario_height);
    Weapon* weapon = new Scout();
    Entity* player = new Player(1, 5, 5, weapon);
    game.addEntity(player);
    game.setShooting(1);
    for (int i = 0; i < CONFIG.weapon_scout_magazine_size; i++) {
        game.update();
    }
    REQUIRE(weapon->emptyMagazine());
    game.update();
    game.setShooting(1);
    game.update();
    int ammo_left = weapon->getAmmoLeft();
    REQUIRE(ammo_left == CONFIG.weapon_scout_magazine_size);
}

TEST_CASE("Reloading test, soldier tries to shoot after it completly reloaded and shoots", "[reloading]") {
    Game game(CONFIG.scenario_width, CONFIG.scenario_height);
    Weapon* weapon = new Scout();
    Entity* player = new Player(1, 5, 5, weapon);
    game.addEntity(player);
    game.setShooting(1);
    for (int i = 0; i < CONFIG.weapon_scout_magazine_size; i++) {
        game.update();
    }
    REQUIRE(weapon->emptyMagazine());
    //starts reloading:
    game.update();
    for (int i = 1; i < CONFIG.soldier_reload_cooldown; i++) {
        game.update();
    }
    //reload complete:
    game.update();
    //shoots:
    game.update();
    int ammo_left = weapon->getAmmoLeft();
    REQUIRE(ammo_left == CONFIG.weapon_scout_magazine_size - 1);
}

TEST_CASE("Reloading test, soldier reloads and can move after it", "[reloading]") {
    Game game(CONFIG.scenario_width, CONFIG.scenario_height);
    Weapon* weapon = new Scout();
    Entity* player = new Player(1, 5, 5, weapon);
    game.addEntity(player);
    game.setReloading(1);
    game.update();
    for (int i = 1; i < CONFIG.soldier_reload_cooldown; i++) {
        game.update();
    }
    //reload complete:
    game.update();
    //moves:
    game.setMoving(1, 1, 0);
    game.update();
    REQUIRE(game.getEntities()[1]->getState() == "moving");
    REQUIRE(game.getEntities()[1]->getDirectionOfMovement()->getX() == 5 + 1 * CONFIG.soldier_speed);
    game.update();
    REQUIRE(game.getEntities()[1]->getDirectionOfMovement()->getX() == 5 + 2 * CONFIG.soldier_speed);
}
