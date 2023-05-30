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

#include "../common/client_protocol.h"
#include "../common/socket.h"

#include "graphics.h"


class Client {
    private: 
    Socket socket;  
    ClientProtocol protocol;
    Graphics graphics;
    int game_id;
    bool connected; 

    public: 
    /* Inicializa la clase Cliente, donde inicializa el protocolo y socket(y lo conecta). 
    Argumentos: el hostname y servname para conectar el socket.  */
    Client(const char* hostname, const char* servname); 
    void run();
};
#endif