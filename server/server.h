#ifndef SERVER_SERVER_H
#define SERVER_SERVER_H

#include "server_protocol.h"
#include "client_accepter.h"
#include "game_loop.h"
#include "../common/queue.h"
#include "../common/thread.h"

/**
 * @class Server
 * 
 * Esta clase representa un servidor que acepta conexiones de clientes.
 */
class Server {
    private: 
    const char* port; /**< El puerto en el que el servidor escucha las conexiones de los clientes. */

    public:
    /**
     * @brief Constructor de la clase Server.
     * 
     * @param port El puerto en el que el servidor escucha las conexiones de los clientes.
     * 
     * Crea una nueva instancia de la clase Server con el puerto especificado.
     */
    explicit Server(const char* port);

    /**
     * @brief Inicia la ejecución del servidor.
     * 
     * Este método inicia la ejecución del servidor y ejecuta el hilo que se encarga de aceptar conexiones de clientes.
     * Mantiene el servidor en ejecución hasta que se introduce "q" desde la entrada estándar.
     * Al recibir "q", se detiene la aceptación de nuevas conexiones y se espera a que todos los
     * hilos de clientes finalicen antes de terminar la ejecución del servidor.
     */
    void run(); 
};

#endif
