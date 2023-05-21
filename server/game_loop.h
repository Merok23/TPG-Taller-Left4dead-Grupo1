#ifndef GAME_LOOP_H
#define GAME_LOOP_H
#include "../common/queue.h"
#include "action.h"
#include "../common/thread.h"  
#include "player.h" 
#include <atomic>   

class GameLoop : public Thread {
    private:
    Queue<Action*> game_queue;
    Game game; 
    std::map<uint32_t, Queue<GameStateForClient*>*> player_queues;
    std::atomic<bool> finished;

    public:
    explicit GameLoop();
    
    Queue<Action*>& getQueue();

    void addPlayer(uint32_t id, Queue<GameStateForClient*>& queue);
    void addClientQueue(Queue<GameStateForClient*>& queue);
    virtual void run() override;

    void stop();

    private: 
}; 
#endif