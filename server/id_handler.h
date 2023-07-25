#ifndef SERVER_ID_HANDLER_H
#define SERVER_ID_HANDLER_H

#include <map>
#include <cstdint>
#include <mutex>
#include "game.h"
#pragma once

/**
 * @class IdHandler
 * 
 * Esta clase maneja los IDs de los jugadores en el juego y proporciona funciones para interactuar con ellos.
 */
class IdHandler {
    private:
        Game& game; /**< Referencia al objeto Game para realizar las operaciones del juego. */
        std::map<uint32_t, uint32_t> my_ids; /**< Mapa que mantiene los IDs de los jugadores asociados a los IDs de los clientes. */
        std::mutex mutex; /**< Mutex utilizado para garantizar la exclusión mutua en el acceso a los IDs de los jugadores. */

    public:
        /**
         * @brief Constructor de la clase IdHandler.
         * 
         * @param game Referencia al objeto Game.
         */
        explicit IdHandler(Game &game);

        /**
         * @brief Crea un nuevo jugador y lo asocia con un cliente específico.
         * 
         * @param client_id El ID del cliente.
         * @param weapon El arma del jugador.
         */
        void createPlayer(uint32_t client_id, Weapon* weapon, std::string player_name);

         /**
         * @brief Establece la dirección de movimiento de un jugador.
         * 
         * @param client_id El ID del cliente.
         * @param x La dirección x.
         * @param y La dirección y.
         */
        void setMoving(uint32_t client_id, int32_t x, int32_t y);

        /**
         * @brief Activa o desactiva el disparo de un jugador.
         * 
         * @param client_id El ID del cliente.
         * @param isShooting true para activar el disparo, false para desactivarlo.
         */
        void shoot(uint32_t client_id, bool isShooting);

        /**
         * @brief Activa o desactiva la recarga de un jugador.
         * 
         * @param client_id El ID del cliente.
         * @param isReloading true para activar la recarga, false para desactivarla.
         */
        void reload(uint32_t client_id, bool isReloading);

        /**
         * @brief Activa un cheat a un jugador.
         * 
         * @param client_id El ID del cliente.
         * @param cheatType El tipo de cheat.
         */
        void setCheat(uint32_t client_id, Cheat cheatType);

        /**
         * @brief Obtiene la cantidad de munición utilizada por un jugador.
         * 
         * @param client_id El ID del cliente.
         * @return La cantidad de munición utilizada por el jugador.
         */
        uint32_t getAmmountOfAmmoUsed(uint32_t client_id);

         /**
         * @brief Obtiene la cantidad de infectados eliminados por un jugador.
         * 
         * @param client_id El ID del cliente.
         * @return La cantidad de infectados eliminados por el jugador.
         */
        uint32_t getAmmountOfInfectedKilled(uint32_t client_id);

        /**
         * @brief Obtiene el tiempo de muerte de un jugador.
         * 
         * @param client_id El ID del cliente.
         * @return El tiempo de muerte del jugador.
         */
        uint32_t getTimeOfDeath(uint32_t client_id);

};
#endif
