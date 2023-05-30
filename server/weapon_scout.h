#ifndef SERVER_WEAPON_SCOUT_H
#define SERVER_WEAPON_SCOUT_H

#include "weapon.h"
#include "config.h"
#include <string>
# pragma once


class Scout : public Weapon {
    private:
        uint32_t base_damage;
        uint32_t range;
        uint32_t magazine_size;
        int32_t rounds_left;
        double damage_falloff;
        
    public:
        Scout();
        virtual uint32_t getAmmoLeft() override;
        virtual bool inRange(uint32_t distance) override;
        virtual int32_t calculateDamage
            (const uint32_t &distance, const uint32_t &hitCount) override;
        virtual void reload() override;
        virtual bool emptyMagazine() override;
        virtual void useAmmo() override;
        virtual std::string getWeaponType() override;
        virtual ~Scout() {}
};
#endif