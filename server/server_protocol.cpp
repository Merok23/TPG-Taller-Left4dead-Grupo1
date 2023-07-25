#include <vector>
#include <array>
#include <map>
#include <utility>

#include "server_protocol.h"


#define CREATE_ROOM_COMMAND 0x01
#define JOIN_ROOM_COMMAND 0x02
#define ADD_PLAYER_COMMAND 0x03
#define MOVE_PLAYER_COMMAND 0x04
#define SHOOT_PLAYER_COMMAND 0x05
#define RELOAD_PLAYER_COMMAND 0x06
#define CHEAT_INFINITE_HITPOINTS_COMMAND 0x07
#define CHEAT_SPAWN_COMMON_INFECTED_COMMAND 0x08
#define CHEAT_KILL_ALL_INFECTED_COMMAND 0x09

ServerProtocol::ServerProtocol(Socket socket) : socket(std::move(socket)), was_closed(false) {
    return; 
}

// --------------------------------- FUNCIONES DE RECIBIR BYTES ---------------------------------//

uint32_t ServerProtocol::receieveUnsignedInteger() {
    uint32_t number;
    uint32_t bytes = socket.recvall(&number, sizeof(uint32_t), &was_closed);
    if (was_closed && bytes != 0) throw LibError(errno, "Socket was closed while receiving unsigned integer. Errno: ");
    number = ntohl(number);
    return number;
}

std::string ServerProtocol::receiveString() {
    uint32_t len; 
    uint32_t bytes = socket.recvall(&len, sizeof(uint32_t), &was_closed); 
    if (was_closed && bytes != 0) throw LibError(errno, "Socket was closed while receiving string length. Errno: ");
    len = ntohl(len); 

    std::vector<char> string(len, 0x00);
    bytes = socket.recvall(string.data(), len, &was_closed);
    if (was_closed && bytes != 0) throw LibError(errno, "Socket was closed while receiving string. Errno: ");
    return std::string(string.begin(), string.end());
}

uint8_t ServerProtocol::receiveSmallUnsignedInt() {
    uint8_t number;
    uint8_t bytes = socket.recvall(&number, sizeof(uint8_t), &was_closed);
    if (was_closed && bytes != 0) throw LibError(errno, "Socket was closed while receiving small unsigned int. Errno: ");
    return number;
}

int8_t ServerProtocol::receiveSmallInt() {
    int8_t number;
    uint8_t bytes = socket.recvall(&number, sizeof(int8_t), &was_closed);
    if (was_closed && bytes != 0) throw LibError(errno, "Socket was closed while receiving small int. Errno: ");
    return number;
}

// --------------------------------- FUNCIONES DE ENVIAR BYTES ---------------------------------//

void ServerProtocol::sendUnsignedInteger(uint32_t number) {
    uint32_t number_to_send = htonl(number);
    uint32_t bytes = socket.sendall(&number_to_send, sizeof(uint32_t), &was_closed);
    if (was_closed && bytes != 0) throw LibError(errno, "Socket was closed while sending unsigned int. Errno: ");
}

void ServerProtocol::sendString(const std::string& string) {
    uint32_t len = string.length();
    len = htonl(len);
    uint32_t bytes = socket.sendall(&len, sizeof(uint32_t), &was_closed);
    if (was_closed && bytes != 0) throw LibError(errno, "Socket was closed while sending string length. Errno: ");
    bytes = socket.sendall((char*)string.c_str(), string.length(), &was_closed);
    if (was_closed && bytes != 0) throw LibError(errno, "Socket was closed while sending string. Errno: ");
}

void ServerProtocol::sendInteger(int32_t number) {
    int32_t number_to_send = htonl(number);
    int32_t bytes = socket.sendall(&number_to_send, sizeof(int32_t), &was_closed);
    if (was_closed && bytes != 0) throw LibError(errno, "Socket was closed while sending int. Errno: ");
}

void ServerProtocol::sendBool(const bool &boolean) {
    uint8_t bytes = socket.sendall(&boolean, sizeof(uint8_t), &was_closed);
    if (was_closed && bytes != 0) throw LibError(errno, "Socket was closed while sending boolean. Errno: ");
}

// --------------------------------- FUNCIONES DE RECIBIR ACCIONES ---------------------------------//

std::shared_ptr<Action> ServerProtocol::receiveAction() {
    uint8_t command = receiveSmallUnsignedInt();
    if (was_closed) return NULL; 
    std::shared_ptr<Action> action = NULL;

    switch (command) {
        case ADD_PLAYER_COMMAND:
            action = receiveAddPlayer();
            break;
        case MOVE_PLAYER_COMMAND:
            action = receiveMoving();
            break;
        case SHOOT_PLAYER_COMMAND:
            action = receiveShooting();
            break;
        case RELOAD_PLAYER_COMMAND:
            action = receiveReloading();
            break;
        case CHEAT_INFINITE_HITPOINTS_COMMAND:
            action = std::make_shared<SetInfiniteHitpointsCheat>();
            break;
        case CHEAT_SPAWN_COMMON_INFECTED_COMMAND:
            action = std::make_shared<SpawnCommonInfectedCheat>();
            break;
        case CHEAT_KILL_ALL_INFECTED_COMMAND:
            action = std::make_shared<KillAllInfectedCheat>();
            break;
        default:
            break;
    }
    return action;
}
 std::shared_ptr<Action> ServerProtocol::receiveMoving() {
    int8_t position_x = receiveSmallInt();
    int8_t position_y = receiveSmallInt();
    if (was_closed) return NULL;

    std::array<int8_t, 2> positionArray = {position_x, position_y};
    std::shared_ptr<Action> action = std::make_shared<Moving>(positionArray);
    return action;
}

std::shared_ptr<Action>  ServerProtocol::receiveAddPlayer() {
    std::string weapon = receiveString();
    if (was_closed) return NULL; 
    std::string name = receiveString();
    if(was_closed) return NULL;

    std::shared_ptr<Action> action = nullptr; 
    if (weapon == "idf") action = std::make_shared<CreateSoldierIdf>(name);
    else if (weapon == "scout") action = std::make_shared<CreateSoldierScout>(name);
    else if (weapon == "p90") action = std::make_shared<CreateSoldierP90>(name);
    return action;
}

std::shared_ptr<Action> ServerProtocol::receiveShooting() {
    uint8_t shooting = receiveSmallUnsignedInt();
    if (was_closed) return NULL; 

    std::shared_ptr<Action> action = std::make_shared<Shooting>((bool)shooting);
    return action;
}

std::shared_ptr<Action> ServerProtocol::receiveReloading() {
    uint8_t reloading = receiveSmallUnsignedInt();
    if (was_closed) return NULL;

    std::shared_ptr<Action> action = std::make_shared<Reloading>((bool)reloading);
    return action; 
}

command_t ServerProtocol::receiveCommand() {
    command_t return_command = command_t(); 
    uint8_t command = receiveSmallUnsignedInt();
    if (was_closed) return return_command; 

    if (command == CREATE_ROOM_COMMAND) {
        return_command.type = CREATE_ROOM;
        return_command.room_name = receiveString();
        if (was_closed) return return_command; 

        uint8_t game_mode = receiveSmallUnsignedInt();
        if (was_closed) return return_command; 
        return_command.game_mode = intToGameMode(game_mode);

    } else if (command == JOIN_ROOM_COMMAND) {
        return_command.type = JOIN_ROOM;
        return_command.room_id = receieveUnsignedInteger();
        if (was_closed) return return_command;
    }
    return return_command;
}

GameMode ServerProtocol::intToGameMode(uint8_t game_mode) {
    if (game_mode == 0) return GameMode::TESTING;
    if (game_mode == 1) return GameMode::SURVIVAL;
    return GameMode::CLEAR_THE_ZONE;
}

// --------------------------------- FUNCIONES DE ENVIAR ACCIONES ---------------------------------//

void ServerProtocol::sendGameState(std::shared_ptr<GameStateForClient> game_state) {
    this->sendFinishConditions(game_state->isGameOver(), game_state->didPlayersWin());
    if (was_closed) return; 
    std::map<uint32_t, Entity*> entities = game_state->getEntities();
    sendUnsignedInteger(entities.size());
    if (was_closed) return;

    for (auto entity : entities) {
        sendUnsignedInteger(entity.first); //id
        if (was_closed) return;
        
        sendString(entity.second->getState());
        if (was_closed) return;

        sendString(entity.second->getEntityType());
        if (was_closed) return;

        sendInteger(entity.second->getHitPoints());
        if (was_closed) return;

        int32_t interface_x = entity.second->getDirectionOfMovement()->getX() - 100;
        sendInteger(interface_x);
        if (was_closed) return;

        int32_t interface_y = CONFIG.scenario_height - entity.second->getDirectionOfMovement()->getY() + 800;
        sendInteger(interface_y);
        if (was_closed) return;

        this->sendBool(entity.second->getDirectionOfMovement()->isFacingLeft());
        if (was_closed) return;

        this->sendBool(entity.second->getDirectionOfMovement()->isMovingUp());
        if (was_closed) return;
        
        if (entity.second->getEntityType() == "player_idf" || entity.second->getEntityType() == "player_scout" || entity.second->getEntityType() == "player_p90") {
            Player* player = dynamic_cast<Player*>(entity.second);            
            sendInteger(player->getAmmoLeft());
            if (was_closed) return;

            uint8_t lives = player->getLives();
            socket.sendall(&lives, sizeof(uint8_t), &was_closed);
            if (was_closed) return;

            sendString(player->getName());
            if (was_closed) return;
        }
        
    }
    if (game_state->isGameOver()) {
        Statistics statistics = game_state->getStatistics();
        bool ranking = statistics.getRanking();
        socket.sendall(&ranking, sizeof(uint8_t), &was_closed);
        if (was_closed) return;

        std::pair<uint32_t, uint32_t> stats = statistics.getGameTimeInfo();
        socket.sendall(&stats.first, sizeof(uint8_t), &was_closed);
        if (was_closed) return;

        sendUnsignedInteger(stats.second);
        if (was_closed) return;

        stats = statistics.getInfectedKilledInfo();
            
        socket.sendall(&stats.first, sizeof(uint8_t), &was_closed);
        if (was_closed) return;

        sendUnsignedInteger(stats.second);
        if (was_closed) return;

        stats = statistics.getAmmoUsedInfo();
        socket.sendall(&stats.first, sizeof(uint8_t), &was_closed);
        if (was_closed) return;

        sendUnsignedInteger(stats.second); 
        if (was_closed) return;

        if (ranking) {
            std::list<uint32_t> top_infected_kills = statistics.getTopInfectedKills();
            std::list<uint32_t> top_ammo_used = statistics.getTopAmmoUsed();
            std::list<uint32_t> top_time_alive = statistics.getTopTimeAlive();

            sendUnsignedInteger(top_infected_kills.size());
            if (was_closed) return;

            for (auto& infected_kills : top_infected_kills) {
                sendUnsignedInteger(infected_kills);
                if (was_closed) return;
            }

            sendUnsignedInteger(top_ammo_used.size());
            if (was_closed) return;

            for (auto& ammo_used : top_ammo_used) {
                sendUnsignedInteger(ammo_used);
                if (was_closed) return;
            }

            sendUnsignedInteger(top_time_alive.size());
            if (was_closed) return;

            for (auto& time_alive : top_time_alive) {
                sendUnsignedInteger(time_alive);
                if (was_closed) return;
            }
        }
    } 
}

void ServerProtocol::sendFinishConditions(const bool &game_over, const bool &players_won) {
    this->sendBool(game_over);
    this->sendBool(players_won);
}

void ServerProtocol::sendRoomId(uint32_t room_id) {
    sendUnsignedInteger(room_id);
    if (was_closed) return;
}

void ServerProtocol::sendJoinResponse(bool accepted) {
    sendBool(accepted);
}

void ServerProtocol::sendGameMode(GameMode game_mode) {
    uint8_t bytes = socket.sendall(&game_mode, sizeof(uint8_t), &was_closed);
    if (was_closed && bytes != 0) throw LibError(errno, "Socket was closed while sending game mode. Errno: ");
}
// --------------------------------- OTRAS FUNCIONES ---------------------------------//
bool ServerProtocol::isFinished() {
    return was_closed;
}

void ServerProtocol::closeSocket() {
    if (was_closed) return;
    socket.shutdown(SHUT_RDWR);
    socket.close();
}
