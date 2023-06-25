#include <cstdint>
#include <string>
# pragma once

/**
 * @class Weapon
 * 
 * Esta clase representa un arma genérica en el juego.
 */
class Weapon {        
    public:
        /**
         * @brief Verifica si un objetivo está dentro del alcance del arma.
         * 
         * @param distance Distancia al objetivo.
         * 
         * @return true si el objetivo está dentro del alcance, false en caso contrario.
         */
        virtual bool inRange(uint32_t distance) = 0;

         /**
         * @brief Obtiene la cantidad de munición restante en el cargador del arma.
         * 
         * @return La cantidad de munición restante en el cargador.
         */
        virtual uint32_t getAmmoLeft() = 0;

        /**
         * @brief Calcula el daño causado por el arma.
         * 
         * @param distance Distancia al objetivo.
         * 
         * @param hitCount Cantidad de impactos previos en el objetivo.
         * 
         * @return El daño causado por el arma.
         */
        virtual int32_t calculateDamage(const uint32_t &distance, const uint32_t &hitCount) = 0;

        /**
         * @brief Recarga el arma.
         */
        virtual void reload() = 0;

        /**
         * @brief Verifica si el cargador del arma está vacío.
         * 
         * @return true si el cargador está vacío, false en caso contrario.
         */
        virtual bool emptyMagazine() = 0;

        /**
         * @brief Utiliza munición del cargador del arma.
         */
        virtual void useAmmo() = 0;

        /**
         * @brief Obtiene el tipo de arma.
         * 
         * @return El tipo de arma.
         */
        virtual std::string getWeaponType() = 0;

        /**
         * @brief Obtiene la cantidad de munición utilizada por el arma.
         * 
         * @return La cantidad de munición utilizada por el arma.
         */
        virtual uint32_t getAmountOfAmmoUsed() = 0;

        /**
         * @brief Destructor de la clase Weapon.
         */
        virtual ~Weapon() {};
};
