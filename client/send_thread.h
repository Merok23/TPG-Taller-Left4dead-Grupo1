#ifndef CLIENT_SEND_THREAD_H
#define CLIENT_SEND_THREAD_H

#include <atomic>   
#include <string>

#include "../common/thread.h"   
#include "client_protocol.h"
#include "../common/queue.h"

/**
 * @brief Clase que se encarga de enviar comandos al servidor.
 * Extiende la clase Thread para ejecutarse en un hilo separado.
 */
class SendThread : public Thread {
    private:
        ClientProtocol& protocol; /** < Protocolo del cliente. */
        Queue<command_t>& queue_comandos;/** < Cola de comandos a enviar. */
        std::atomic<bool> finished; /** < Indica si el hilo terminó. */

    public:
        /**
         * @brief Constructor de la clase `SendThread`.
         *
         * @param protocol El protocolo del cliente.
         * @param queue La cola de comandos a enviar al servidor.
         */
        SendThread(ClientProtocol& protocol, Queue<command_t>& queue_comandos);

        /**
         * @brief Método principal del hilo de envío.
         *        Envia comandos desde la cola de comandos hasta que se detenga el hilo.
         */
        virtual void run() override; 

        /**
         * @brief Detiene el hilo de envío.
         */
        void stop();

};

#endif
