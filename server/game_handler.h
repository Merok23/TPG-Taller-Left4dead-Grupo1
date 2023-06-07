#ifndef SERVER_GAME_HANDLER_H
#define SERVER_GAME_HANDLER_H

#include <map>
#include <mutex>
#include <string>
#include <memory>

#include "game_loop.h"

class GameHandler {
    private: 
    std::map<uint32_t, GameLoop*> rooms;
    uint32_t rooms_id;
    std::mutex mutex;

    uint32_t createRoomId();

    public: 
    GameHandler();
    uint32_t createRoom(const std::string& room_name, 
        Queue<std::shared_ptr<GameStateForClient>>& client_queue, uint32_t& client_id, GameMode game_mode);
    bool joinRoom(uint32_t room_id, 
        Queue<std::shared_ptr<GameStateForClient>>& client_queue, uint32_t& client_id);
    Queue<Action*>& getQueue(uint32_t room_id);
    uint32_t getClientId();
    void leaveRoom(uint32_t room_id, Queue<std::shared_ptr<GameStateForClient>>&);
    ~GameHandler();
};
#endif
