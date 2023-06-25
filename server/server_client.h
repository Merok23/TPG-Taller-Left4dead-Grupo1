#ifndef SERVER_CLIENT_H
#define SERVER_CLIENT_H

#include <memory>

#include "server_protocol.h"
#include "receive_thread.h"
#include "send_thread.h"
#include "action.h"
#include "game_handler.h"
/**
 * @class ServerClient
 * 
 * Esta clase representa un cliente conectado al servidor.
 */
class ServerClient {
    private: 
    ServerProtocol protocol;  /**< El protocolo utilizado para comunicarse con el cliente. */
    Queue<std::shared_ptr<GameStateForClient>> client_queue;  /**< La cola de estados de juego para enviar al cliente. */
    ReceiveThread receive_thread;  /**< El hilo encargado de recibir mensajes del cliente. */
    SendThread send_thread;  /**< El hilo encargado de enviar mensajes al cliente. */
    
    public:
      /**
     * @brief Constructor de la clase ServerClient.
     * 
     * @param socket El socket de conexión de el cliente.
     * @param game_handler El controlador de juegos utilizado para administrar las interacciones con el cliente.
     * 
     * Crea una nueva instancia de la clase ServerClient utilizando el socket proporcionado y el controlador de juegos.
     * Inicializa el protocolo de comunicación, la cola de estados de juego y los hilos de recepción y envío de mensajes.
     */
    ServerClient(Socket socket, GameHandler& game_handler); 
    
    /**
     * @brief Verifica si el cliente ha finalizado su conexión.
     * 
     * @return true si el cliente ha finalizado su conexión, false en caso contrario.
     * 
     * Comprueba si tanto el hilo de recepción como el hilo de envío han finalizado su ejecución,
     * lo cual indica que el cliente ha terminado su conexión.
     */
    bool isFinished();

     /**
     * @brief Destructor de la clase ServerClient.
     * 
     * Cierra el socket de comunicación, finaliza los hilos de recepción y envío, y espera a que ambos hilos terminen su ejecución.
     */
    ~ServerClient();
};  
#endif
