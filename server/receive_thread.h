#ifndef SERVER_RECIEVE_THREAD_H
#define SERVER_RECIEVE_THREAD_H

#include <atomic>
#include <memory>

#include "../common/thread.h"
#include "server_protocol.h"
#include "../common/queue.h"
#include "../server/game.h"
#include "../server/game_handler.h"

/**
 * @class ReceiveThread
 * 
 * Esta clase se encarga de la recepción de mensajes del cliente, y gestionar los comandos y acciones.
 * Hereda de la clase Thread para ejecutarse en un hilo separado.
 */
class ReceiveThread : public Thread {
    private:
        ServerProtocol& protocol; /**< El protocolo utilizado para la comunicación con el cliente. */
        GameHandler& game_handler; /**< El controlador de juegos utilizado para administrar las interacciones con el cliente. */
        Queue<std::shared_ptr<GameStateForClient>>& client_queue; /**< La cola de estados de juego para enviar al cliente. */
        std::atomic<bool> finished; /**< Flag que indica si el hilo ha finalizado su ejecución. */
        uint32_t client_id; /**< El ID del cliente. */
        uint32_t room_id; /**< El ID de la sala de juego. */
        bool game_started; /**< Indicador de si el juego ha comenzado o no. */

    public:
        /**
         * @brief Constructor de la clase ReceiveThread.
         * 
         * @param protocol El protocolo de comunicación con el cliente.
         * @param game_handler El controlador de juegos.
         * @param client_queue La cola de estados de juego para enviar al cliente.
         * 
         * Crea una nueva instancia de la clase ReceiveThread con el protocolo de comunicación,
         * el controlador de juegos y la cola de estados de juego especificados.
         * Inicializa las variables y flags necesarios.
         */
        ReceiveThread(ServerProtocol& protocol, 
            GameHandler& game_handler, 
                Queue<std::shared_ptr<GameStateForClient>>& client_queue);
        
        /**
         * @brief Método de ejecución del hilo.
         * 
         * Este método se ejecuta al iniciar el hilo y llama a los métodos receiveCommand() y receiveGameActions() para recibir los mensajes del cliente.
         */
        virtual void run() override;

         /**
         * @brief Recibe los comandos del cliente.
         * 
         * Este método se ejecuta en un bucle hasta que el hilo se detenga o hasta que se inicie el juego.
         * Recibe los comandos (crear sala o unirse a una sasla) del cliente a través del protocolo de comunicación 
         * y realiza las acciones correspondientes.
         */
        void receiveCommand();

         /**
         * @brief Recibe las acciones de juego del cliente.
         * 
         * Este método se ejecuta en un bucle hasta que el hilo se detenga.
         * Recibe las acciones de juego del cliente a través del protocolo de comunicación y las envía a la cola de juego correspondiente.
         */
        void receiveGameActions();

        /**
         * @brief Verifica si el hilo ha finalizado su ejecución.
         * 
         * @return true si el hilo ha finalizado, false en caso contrario.
         * 
         * Comprueba el estado del flag "finished" para determinar si el hilo ha finalizado su ejecución.
         */
        bool isFinished();

         /**
         * @brief Detiene la ejecución del hilo.
         * 
         * Marca el flag "finished" como verdadero y realiza las operaciones necesarias para finalizar la ejecución del hilo.
         */
        void stop();
};
#endif
