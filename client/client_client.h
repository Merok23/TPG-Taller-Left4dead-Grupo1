#ifndef CLIENT_CLIENT_H
#define CLIENT_CLIENT_H

#include <list>
#include <string>
#include "send_thread.h"
#include "receive_thread.h"
#include "../common/queue.h"

class Client {
    private: 
    ClientProtocol protocol;
    Queue<std::string> queue_comandos; 
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
