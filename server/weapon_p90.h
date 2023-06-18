#ifndef SERVER_WEAPON_P90_H
#define SERVER_WEAPON_P90_H

#include "weapon.h"
#include "config.h"
#include <string>
# pragma once


class AssaultRifle : public Weapon {
    private:
        uint32_t base_damage;
        uint32_t range;
        uint32_t magazine_size;
        int32_t rounds_left;
        int32_t burst_size;
        double distance_modifier;
        uint32_t ammo_used;
        
    public:
        AssaultRifle();
        virtual uint32_t getAmmoLeft() override;
        virtual bool inRange(uint32_t distance) override;
        virtual int32_t calculateDamage
            (const uint32_t &distance, const uint32_t &hitCount) override;
        virtual void reload() override;
        virtual bool emptyMagazine() override;
        virtual void useAmmo() override;
        virtual std::string getWeaponType() override;
        virtual uint32_t getAmountOfAmmoUsed() override;
        virtual ~AssaultRifle() {}
};
#endif