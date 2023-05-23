#ifndef SERVER_CLIENT_H
#define SERVER_CLIENT_H
#include "server_protocol.h"
#include "server_receive_thread.h"
#include "send_thread.h"
#include "action.h"
#include "game_loop.h"

class ServerClient {
    private: 
    ServerProtocol protocol;
    GameLoop& game_loop;    
    Queue<std::shared_ptr<GameStateForClient>> client_queue;
    int id; //no se como inicializar numero random aún 
    ReceiveThread receive_thread;
    SendThread send_thread; 
    
    public:
    ServerClient(Socket socket, Queue<Action*>&  game_queue, GameLoop& game_loop); 
    bool isFinished();
    ~ServerClient();
};  
#endif