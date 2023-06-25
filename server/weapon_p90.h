#ifndef SERVER_WEAPON_P90_H
#define SERVER_WEAPON_P90_H

#include "weapon.h"
#include "config.h"
#include <string>
# pragma once


class AssaultRifle : public Weapon {
    private:
        uint32_t base_damage; /** < Daño base del arma. */
        uint32_t range; /** < Rango del arma. */
        uint32_t magazine_size; /** < Tamaño del cargador. */
        int32_t rounds_left; /** < Balas restantes en el cargador. */
        int32_t burst_size; /** < Tamaño de la ráfaga. */
        double distance_modifier; /** < Modificador de distancia. */
        uint32_t ammo_used; /** < Balas usadas. */
        
    public:
        /**
         * @brief Constructor de la clase AssaultRifle.
         */
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
        ~AssaultRifle() {};
};
#endif