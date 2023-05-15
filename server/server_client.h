#ifndef SERVER_CLIENT_H
#define SERVER_CLIENT_H
#include "../common/server_protocol.h"
#include "server_receiveThread.h"
class ServerClient {
    private: 
    ServerProtocol protocol;
    int id; //no se como inicializar numero random aún 
    ReceiveThread* receive_thread;

    ServerClient(Socket socket); 
};  
#endif