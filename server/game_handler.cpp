#include <utility>
#include "game_handler.h"

GameHandler::GameHandler(): rooms_id(0), mutex() {}  //cambiar el 0 por una constante

uint32_t GameHandler::createRoomId() {
    return ++rooms_id;
}

uint32_t GameHandler::createRoom(const std::string& room_name, 
        Queue<std::shared_ptr<GameStateForClient>>& queue, uint32_t& client_id, GameMode game_mode) {
   std::unique_lock<std::mutex> lock(mutex);
    uint32_t room_id = createRoomId();
    GameLoop* game_loop = new GameLoop(game_mode);
    rooms.insert(std::make_pair(room_id, game_loop));
    game_loop->start();
    client_id = game_loop->addClientQueue(queue);
    return room_id;
}

Queue<std::shared_ptr<Action>>& GameHandler::getQueue(uint32_t room_id) {
    std::unique_lock<std::mutex> lock(mutex);
    auto it = rooms.find(room_id);
    return it->second->getQueue();
}

void GameHandler::leaveRoom(uint32_t room_id, 
    Queue<std::shared_ptr<GameStateForClient>>& queue) {
    std::unique_lock<std::mutex> lock(mutex);
    auto it = rooms.find(room_id);
    if (it == rooms.end()) return; 
    it->second->deleteClientQueue(queue);
    if (it->second->isRoomEmpty()) closeRoom();
}

bool GameHandler::joinRoom(uint32_t room_id, 
    Queue<std::shared_ptr<GameStateForClient>>& queue, uint32_t& client_id) {
    std::unique_lock<std::mutex> lock(mutex);
    auto it = rooms.find(room_id);
    if (it == rooms.end() || it->second->isFinished()) return false;
    client_id = it->second->addClientQueue(queue);
    return true;
}

void GameHandler::closeRoom() {
    for (auto it = rooms.begin(); it != rooms.end();) {
        if (it->second->isFinished()) {
            it->second->stop(); 
            it->second->join();
            delete it->second;
            it = rooms.erase(it);
        } else {
            ++it;
        }
    }
}

GameHandler::~GameHandler() {
    std::unique_lock<std::mutex>  lock(mutex);
    for (auto it = rooms.begin(); it != rooms.end(); ++it) {
        it->second->stop();
        it->second->join();
        delete it->second;
    }
}
