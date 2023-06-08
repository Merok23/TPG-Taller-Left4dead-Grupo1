#include "game_state.h"
#include <string>
#include <iostream>
#include <memory>

GameState::GameState(const std::map<uint32_t, std::shared_ptr<Entity>>& entities,
    bool game_over,
    bool players_won) : 
    entities(entities), 
    game_over(game_over),
    players_won(players_won){}

void GameState::print() {
    for (auto&& id_entity : this->entities) {
        std::cout << "id: " << id_entity.first << std::endl;
        std::cout << "type: " << id_entity.second->getType() << std::endl;
        std::cout << "hp: " << id_entity.second->getHitPoints() << std::endl;
        std::cout << "x: " << id_entity.second->getPositionX() << std::endl;
        std::cout << "y: " << id_entity.second->getPositionY() << std::endl;
        std::cout << "is facing left: " << id_entity.second->isFacingLeft() << std::endl;
        std::cout << "is moving up: " << id_entity.second->isMovingUp() << std::endl;
        std::cout << "state: " << id_entity.second->getStateEnum() << std::endl;
        std::cout << "weapon type: " << id_entity.second->getWeaponType() << std::endl;
        std::cout << "ammo left: " << id_entity.second->getAmmoLeft() << std::endl;
    }
}

GameState::~GameState() {
}
