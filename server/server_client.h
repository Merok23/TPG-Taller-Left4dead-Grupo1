#ifndef SERVER_CLIENT_H
#define SERVER_CLIENT_H
#include "server_protocol.h"
#include "server_receive_thread.h"
#include "send_thread.h"
#include "action.h"
#include "game_handler.h"

class ServerClient {
    private: 
    ServerProtocol protocol;
    GameHandler& game_handler;  
    Queue<std::shared_ptr<GameStateForClient>> client_queue;
    ReceiveThread receive_thread;
    SendThread send_thread; 
    
    public:
    ServerClient(Socket socket, GameHandler& game_handler); 
    bool isFinished();
    ~ServerClient();
};  
#endif