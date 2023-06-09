#include <iostream>
#include <fstream>
#include <unordered_map>
#include <map>
#include <utility>

#include "client_protocol.h"
#define MAX_TYPE_LENGHT 200

#define CREATE_ROOM_COMMAND 0x01
#define JOIN_ROOM_COMMAND 0x02
#define ADD_PLAYER_COMMAND 0x03
#define MOVE_PLAYER_COMMAND 0x04
#define SHOOT_PLAYER_COMMAND 0x05
#define RELOAD_PLAYER_COMMAND 0x06
#define CHEAT_INFINITE_HITPOINTS_COMMAND 0x07
#define CHEAT_SPAWN_COMMON_INFECTED_COMMAND 0x08
#define CHEAT_KILL_ALL_INFECTED_COMMAND 0x09

ClientProtocol::ClientProtocol(Socket socket) : socket(std::move(socket)), was_closed(false) {
    return; 
}   
//--------------------------------- FUNCIONES DE ENVIAR BYTES ---------------------------------//

void ClientProtocol::sendString(const std::string& string) {
    uint32_t len = string.length();
    len = htonl(len);
    socket.sendall(&len, sizeof(uint32_t), &was_closed);
    socket.sendall((char*)string.c_str(), string.length(), &was_closed);
}

void ClientProtocol::sendUnsignedInteger(uint32_t number) {
    uint32_t number_to_send = htonl(number);
    socket.sendall(&number_to_send, sizeof(uint32_t), &was_closed);
}


//--------------------------------- FUNCIONES DE ENVIAR COMMANDOS PRIVADAS ---------------------------------//
void ClientProtocol::sendCommand(command_t command) {
    switch (command.type) {
        case (Commands::CREATE_ROOM): {
            sendCreateRoom(command.room_name, command.game_mode);
            break;
        }
        case (Commands::JOIN_ROOM): {
            sendJoinRoom(command.room_id);
            break;
        }
        case (Commands::ADD_PLAYER): {
            sendAddPlayer(command.weapon);
            break;
        }
        case (Commands::MOVE_PLAYER): {
            sendMoving(command.moving_x, command.moving_y);
            break;
        }
        case (Commands::SHOOT_PLAYER): {
            sendShooting(command.shooting);
            break;
        }
        case (Commands::RELOAD_PLAYER): {
            sendReloading(command.reloading);
            break;
        }
        case (Commands::CHEAT_INFINITE_HITPOINTS): {
            sendCheatInfiniteHitpoints();
            break;
        }
        case (Commands::CHEAT_SPAWN_COMMON_INFECTED): {
            sendCheatSpawnCommonInfected();
            break;
        }
        case (Commands::CHEAT_KILL_ALL_INFECTED): {
            sendCheatKillAllInfected();
            break;
        }
    }
    /*
    if (command.type == Commands::CREATE_ROOM) 
        sendCreateRoom(command.room_name, command.game_mode); 
    else if (command.type == Commands::JOIN_ROOM) 
        sendJoinRoom(command.room_id);
    else if (command.type == Commands::ADD_PLAYER) 
        sendAddPlayer(command.weapon);
    else if (command.type == Commands::MOVE_PLAYER) 
        sendMoving(command.moving_x, command.moving_y);
    else if (command.type == Commands::SHOOT_PLAYER)
        sendShooting(command.shooting);
    else if (command.type == Commands::RELOAD_PLAYER)
        sendReloading(command.reloading);
    */
}

void ClientProtocol::sendCheatInfiniteHitpoints() {
    uint8_t action = CHEAT_INFINITE_HITPOINTS_COMMAND;
    socket.sendall(&action, sizeof(uint8_t), &was_closed);
    if (was_closed) throw LibError(errno, "Socket was closed while sending cheat infinite hitpoints. Errno: ");
}

void ClientProtocol::sendCheatSpawnCommonInfected() {
    uint8_t action = CHEAT_SPAWN_COMMON_INFECTED_COMMAND;
    socket.sendall(&action, sizeof(uint8_t), &was_closed);
    if (was_closed) throw LibError(errno, "Socket was closed while sending cheat spawn common infected. Errno: ");
}

void ClientProtocol::sendCheatKillAllInfected() {
    uint8_t action = CHEAT_KILL_ALL_INFECTED_COMMAND;
    socket.sendall(&action, sizeof(uint8_t), &was_closed);
    if (was_closed) throw LibError(errno, "Socket was closed while sending cheat kill all infected. Errno: ");
}

void ClientProtocol::sendCreateRoom(const std::string& room_name, uint8_t game_mode) {
    uint8_t action = CREATE_ROOM_COMMAND;
    socket.sendall(&action, sizeof(uint8_t), &was_closed);
    if(was_closed) throw LibError(errno, "Socket was closed while sending create room. Errno: ");
    sendString(room_name);
    if (was_closed) throw LibError(errno, "Socket was closed while sending room name. Errno: ");

    socket.sendall(&game_mode, sizeof(uint8_t), &was_closed);
    if (was_closed) throw LibError(errno, "Socket was closed while sending game mode. Errno: "); 
}

void ClientProtocol::sendJoinRoom(int room_id) {
    uint8_t action = JOIN_ROOM_COMMAND;
    socket.sendall(&action, sizeof(uint8_t), &was_closed);
    if (was_closed) throw LibError(errno, "Socket was closed while sending join room. Errno: "); 

    sendUnsignedInteger(room_id);
    if (was_closed) throw LibError(errno, "Socket was closed while sending room id. Errno: ");
}

void ClientProtocol::sendAddPlayer(const std::string& weapon) {
    uint8_t action = ADD_PLAYER_COMMAND;
    socket.sendall(&action, sizeof(uint8_t), &was_closed);
    if (was_closed) throw LibError(errno, "Socket was closed while sending add player. Errno: "); 

    sendString(weapon);
    if (was_closed) throw LibError(errno, "Socket was closed while sending weapon. Errno: ");
}

void ClientProtocol::sendMoving(int8_t moving_x, int8_t moving_y) {
    uint8_t action = MOVE_PLAYER_COMMAND;  
    socket.sendall(&action, sizeof(uint8_t), &was_closed);
    if (was_closed) throw LibError(errno, "Socket was closed while sending moving. Errno: "); 

    socket.sendall(&moving_x, sizeof(int8_t), &was_closed);
    if (was_closed) throw LibError(errno, "Socket was closed while sending moving x. Errno: ");

    socket.sendall(&moving_y, sizeof(int8_t), &was_closed);
    if (was_closed) throw LibError(errno, "Socket was closed while sending moving y. Errno: ");
}

void ClientProtocol::sendShooting(int shooting) {
    uint8_t action = SHOOT_PLAYER_COMMAND;  
    socket.sendall(&action, sizeof(uint8_t), &was_closed);
    if (was_closed) throw LibError(errno, "Socket was closed while sending shooting. Errno: ");

    socket.sendall(&shooting, sizeof(uint8_t), &was_closed);
    if (was_closed) throw LibError(errno, "Socket was closed while sending shooting. Errno: ");
}


void ClientProtocol::sendReloading(int reloading) {
    uint8_t action = RELOAD_PLAYER_COMMAND;  
    socket.sendall(&action, sizeof(uint8_t), &was_closed);
    if (was_closed) throw LibError(errno, "Socket was closed while sending reloading. Errno: "); 
     
    socket.sendall(&reloading, sizeof(uint8_t), &was_closed);
    if (was_closed) throw LibError(errno, "Socket was closed while sending reloading state. Errno: ");
}

//--------------------------------- FUNCIONES DE RECIBIR RESPUESTA A COMANDOS ---------------------------------//

uint32_t ClientProtocol::receiveRoomId() {
    uint32_t room_id = receieveUnsignedInteger();
    if (was_closed) throw LibError(errno, "Socket was closed while receiving room id. Errno: ");
    return room_id;
}

bool ClientProtocol::receiveJoinResponse() {
    uint8_t response;
    socket.recvall(&response, sizeof(uint8_t), &was_closed);
    if (was_closed) throw LibError(errno, "Socket was closed while receiving join response. Errno: "); 
    return (bool)response;
}

std::shared_ptr<GameState> ClientProtocol::receiveGameState() {
    bool game_over = (bool)receiveUnsignedSmallInteger();
    if (was_closed) throw LibError(errno, "Socket was closed while receiving game over. Errno: ");
    bool players_won = (bool)receiveUnsignedSmallInteger();
    if (was_closed) throw LibError(errno, "Socket was closed while receiving game won. Errno: ");
    std::map<uint32_t, Entity*> entities;
    uint32_t bytes, entities_len;
    bytes = socket.recvall(&entities_len, sizeof(uint32_t), &was_closed);
    entities_len = ntohl(entities_len);
    if (was_closed && bytes == 0) return NULL;
    if (was_closed && bytes != 0) throw LibError(errno, "Socket was closed while receiving entities length. Errno: "); 

    while (entities_len > 0) {
        uint32_t id = receieveUnsignedInteger();
        if (was_closed) throw LibError(errno, "Socket was closed while receiving entity id. Errno: ");

        std::string state = receiveString();
        if (was_closed) throw LibError(errno, "Socket was closed while receiving entity state. Errno: ");
        State state_enum = stringToState(state);

        std::string type = receiveString();
        if (was_closed) throw LibError(errno, "Socket was closed while receiving entity type. Errno: ");
        
        int32_t hit_point = receiveInteger();
        if (was_closed) throw LibError(errno, "Socket was closed while receiving entity hit point. Errno: ");

        int32_t position_x = receiveInteger(); 
        if (was_closed) throw LibError(errno, "Socket was closed while receiving entity position x. Errno: ");
        int32_t position_y = receiveInteger(); 
        if (was_closed) throw LibError(errno, "Socket was closed while receiving entity position y. Errno: "); 

        bool is_facing_left = (bool)receiveUnsignedSmallInteger();
        if (was_closed) throw LibError(errno, "Socket was closed while receiving entity facing left. Errno: ");

        bool is_moving_up = (bool)receiveUnsignedSmallInteger();
        if (was_closed) throw LibError(errno, "Socket was closed while receiving entity moving up. Errno: ");
        
        Entity* entity = NULL;
        if (type == "player") {
            WeaponType weapon_type = stringToWeapon(receiveString());
            if (was_closed) throw LibError(errno, "Socket was closed while receiving entity weapon type. Errno: ");

            int32_t ammo_left = receiveInteger();
            if (was_closed) throw LibError(errno, "Socket was closed while receiving entity ammo left. Errno: ");

            uint8_t lives = receiveUnsignedSmallInteger();
            if (was_closed) throw LibError(errno, "Socket was closed while receiving entity lives. Errno: ");

            EntityTypeGS entity_type = SOLDIER;
            entity =   new Entity(id, entity_type, state_enum, lives, weapon_type, ammo_left,  hit_point, 
            position_x,  position_y, is_facing_left, is_moving_up);
        } else if (type == "common_infected") {
            EntityTypeGS entity_type = COMMON_INFECTED;
            entity = new Entity(id, entity_type, state_enum, hit_point, position_x, position_y, 
                is_facing_left, is_moving_up);
        } else if (type == "spear") {
            EntityTypeGS entity_type = SPEAR_INFECTED;
            entity = new Entity(id, entity_type, state_enum, hit_point, position_x, position_y, 
                is_facing_left, is_moving_up);
        }
        entities[id] = entity;
        entities_len--; 
    }
    std::shared_ptr<GameState> game_state = std::make_shared<GameState>(entities, game_over, players_won);
    return game_state;
}

State ClientProtocol::stringToState(const std::string& state) {
    static const std::unordered_map<std::string, State> stateMap = {
        { "moving", RUN },
        { "shooting", SHOOT },
        { "reloading", RELOAD },
        { "dead", DIE },
        { "idle", IDLE},
        { "attacking", ATTACKING},
        { "down", DOWN },
        { "reviving", REVIVING}
    };

    auto it = stateMap.find(state);
    return it->second;
}

WeaponType ClientProtocol::stringToWeapon(const std::string& weapon) {
    static const std::unordered_map<std::string, WeaponType> weaponMap = {
        { "idf", WeaponType::IDF },
        { "p90", WeaponType::P90 },
        { "scout", WeaponType::SCOUT },
    };

    auto it = weaponMap.find(weapon);
    return it->second;
}
//--------------------------------- FUNCIONES DE RECIBIR BYTES PRIVADAS ---------------------------------//

uint32_t ClientProtocol::receieveUnsignedInteger() {
    uint32_t number;
    socket.recvall(&number, sizeof(uint32_t), &was_closed);
    number = ntohl(number);
    return number;
}

std::string ClientProtocol::receiveString() {
    uint32_t len; 
    socket.recvall(&len, sizeof(uint32_t), &was_closed); 
    len = ntohl(len); 

    std::vector<char> string(len, 0x00);
    socket.recvall(string.data(), len, &was_closed);
    return std::string(string.begin(), string.end());
}

int32_t ClientProtocol::receiveInteger() {
    int32_t  number;
    socket.recvall(&number, sizeof(uint32_t), &was_closed);
    number = ntohl(number);
    return number;
}

uint8_t ClientProtocol::receiveUnsignedSmallInteger() {
    uint8_t command;
    socket.recvall(&command, sizeof(uint8_t), &was_closed);
    return command;
}

//--------------------------------- OTRAS FUNCIONES ---------------------------------//

bool ClientProtocol::isFinished() {
    return was_closed;
}

void ClientProtocol::closeSocket() {
    if (was_closed) return;
    socket.shutdown(SHUT_RDWR);
    socket.close();
}