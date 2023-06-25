#ifndef GAME_LOOP_H
#define GAME_LOOP_H
#include <atomic>   
#include <map>
#include <memory>
#include <chrono>

#include "../common/queue.h"
#include "action.h"
#include "../common/thread.h"  
#include "entity_player.h"
#include "id_handler.h" 


/**
 * @class GameLoop
 * 
 * Esta clase representa el bucle principal del juego y controla la lógica del juego en cada iteración.
 * Hereda de la clase Thread para ejecutarse en un hilo separado.
 */

class GameLoop : public Thread {
    private:
    Queue<std::shared_ptr<Action>> game_queue; /**< Cola de acciones del juego. */
    GameMode game_mode;  /**< Modo de juego actual. */
    Game game; /**< Objeto del juego. */
    IdHandler id_handler; /**< Manejador de IDs de jugadores. */
    std::map<uint32_t, Queue<std::shared_ptr<GameStateForClient>>*> player_queues; /**< Mapa de colas de estado del juego de los clientes. */
    std::atomic<bool> finished;  /**< Flag que indica si el bucle del juego ha terminado. */
    std::atomic<int> client_id; /**< Identificador único del cliente. */
    std::chrono::high_resolution_clock::time_point start_loop_time; /**< Punto de inicio del tiempo del bucle. */
    uint32_t total_loop_time;    /**< Tiempo total de ejecución del bucle del juego. */
    std::mutex mutex;  /**< Mutex para garantizar la sincronización. */

    private:
    /**
     * @brief Establece las estadísticas del juego en el modo "Clear the Zone".
     * 
     * @param game_state Estado del juego para el cliente.
     */
    void setStadisticsCTZ(std::shared_ptr<GameStateForClient>& game_state);

     /**
     * @brief Establece las estadísticas del juego en el modo de supervivencia.
     * 
     * @param game_state Estado del juego para el cliente.
     */
    void setStadisticsSurvival(std::shared_ptr<GameStateForClient>& game_state);

     /**
     * @brief Ordena el ranking de las estadísticas en orden descendente.
     * 
     * @param stadistic Estadísticas del juego.
     */
    void sortRankingStadistic(std::vector<std::pair<uint32_t, uint32_t>>& stadistic);

     /**
     * @brief Obtiene la posición de un jugador en el ranking de estadísticas.
     * 
     * @param stadistic Estadísticas del juego.
     * @param id        ID del jugador.
     * @return uint8_t  Posición del jugador en el ranking.
     */
    uint8_t getRanking(std::vector<std::pair<uint32_t, uint32_t>>& stadistic, uint32_t id);


    public:
    /**
     * @brief Constructor de la clase GameLoop.
     * 
     * @param gameMode Modo de juego para inicializar la instancia de GameLoop.
     */
    explicit GameLoop(GameMode gameMode);

    /**
     * @brief Obtiene la cola de acciones del juego.
     * 
     * @return Referencia a la cola de acciones del juego.
     */
    Queue<std::shared_ptr<Action>>& getQueue();

    /**
     * @brief Agrega una cola de estado del juego de un cliente.
     * 
     * @param queue Cola de estado del juego para ser agregada.
     * @return Identificador asignado a la cola del cliente.
     */
    int addClientQueue(Queue<std::shared_ptr<GameStateForClient>>& queue);

    /**
     * @brief Elimina la cola de estado del juego de un cliente.
     * 
     * @param queue Cola de estado del juego a ser eliminada.
     */
    void deleteClientQueue(Queue<std::shared_ptr<GameStateForClient>>& queue);

    /**
     * @brief Verifica si no hay jugadores en la sala.
     * 
     * @return true si no hay jugadores en la sala, false de lo contrario.
     */
    bool isRoomEmpty();

    /**
     * @brief Obtiene el modo de juego actual.
     * 
     * @return Modo de juego actual.
     */
    GameMode getGameMode();

    /**
     * @brief Establece las estadísticas del juego en el estado de juego para los clientes.
     * 
     * @param game_state Estado de juego actual.
     */
    void setGameStadistics(std::shared_ptr<GameStateForClient>& game_state);

    /**
     * @brief Obtiene el tiempo total de ejecución del bucle del juego.
     * 
     * @return Tiempo total de ejecución del bucle del juego.
     */
    int getTotalTimeOfGameLoop();

    /**
     * @brief Finaliza el tiempo de ejecución del bucle del juego y registra el tiempo total.
     */
    void endGameLoopTime();

    /**
     * @brief Ejecuta el bucle del juego.
     * 
     * Realiza las actualizaciones del juego y notifica a los clientes sobre el estado del juego.
     * Sobrescribe el método `run` de la clase Thread.
     */
    virtual void run() override;

     /**
     * @brief Verifica si el bucle del juego ha terminado.
     * 
     * @return true si el bucle del juego ha terminado, false de lo contrario.
     */
    bool isFinished();

    /**
     * @brief Detiene el bucle del juego y registra el tiempo de finalización.
     */
    void stop();

     /**
     * @brief Destructor de la clase GameLoop.
     * 
     * Cierra la cola de acciones del juego.
     */
    ~GameLoop();
}; 
#endif
