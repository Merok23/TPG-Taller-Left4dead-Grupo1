#ifndef SERVER_ENTITY_PLAYER_H
#define SERVER_ENTITY_PLAYER_H

#include <vector>
#include <string>
#include <utility>
#include <algorithm>

#include "entity.h"
#include "movement.h"
#include "config.h"
#include "weapon.h"

enum SoldierState {
    IDLE_SOLDIER,
    MOVING_SOLDIER,
    SHOOTING_SOLDIER,
    RELOADING_SOLDIER,
    DOWN_SOLDIER,
    REVIVING_SOLDIER,
    DEAD_SOLDIER
};

class Player : public Entity {
    private:
        SoldierState state;
        Weapon* my_weapon;
        int32_t incapacitated;
        int32_t reload_cooldown;
        int32_t revival_countdown;
        int32_t time_until_dead;
        int lives; 
        uint32_t infected_killed;
        std::chrono::high_resolution_clock::time_point start_time_of_death; 
        uint32_t time_of_death;

    public:
        Player(uint32_t id, uint32_t positionX, uint32_t positionY, Weapon* weapon);
        virtual void move(int32_t x_movement, int32_t y_movement) override;
        virtual void update(Map& map) override;
        virtual void shoot(std::vector<HitEntity>& entities_hit) override;
        void setReload();
        virtual bool isInfected() override;
        virtual bool isSoldier() override;
        virtual std::string getEntityType() override;
        virtual bool isDead() override;
        virtual std::string getState() override;
        void stopShooting();
        int32_t getAmmoLeft();
        uint8_t getLives();
        bool isReviving();
        bool isDown();
        uint32_t getAmmountOfInfectedKilled();
        uint32_t getAmmountOfAmmoUsed();
        uint32_t getTimeOfDeath();
        void setReviving();
        virtual ~Player() override;
    private:
        void resolveDamage();
        void removeInfectedOutOfRange(std::vector<HitEntity>& entities_hit);
        void orderByDistance(std::vector<HitEntity>& entities_hit);
};
#endif
