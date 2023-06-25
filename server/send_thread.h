#ifndef SERVER_SEND_THREAD_H
#define SERVER_SEND_THREAD_H
#include <atomic>   
#include <memory>

#include "../common/thread.h"   
#include "server_protocol.h"
#include "../common/queue.h"

/**
 * @class SendThread
 * 
 * Esta clase se encarga de enviar mensajes a un cliente.
 * Hereda de la clase Thread para ejecutarse en un hilo separado.
*/
class SendThread : public Thread {
    private:
        ServerProtocol& protocol;  /** < El protocolo utilizado para la comunicación con el cliente. */
        Queue<std::shared_ptr<GameStateForClient>>& client_queue;  /** < La cola de estados de juego para enviar al cliente. */
        std::atomic<bool> finished; /**< Flag que indica si el hilo ha finalizado su ejecución. */ 

    public:
        /**
         * @brief Constructor de la clase SendThread.
         * 
         * @param protocol Referencia al objeto ServerProtocol.
         * @param client_queue Cola de estados de juego para el cliente.
         */
        SendThread(ServerProtocol& protocol, 
            Queue<std::shared_ptr<GameStateForClient>>& client_queue);
        
        /**
        * @brief Método de ejecución del hilo.
        * 
        * Este método se encarga de enviar los estados de juego al cliente a través del protocolo de servidor.
        * Continúa ejecutándose hasta que se finaliza el hilo o el protocolo de servidor ha finalizado.
        */
        virtual void run() override; 
        
        /**
         * @brief Indica si el hilo ha finalizado.
         * 
         * @return true si el hilo ha finalizado, false en caso contrario.
         */
        bool isFinished();

         /**
         * @brief Detiene la ejecución del hilo.
         */
        void stop();

};
#endif
