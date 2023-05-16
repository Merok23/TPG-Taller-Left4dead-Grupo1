#ifndef SERVER_CLIENT_H
#define SERVER_CLIENT_H
#include "../common/server_protocol.h"
#include "server_receiveThread.h"
#include "../common/action.h"

class ServerClient {
    private: 
    ServerProtocol protocol;
    //int id; //no se como inicializar numero random aún 
    ReceiveThread receive_thread;

    public:
    ServerClient(Socket socket, Queue<Action*>& game_queue); 
};  
#endif