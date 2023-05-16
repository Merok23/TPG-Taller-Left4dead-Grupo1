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
#include "server_client.h"  

ServerClient::ServerClient(Socket socket, Queue<Action*>* queue_game) : protocol(std::move(socket)) {
    receive_thread = new ReceiveThread(protocol, queue_game);
    return; 
}