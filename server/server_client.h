#ifndef SERVER_CLIENT_H
#define SERVER_CLIENT_H
#include "../common/server_protocol.h"
#include "server_receive_thread.h"
#include "../common/action.h"

class ServerClient {
    private: 
    ServerProtocol protocol;
    //int id; //no se como inicializar numero random aún 
    ReceiveThread receive_thread;
    //SendThread send_thread;
    
    public:
    ServerClient(Socket socket, Queue<std::shared_ptr<Action>>&  game_queue); 
};  
#endif