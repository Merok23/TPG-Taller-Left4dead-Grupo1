#include <cstdint>
#include <string>
# pragma once

class Weapon {        
    public:
        virtual bool inRange(uint32_t distance) = 0;
        virtual uint32_t getAmmoLeft() = 0;
        virtual int32_t calculateDamage(const uint32_t &distance, const uint32_t &hitCount) = 0;
        virtual void reload() = 0;
        virtual bool emptyMagazine() = 0;
        virtual void useAmmo() = 0;
        virtual std::string getWeaponType() = 0;
        virtual ~Weapon() {}
};
