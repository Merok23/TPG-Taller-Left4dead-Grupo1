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

#include "graphics.h"

#include <list>
#include <string>
#include "send_thread.h"
#include "receive_thread.h"
#include "../common/queue.h"

class Client {
    private: 
    ClientProtocol protocol;
    Graphics graphics;
    int game_id;
    bool connected; 
    Queue<command_t> queue_comandos; 
    Queue<GameState*> game_states;
    SendThread* send_thread;
    ReceiveThread* receive_thread;

    Client(const Client&) = delete;
    Client& operator=(const Client&) = delete;
    bool finished;


    public: 
    /* Inicializa la clase Cliente, donde inicializa el protocolo y socket(y lo conecta). 
    Argumentos: el hostname y servname para conectar el socket.  */
    Client(const char* hostname, const char* servname); 
    void run();
    ~Client();
};
#endif
