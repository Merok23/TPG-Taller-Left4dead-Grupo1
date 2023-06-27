#ifndef STATISTICS_HANDLER_H
#define STATISTICS_HANDLER_H

#include <mutex>
#include <fstream>
#include <list>
#include <algorithm>
#include <iostream>
#include "config.h"
/**
 * @class StatisticsHandler
 * 
 * Esta clase representa el manejador de las estadísticas del juego.
 * 
*/
class StatisticsHandler {
    private: 
    std::list<uint32_t> top_infected_kills; /** < Lista de los 10 mejores puntajes de infectados matados. */
    std::list<uint32_t> top_ammo_used; /** < Lista de los 10 mejores puntajes de municiones usadas. */
    std::list<uint32_t> top_time_alive; /** < Lista de los 10 mejores puntajes de tiempo de vida. */
    uint8_t ranking_size; /** < Tamaño del ranking. */
    bool was_updated; /** < Flag que indica si las estadísticas fueron actualizadas. */
    std::mutex mutex; /** < Mutex para garantizar la sincronización. */

    /**
     * @brief Actualiza la lista de estadísticas.
     * 
     * @param list Lista de estadísticas.
     * @param value Valor de la estadística.
     * 
    */

    void updateList(std::list<uint32_t>& list, uint32_t& value);
    public:

    /**
     * @brief Constructor de la clase.
     * 
     * Lee las estadísticas del archivo statistics.txt. 
    */
    StatisticsHandler();

    /**
     * @brief Actualiza las estadísticas.
     * 
     * @param infected_kills Cantidad de infectados matados.
     * @param ammo_used Cantidad de municiones usadas.
     * @param time_alive Tiempo de vida.
     * 
    */
    void updateStatistics(uint32_t& infected_kills, uint32_t& ammo_used, uint32_t& time_alive);

    /**
     * @brief Obtiene los 10 mejores puntajes de infectados matados.
     * 
     * @return Lista de los 10 mejores puntajes de infectados matados.
     * 
    */
    std::list<uint32_t> getTopInfectedKills();

    /**
     * @brief Obtiene los 10 mejores puntajes de municiones usadas.
     * 
     * @return Lista de los 10 mejores puntajes de municiones usadas.
     * 
    */
    std::list<uint32_t> getTopAmmoUsed();

    /**
     * @brief Obtiene los 10 mejores puntajes de tiempo de vida.
     * 
     * @return Lista de los 10 mejores puntajes de tiempo de vida.
     * 
    */
    std::list<uint32_t> getTopTimeAlive();

    /**
     * @brief Guarda las estadísticas en el archivo statistics.txt.
     * 
    */
    void saveAllStatistics();

    /**
     * @brief Destructor de la clase.
     * 
    */
    ~StatisticsHandler();
};


extern StatisticsHandler statistics_handler;

#endif
