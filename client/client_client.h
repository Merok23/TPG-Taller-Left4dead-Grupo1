#ifndef CLIENT_CLIENT_H
#define CLIENT_CLIENT_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <sstream>
#include <sys/types.h>
#include <netinet/in.h>
#include <iostream>
#include <fstream>
#include <thread>

#include "../client/client_protocol.h"
#include "../common/socket.h"
#include "graphics_qt.h"
#include "graphics_qt_ending.h"

#include "graphics.h"

#include <list>
#include <string>
#include "send_thread.h"
#include "receive_thread.h"
#include "../common/queue.h"

class Client {
    private: 
    ClientProtocol protocol; /** < Protocolo del cliente. */
    Graphics graphics; /** < Gráficos del cliente. */
    GraphicsQt graphics_qt; /** < Gráficos del cliente. */
    Queue<command_t> queue_comandos; /** < Cola de comandos. */
    Queue<std::shared_ptr<GameState>> game_states; /** < Cola de estados del juego. */
    SendThread* send_thread; /** < Hilo de envío de comandos. */
    ReceiveThread* receive_thread; /** < Hilo de recepción de estados del juego. */

    Client(const Client&) = delete;
    Client& operator=(const Client&) = delete;
    bool match_started;


    public: 
    /**
    *    @brief Constructor de la clase Client.
    * 
    *    @param hostname El nombre de host del servidor al que se desea conectar.
    * 
    *    @param servname El nombre de servicio o número de puerto del servidor al que se desea conectar.
    * 
    *    Inicializa una nueva instancia de la clase Client con el nombre de host y el nombre de servicio especificados.
    *    Crea los hilos necesarios e inicializa las variables miembro.
    */
    Client(const char* hostname, const char* servname); 

   /**
    * @brief Ejecuta el cliente.
    * 
    * Este método ejecuta la lógica principal del cliente. Maneja el flujo del juego, incluyendo
    * la conexión al servidor, el envío de comandos, la recepción de actualizaciones del juego y la visualización de los gráficos.
    * También gestiona los hilos para enviar y recibir datos.
    */
    void run();

    /**
     * @brief Destructor de la clase.
    */
    ~Client();
};
#endif
