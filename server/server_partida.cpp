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
#include "server_partida.h"

Partida::Partida(Queue<Action*>* game_queue) : game_queue(game_queue) {
    return; 
}