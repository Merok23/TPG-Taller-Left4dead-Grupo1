#ifndef CLIENT_ACCEPTER_H
#define CLIENT_ACCEPTER_H

#include "../common/socket.h"
#include "../common/thread.h"
#include "game.h"
#include "action.h"
#include "game_handler.h"
#include "server_client.h"
#include <atomic>
#include <vector>
#include <list>

/**
 * @class ClientAccepter
 * 
 * Esta clase se encarga de aceptar conexiones de clientes en el servidor.
 * Hereda de la clase Thread para ejecutarse en un hilo separado.
 */
class ClientAccepter : public Thread {
    private:
        Socket recieving_socket; /**< El socket de recepción utilizado para aceptar conexiones de clientes. */
        GameHandler game_handler;  /**< El controlador de juegos utilizado para administrar las interacciones con los clientes. */
        std::list<ServerClient*> clients;  /**< Lista de clientes conectados al servidor. */
        std::atomic<bool> finished; /**< Flag que indica si se ha detenido la aceptación de nuevos clientes. */

    public:
        /**
         * @brief Constructor de la clase ClientAccepter.
         * 
         * @param port El puerto en el que se aceptarán las conexiones de los clientes.
         * 
         * Crea una nueva instancia de la clase ClientAccepter con el puerto especificado.
         * Inicializa el socket de recepción y el controlador de juegos.
         */
        explicit ClientAccepter(const char* port);

        /**
         * @brief Método de ejecución del hilo.
         * 
         * Este método se llama cuando se inicia el hilo y se encarga de iniciar la aceptación de clientes.
         */
        virtual void run() override;

        /**
         * @brief Acepta un cliente y lo agrega a la lista de clientes conectados.
         * 
         * Este método espera a que un cliente se conecte al servidor y lo agrega a la lista de clientes conectados.
         * Si se produce algún error durante la aceptación, se maneja adecuadamente.
         */
        void acceptClient();

         /**
         * @brief Elimina los clientes que han finalizado su conexión.
         * 
         * Este método recorre la lista de clientes conectados y elimina aquellos que han finalizado su conexión.
         */
        void removeDeadClients();

        /**
         * @brief Detiene la aceptación de nuevos clientes.
         * 
         * Este método marca el flag "finished" como verdadero, lo que indica que se debe detener la aceptación de nuevos clientes.
         */
        void stop();

        /**
         * @brief Destructor de la clase ClientAccepter.
         * 
         * Libera la memoria ocupada por los clientes conectados y cierra el socket de recepción.
         */
        ~ClientAccepter();
};
#endif

