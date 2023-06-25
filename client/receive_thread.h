#ifndef CLIENT_RECIEVE_THREAD_H
#define CLIENT_RECIEVE_THREAD_H

#include <atomic>
#include <memory>
#include "../common/thread.h"
#include "client_protocol.h"
#include "../common/queue.h"

/**
 * @brief Clase se encarga de recibir estados del juego desde el servidor.
 * Hereda de la clase Thread para ejecutarse en un hilo separado.
 */
class ReceiveThread : public Thread {
    private:
        ClientProtocol& protocol; /** < Protocolo del cliente. */
        Queue<std::shared_ptr<GameState>>& game_states; /** < Cola de estados del juego. */
        std::atomic<bool> finished; /** < Indica si el hilo terminó. */

    public:
        /**
         * @brief Constructor de la clase `ReceiveThread`.
         *
         * @param protocol El protocolo del cliente.
         * @param queue La cola de estados de juego recibidos.
         */
        ReceiveThread(ClientProtocol& protocol, 
            Queue<std::shared_ptr<GameState>>& queue);

         /**
         * @brief Método principal del hilo de recepción.
         *        Recibe estados de juego desde el servidor hasta que se detenga el hilo.
         */
        virtual void run() override; 

        /**
         * @brief Verifica si el hilo de recepción ha finalizado.
         *
         * @return `true` si el hilo ha finalizado, `false` en caso contrario.
         */
        bool isFinished();

        /**
         * @brief Detiene el hilo de recepción.
         */
        void stop();
};
#endif
