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

#include "client_protocol.h"
#include "../common/socket.h"



class Client {
    private: 
    Socket socket;  
    ClientProtocol protocol;

    public: 
    /* Inicializa la clase Cliente, donde inicializa el protocolo y socket(y lo conecta). 
    Argumentos: el hostname y servname para conectar el socket.  */
    Client(const char* hostname, const char* servname); 
    void run();
};
#endif