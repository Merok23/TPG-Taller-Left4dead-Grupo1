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
    DEAD_SOLDIER
};

class Player : public Entity {
    private:
        SoldierState state;
        Weapon* my_weapon;
        int32_t incapacitated;
        int32_t reload_cooldown;

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
        std::string getWeaponType();
        int32_t getAmmoLeft();
        virtual ~Player() override;
    private:
        void resolveDamage();
        void removeInfectedOutOfRange(std::vector<HitEntity>& entities_hit);
        void orderByDistance(std::vector<HitEntity>& entities_hit);
};
#endif
