#ifndef GAME_LOOP_H
#define GAME_LOOP_H
#include <atomic>   
#include <map>
#include <memory>

#include "../common/queue.h"
#include "action.h"
#include "../common/thread.h"  
#include "entity_player.h"
#include "id_handler.h" 

class GameLoop : public Thread {
    private:
    Queue<Action*> game_queue;
    Game game;
    IdHandler id_handler; 
    std::map<uint32_t, Queue<std::shared_ptr<GameStateForClient>>*> player_queues;
    std::atomic<bool> finished;
    std::atomic<int> client_id; 
    std::mutex mutex;

    public:
    GameLoop();
    Queue<Action*>& getQueue();
    int addClientQueue(Queue<std::shared_ptr<GameStateForClient>>& queue);
    void deleteClientQueue(Queue<std::shared_ptr<GameStateForClient>>& queue);
    virtual void run() override;
    void stop();
}; 
#endif
