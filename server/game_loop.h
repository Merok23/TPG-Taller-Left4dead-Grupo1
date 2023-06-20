#ifndef GAME_LOOP_H
#define GAME_LOOP_H
#include <atomic>   
#include <map>
#include <memory>
#include <chrono>

#include "../common/queue.h"
#include "action.h"
#include "../common/thread.h"  
#include "entity_player.h"
#include "id_handler.h" 



class GameLoop : public Thread {
    private:
    Queue<std::shared_ptr<Action>> game_queue;
    GameMode game_mode;
    Game game;
    IdHandler id_handler; 
    std::map<uint32_t, Queue<std::shared_ptr<GameStateForClient>>*> player_queues;
    std::atomic<bool> finished;
    std::atomic<int> client_id;
    std::chrono::high_resolution_clock::time_point start_loop_time;
    uint32_t total_loop_time;   
    std::mutex mutex;
    private:
    void setStadisticsCTZ(std::shared_ptr<GameStateForClient>& game_state);
    void setStadisticsSurvival(std::shared_ptr<GameStateForClient>& game_state);
    void sortRankingStadistic(std::vector<std::pair<uint32_t, uint32_t>>& stadistic);
    uint8_t getRanking(std::vector<std::pair<uint32_t, uint32_t>>& stadistic, uint32_t id);


    public:
    explicit GameLoop(GameMode gameMode);
    Queue<std::shared_ptr<Action>>& getQueue();
    int addClientQueue(Queue<std::shared_ptr<GameStateForClient>>& queue);
    void deleteClientQueue(Queue<std::shared_ptr<GameStateForClient>>& queue);
    bool isRoomEmpty();
    GameMode getGameMode();
    void setGameStadistics(std::shared_ptr<GameStateForClient>& game_state);
    int getTotalTimeOfGameLoop();
    void endGameLoopTime();
    virtual void run() override;
    bool isFinished();
    void stop();
    ~GameLoop();
}; 
#endif
