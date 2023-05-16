#ifndef SERVER_PARTIDA_H
#define SERVER_PARTIDA_H
#include "../common/queue.h"
#include "../common/action.h"

class Partida {
    private:
    Queue<Action*>* game_queue;

    public:
    Partida(Queue<Action*>* game_queue);
}; 
#endif