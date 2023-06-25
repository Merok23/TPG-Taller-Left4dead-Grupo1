#include <cstdint>
#include <map>
#include "entity.h"

typedef struct Statistics {
    bool ranking; 
    std::pair<uint8_t, uint32_t> infected_killed_info;
    std::pair<uint8_t, uint32_t> ammo_used_info;
    std::pair<uint8_t, uint32_t> game_time_info;
    std::list<uint32_t> infected_kills_top_10;
    std::list<uint32_t> ammo_used_top_10;
    std::list<uint32_t> time_alive_top_10;
    
    Statistics() {
        this->ranking = false;
        this->infected_killed_info = std::make_pair(0, 0);
        this->ammo_used_info = std::make_pair(0, 0);
        this->game_time_info = std::make_pair(0, 0);
        this->infected_kills_top_10 = std::list<uint32_t>(10, 0);
        this->ammo_used_top_10 = std::list<uint32_t>(10, 0);
        this->time_alive_top_10 = std::list<uint32_t>(10, 0);
    }
    void setStatisticsCTZ(bool ranking, std::pair<uint8_t, uint32_t> infected_killed_info, 
        std::pair<uint8_t, uint32_t> ammo_used_info, 
        std::pair<uint8_t, uint32_t> game_time_info) {
        this->ranking = ranking;
        this->infected_killed_info = infected_killed_info;
        this->ammo_used_info = ammo_used_info;
        this->game_time_info = game_time_info;
        this->infected_kills_top_10 = std::list<uint32_t>(10, 0);
        this->ammo_used_top_10 = std::list<uint32_t>(10, 0);
        this->time_alive_top_10 = std::list<uint32_t>(10, 0);
    }
    void setStatisticsSurvival(bool ranking, std::pair<uint8_t, uint32_t> infected_killed_info, 
        std::pair<uint8_t, uint32_t> ammo_used_info, 
        std::pair<uint8_t, uint32_t> game_time_info, 
        const std::list<uint32_t> &infected_kills_top_10,
        const std::list<uint32_t> &ammo_used_top_10,
        const std::list<uint32_t> &time_alive_top_10) {
        this->ranking = ranking;
        this->infected_killed_info = infected_killed_info;
        this->ammo_used_info = ammo_used_info;
        this->game_time_info = game_time_info;
        this->infected_kills_top_10 = infected_kills_top_10;
        this->ammo_used_top_10 = ammo_used_top_10;
        this->time_alive_top_10 = time_alive_top_10;
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

    std::list<uint32_t> getInfectedKillsTop10() {
        return this->infected_kills_top_10;
    }

    std::list<uint32_t> getAmmoUsedTop10() {
        return this->ammo_used_top_10;
    }

    std::list<uint32_t> getTimeAliveTop10() {
        return this->time_alive_top_10;
    }
    
    bool getRanking() {
        return this->ranking;
    }    

} Statistics;


/**
 * @class GameStateForClient
 * 
 * Esta clase representa el estado del juego para el cliente.
*/
class GameStateForClient {
    private:
        std::map<uint32_t, Entity*> entities; /** < Mapa de entidades del juego. */
        bool game_over; /** < Flag que indica si el juego terminó. */
        bool players_won; /** < Flag que indica si los jugadores ganaron. */
        Statistics statistics; /** < Estadísticas del juego. */

    public:

        /**
         * @brief Constructor de la clase.
         * 
         * @param entities Mapa de entidades del juego.
         * @param game_over Flag que indica si el juego terminó.
         * @param players_won Flag que indica si los jugadores ganaron.
        */
        GameStateForClient(const std::map<uint32_t, Entity*> &entities, 
            bool game_over, 
            bool players_won);

        /**
         * @brief Obtiene las entidades del juego.
         * 
         * @return std::map<uint32_t, Entity*>& Mapa de entidades del juego.
        */

        std::map<uint32_t, Entity*>& getEntities();
   
        /**
         * @brief Actualiza las estadísticas del juego, en el modo "Clear the Zone".
         * 
         * @param ranking Flag que indica si se debe las estadísticas tienen ranking.
         * 
         * @param infected_killed_info Cantidad de infectados muertos, y el ranking.
         * 
         * @param ammo_used_info Cantidad de municiones usadas, y el ranking.
         * 
         * @param game_time_info Tiempo de ejecución del juego, y el ranking.
         *
        */
        void setStadisticsCTZ(bool ranking, std::pair<uint8_t, uint32_t> infected_killed_info, 
            std::pair<uint8_t, uint32_t> ammo_used_info, 
            std::pair<uint8_t, uint32_t> game_time_info);

        /**
         * @brief Actualiza las estadísticas del juego, en el modo de supervivencia.
         * 
         * @param ranking Flag que indica si se debe las estadísticas tienen ranking.
         * 
         * @param infected_killed_info Cantidad de infectados muertos, y el ranking.
         * 
         * @param ammo_used_info Cantidad de municiones usadas, y el ranking.
         * 
         * @param game_time_info Tiempo de ejecución del juego, y el ranking.
         * 
         * @param infected_kills_top_10 Lista de los 10 mejores puntajes de infectados matados.
         * 
         * @param ammo_used_top_10 Lista de los 10 mejores puntajes de municiones usadas.
         * 
         * @param time_alive_top_10 Lista de los 10 mejores puntajes de tiempo de vida.
         * 
        */
        void setStatisticsSurvival(bool ranking, std::pair<uint8_t, uint32_t> infected_killed_info, 
            std::pair<uint8_t, uint32_t> ammo_used_info, 
            std::pair<uint8_t, uint32_t> game_time_info, 
            std::list<uint32_t> infected_kills_top_10,
            std::list<uint32_t> ammo_used_top_10,
            std::list<uint32_t> time_alive_top_10);

        /**
         * @brief Obtiene las estadísticas del juego.
         * 
         * @return Statistics& Estadísticas del juego.
        */
        Statistics& getStatistics();

        /**
         * @brief Verifica si el juego terminó.
         * 
         * @return bool& Flag que indica si el juego terminó.
        */
        bool& isGameOver();

        /**
         * @brief Verifica si los jugadores ganaron.
         * 
         * @return bool& Flag que indica si los jugadores ganaron.
        */
        bool& didPlayersWin();
};
