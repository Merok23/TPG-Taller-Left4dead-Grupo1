#ifndef SERVER_GAME_HANDLER_H
#define SERVER_GAME_HANDLER_H

#include <map>
#include <mutex>
#include <string>
#include <memory>

#include "game_loop.h"
/**
 * @class GameHandler
 * 
 * Esta clase se encarga de manejar las salas de juego y la interacción entre los clientes y las salas de juego.
 */

class GameHandler {
    private: 
    std::map<uint32_t, GameLoop*> rooms; /**< Mapa de salas de juego. */
    uint32_t rooms_id; /**< Identificador para las salas de juego */
    std::mutex mutex; /**< Mutex para proteger el mapa de salas de juego. */

     /**
     * @brief Genera un ID único para una nueva sala de juego.
     * 
     * @return El ID único generado para la sala de juego.
     */
    uint32_t createRoomId();

    /**
     * @brief Cierra una sala de juego y realiza las operaciones necesarias para finalizarla.
     * 
     * @param room_id El ID de la sala de juego a cerrar.
     */
    void closeRoom(uint32_t room_id);

    public: 

     /**
     * @brief Constructor de la clase GameHandler.
     * 
     * Crea una nueva instancia de la clase GameHandler y establece el ID de la sala de juego en 0.
     */
    GameHandler();

     /**
     * @brief Crea una nueva sala de juego y asigna un ID a la sala creada.
     * 
     * @param room_name El nombre de la sala de juego.
     * @param client_queue La cola de estados de juego para enviar a los clientes.
     * @param client_id El ID del cliente que crea la sala.
     * @param game_mode El modo de juego de la sala.
     * @return El ID asignado a la sala de juego creada.
     */
    uint32_t createRoom(const std::string& room_name, 
        Queue<std::shared_ptr<GameStateForClient>>& client_queue, uint32_t& client_id, GameMode game_mode);

    /**
     * @brief Permite que un cliente se una a una sala de juego existente.
     * 
     * @param room_id El ID de la sala de juego a la que el cliente desea unirse.
     * @param client_queue La cola de estados de juego para enviar al cliente.
     * @param client_id El ID asignado al cliente que se une a la sala.
     * @param game_mode El modo de juego de la sala.
     * @return true si el cliente se unió exitosamente a la sala de juego, false en caso contrario.
     */
    bool joinRoom(uint32_t room_id, 
        Queue<std::shared_ptr<GameStateForClient>>& client_queue, uint32_t& client_id, GameMode& game_mode);
    
    /**
     * @brief Obtiene la cola de acciones de juego asociada a una sala de juego.
     * 
     * @param room_id El ID de la sala de juego.
     * @return La cola de acciones de juego asociada a la sala especificada.
     */
    Queue<std::shared_ptr<Action>>& getQueue(uint32_t room_id);

     /**
     * @brief Permite que un cliente abandone una sala de juego.
     * 
     * @param room_id El ID de la sala de juego a abandonar.
     * @param queue La cola de estados de juego del cliente que abandona la sala.
     */
    void leaveRoom(uint32_t room_id, Queue<std::shared_ptr<GameStateForClient>>&);

    /**
     * @brief Destructor de la clase GameHandler.
     * 
     * Libera la memoria y finaliza todas las salas de juego activas.
     */
    ~GameHandler();
};
#endif
