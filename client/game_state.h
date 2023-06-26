#ifndef CLIENT_GAME_STATE_H
#define CLIENT_GAME_STATE_H
#include "entity.h"
#include <memory>
#include <map>
#include <list>
typedef struct Statistics {
    //if game mode == survival, then ranking = true, because is the only game mode where stadistics have ranking
    bool ranking;
    //save as <ranking, value> if game mode != survival, then ranking =  0
    std::pair<uint8_t, uint32_t> infected_killed_info;
    std::pair<uint8_t, uint32_t> ammo_used_info;
    std::pair<uint8_t, uint32_t> game_time_info;
    std::list<uint32_t> infected_kills_top;
    std::list<uint32_t> ammo_used_top;
    std::list<uint32_t> time_alive_top;
    
    Statistics() {
        this->ranking = false;
        this->infected_killed_info = std::make_pair(0, 0);
        this->ammo_used_info = std::make_pair(0, 0);
        this->game_time_info = std::make_pair(0, 0);
        this->infected_kills_top = std::list<uint32_t>(10, 0);
        this->ammo_used_top = std::list<uint32_t>(10, 0);
        this->time_alive_top = std::list<uint32_t>(10, 0);
    }

    void setStatisticsCTZ(bool ranking, std::pair<uint8_t, uint32_t> infected_killed_info, 
        std::pair<uint8_t, uint32_t> ammo_used_info, 
        std::pair<uint8_t, uint32_t> game_time_info) {
        this->ranking = ranking;
        this->infected_killed_info = infected_killed_info;
        this->ammo_used_info = ammo_used_info;
        this->game_time_info = game_time_info;
    }

    void setStatisticsSurvival(bool ranking, std::pair<uint8_t, uint32_t> infected_killed_info, 
        std::pair<uint8_t, uint32_t> ammo_used_info, 
        std::pair<uint8_t, uint32_t> game_time_info, 
        std::list<uint32_t> infected_kills_top,
        std::list<uint32_t> ammo_used_top,
        std::list<uint32_t> time_alive_top) {
        this->ranking = ranking;
        this->infected_killed_info = infected_killed_info;
        this->ammo_used_info = ammo_used_info;
        this->game_time_info = game_time_info;
        this->infected_kills_top = infected_kills_top;
        this->ammo_used_top = ammo_used_top;
        this->time_alive_top = time_alive_top;
    }

    std::pair<uint8_t, uint32_t> getInfectedKilledInfo() {
        return this->infected_killed_info;
    }

    std::pair<uint8_t, uint32_t> getAmmoUsedInfo() {
        return this->ammo_used_info;
    }   

    std::pair<uint8_t, uint32_t> getGameTimeInfo() {
        return this->game_time_info;
    }

    bool getRanking() {
        return this->ranking;
    }    

} Statistics;


/**
 * @brief Clase que representa el estado del juego.
 */
class GameState {
    public:
    std::map<uint32_t, Entity*> entities; /**< Mapa de entidades del juego. */
    bool game_over; /**< Indica si el juego terminó. */
    bool players_won; /**< Indica si los jugadores ganaron. */
    bool lost_connection; /**< Indica si se perdió la conexión con el servidor. */
    Statistics statistics; /**< Estadísticas del juego. */
    
    /**
     * @brief Constructor por defecto de la clase `GameState`.
     *        Crea un estado de juego vacío con la conexión perdida.
     */
    GameState();

    /**
     * @brief Constructor de la clase `GameState`.
     *
     * @param entities El mapa de entidades en el juego.
     * @param game_over Indicador de fin del juego.
     * @param players_won Indicador de victoria de los jugadores.
     */
    explicit GameState(const std::map<u_int32_t, Entity*>& entities, 
        bool game_over, 
        bool players_won);

     /**
     * @brief Constructor de la clase `GameState`.
     *
     * @param entities El mapa de entidades en el juego.
     * @param game_over Indicador de fin del juego.
     * @param players_won Indicador de victoria de los jugadores.
     * @param statistics Las estadísticas del juego.
     */
    explicit GameState(const std::map<u_int32_t, Entity*>& entities, 
        bool game_over, 
        bool players_won, 
        Statistics stadistics);
    
    /**
     * @brief Establece la conexión perdida.
     */
    void setLostConnection();

    /**
     * @brief Destructor de la clase `GameState`.
     *        Libera la memoria de las entidades en el estado de juego.
     */
    ~GameState();
}; 
#endif
