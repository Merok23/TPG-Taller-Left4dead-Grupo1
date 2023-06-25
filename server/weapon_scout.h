#ifndef SERVER_WEAPON_SCOUT_H
#define SERVER_WEAPON_SCOUT_H

#include "weapon.h"
#include "config.h"
#include <string>
# pragma once


class Scout : public Weapon {
    private:
        uint32_t base_damage; /** < Daño base del arma. */
        uint32_t range; /** < Alcance del arma. */
        uint32_t magazine_size; /** < Tamaño del cargador del arma. */ 
        int32_t rounds_left; /** < Cantidad de balas restantes en el cargador. */
        double damage_falloff; /** < Reducción de daño por distancia. */
        uint32_t ammo_used; /** < Cantidad de balas utilizadas. */
        
    public:
        /**
         * @brief Constructor de la clase Scout.
         */
        Scout();
        virtual uint32_t getAmmoLeft() override;
        virtual bool inRange(uint32_t distance) override;
        virtual int32_t calculateDamage
            (const uint32_t &distance, const uint32_t &hitCount) override;
        virtual void reload() override;
        virtual bool emptyMagazine() override;
        virtual void useAmmo() override;
        virtual std::string getWeaponType() override;
        virtual uint32_t getAmountOfAmmoUsed() override;
        ~Scout() {};
};
#endif
