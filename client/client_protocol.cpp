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
    uint32_t bytes = socket.sendall(&len, sizeof(uint32_t), &was_closed);
    if (was_closed && bytes != 0) throw LibError(errno, "Socket was closed while sending message. Errno: ");
    
    bytes = socket.sendall((char*)string.c_str(), string.length(), &was_closed);
    if (was_closed && bytes != 0) throw LibError(errno, "Socket was closed while sending message. Errno: ");
}

void ClientProtocol::sendUnsignedInteger(uint32_t number) {
    uint32_t number_to_send = htonl(number);
    uint32_t bytes = socket.sendall(&number_to_send, sizeof(uint32_t), &was_closed);
    if (was_closed && bytes != 0) throw LibError(errno, "Socket was closed while sending message. Errno: ");
}

void ClientProtocol::sendUnsignedSmallInteger(uint8_t number) {
    uint8_t number_to_send = number;
    uint32_t bytes = socket.sendall(&number_to_send, sizeof(uint8_t), &was_closed);
    if (was_closed && bytes != 0) throw LibError(errno, "Socket was closed while sending message. Errno: ");
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
            sendCheat(CHEAT_INFINITE_HITPOINTS_COMMAND);
            break;
        }
        case (Commands::CHEAT_SPAWN_COMMON_INFECTED): {
            sendCheat(CHEAT_SPAWN_COMMON_INFECTED_COMMAND);
            break;
        }
        case (Commands::CHEAT_KILL_ALL_INFECTED): {
            sendCheat(CHEAT_KILL_ALL_INFECTED_COMMAND);
            break;
        }
    }
}
void ClientProtocol::sendCheat(uint8_t cheat) {
    sendUnsignedSmallInteger(cheat);
    if (was_closed) return;
}

void ClientProtocol::sendCreateRoom(const std::string& room_name, GameMode game_mode) {
    uint8_t action = CREATE_ROOM_COMMAND;
    sendUnsignedSmallInteger(action);
    if (was_closed) return;
    sendString(room_name);
    if (was_closed) return;
    sendUnsignedSmallInteger((uint8_t)game_mode);
    if (was_closed) return;
}

void ClientProtocol::sendJoinRoom(int room_id) {
    uint8_t action = JOIN_ROOM_COMMAND;
    sendUnsignedSmallInteger(action);
    if (was_closed) return;

    sendUnsignedInteger(room_id);
   if (was_closed) return;
}

void ClientProtocol::sendAddPlayer(const std::string& weapon) {
    uint8_t action = ADD_PLAYER_COMMAND;
    sendUnsignedSmallInteger(action);
    if (was_closed) return;
    sendString(weapon);
    if (was_closed) return;
}

void ClientProtocol::sendMoving(int8_t moving_x, int8_t moving_y) {
    uint8_t action = MOVE_PLAYER_COMMAND;  
    sendUnsignedSmallInteger(action);
    if (was_closed) return;

    int bytes = socket.sendall(&moving_x, sizeof(int8_t), &was_closed);
    if (was_closed && bytes != 0) throw LibError(errno, "Socket was closed while sending message. Errno: ");
    if (was_closed) return;

    socket.sendall(&moving_y, sizeof(int8_t), &was_closed);
    if (was_closed && bytes != 0) throw LibError(errno, "Socket was closed while sending message. Errno: ");
    if (was_closed) return;
}

void ClientProtocol::sendShooting(int shooting) {
    uint8_t action = SHOOT_PLAYER_COMMAND;  
    sendUnsignedSmallInteger(action);
    if (was_closed) return;

   sendUnsignedSmallInteger(shooting);
    if (was_closed) return;
}


void ClientProtocol::sendReloading(int reloading) {
    uint8_t action = RELOAD_PLAYER_COMMAND;  
    sendUnsignedSmallInteger(action);
    if (was_closed) return;

   sendUnsignedSmallInteger(reloading);
    if (was_closed) return;
}

//--------------------------------- FUNCIONES DE RECIBIR RESPUESTA A COMANDOS ---------------------------------//

uint32_t ClientProtocol::receiveRoomId() {
    uint32_t room_id = receieveUnsignedInteger();
    return room_id;
}

bool ClientProtocol::receiveJoinResponse() {
    uint8_t response = receiveUnsignedSmallInteger();
    return (bool)response;
}

std::shared_ptr<GameState> ClientProtocol::receiveGameState() {
    uint8_t game_over;
    game_over = receiveUnsignedSmallInteger();
    if (was_closed) return NULL; 

    bool players_won = (bool)receiveUnsignedSmallInteger();
    if (was_closed) return NULL;    

    std::map<uint32_t, Entity*> entities;
    uint32_t entities_len = receieveUnsignedInteger();
    if (was_closed) return NULL; 

    while (entities_len > 0) {
        uint32_t id = receieveUnsignedInteger();
        if (was_closed) return NULL; 
    
        std::string state = receiveString();
        if (was_closed) return NULL; 
    
        State state_enum = stringToState(state);

        std::string type = receiveString();
        std::cout << "type: " << type << std::endl;
        if (was_closed) return NULL; 
        EntityType entity_type = stringToEntityType(type);
            
        int32_t hit_point = receiveInteger();
        if (was_closed) return NULL; 
    
        int32_t position_x = receiveInteger(); 
        if (was_closed) return NULL; 
            int32_t position_y = receiveInteger(); 
        if (was_closed) return NULL; 
    
        bool is_facing_left = (bool)receiveUnsignedSmallInteger();
        if (was_closed) return NULL; 
    
        bool is_moving_up = (bool)receiveUnsignedSmallInteger();
        if (was_closed) return NULL; 
            
        Entity* entity = NULL;
        
        if (entity_type == EntityType::SOLDIER_IDF ||
            entity_type == EntityType::SOLDIER_P90 ||
            entity_type == EntityType::SOLDIER_SCOUT) {
            int32_t ammo_left = receiveInteger();
            if (was_closed) return NULL;

            uint8_t lives = receiveUnsignedSmallInteger();
            if (was_closed) return NULL;

            entity = new Entity(id, entity_type, state_enum, lives, ammo_left, hit_point,
                                position_x, position_y, is_facing_left, is_moving_up);
        } else if (entity_type == EntityType::ZOMBIE ||
                entity_type == EntityType::SPEAR ||
                entity_type == EntityType::WITCH ||
                entity_type == EntityType::JUMPER ||
                entity_type == EntityType::VENOM ||
                entity_type == EntityType::CRATER) {
            entity = new Entity(id, entity_type, state_enum, hit_point, position_x, position_y,
                                is_facing_left, is_moving_up);
        }
        entities[id] = entity;
        entities_len--; 
    }
    std::shared_ptr<GameState> game_state = std::make_shared<GameState>(entities, game_over, players_won);
    return game_state;
}

EntityType ClientProtocol::stringToEntityType(const std::string& entity_type) {
    static const std::unordered_map<std::string, EntityType> entityTypeMap = {
        { "player_idf", SOLDIER_IDF },
        { "player_p90", SOLDIER_P90 },
        { "player_scout", SOLDIER_SCOUT },
        { "jumper", JUMPER },
        { "venom", VENOM },
        { "spear", SPEAR },
        { "witch", WITCH },
        { "common_infected", ZOMBIE },
        { "crater", CRATER }
    };

    auto it = entityTypeMap.find(entity_type);
    return it->second;
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
        { "reviving", REVIVING},
        { "screaming", SCREAMING}
    };

    auto it = stateMap.find(state);
    return it->second;
}

//--------------------------------- FUNCIONES DE RECIBIR BYTES PRIVADAS ---------------------------------//

uint32_t ClientProtocol::receieveUnsignedInteger() {
    uint32_t number;
    uint32_t bytes = socket.recvall(&number, sizeof(uint32_t), &was_closed);
    if (was_closed && bytes != 0) throw LibError(errno, "Socket was closed while receiving message. Errno: "); 
    number = ntohl(number);
    return number;
}

std::string ClientProtocol::receiveString() {
    uint32_t len; 
    uint32_t  bytes = socket.recvall(&len, sizeof(uint32_t), &was_closed); 
    if (was_closed && bytes != 0) throw LibError(errno, "Socket was closed while receiving message. Errno: ");
    len = ntohl(len); 

    std::vector<char> string(len, 0x00);
    bytes = socket.recvall(string.data(), len, &was_closed);
    if (was_closed && bytes != 0) throw LibError(errno, "Socket was closed while receiving message. Errno: ");
    return std::string(string.begin(), string.end());
}

int32_t ClientProtocol::receiveInteger() {
    int32_t  number;
    int32_t bytes = socket.recvall(&number, sizeof(uint32_t), &was_closed);
    if (was_closed && bytes != 0) throw LibError(errno, "Socket was closed while receiving message. Errno: ");
    number = ntohl(number);
    return number;
}

uint8_t ClientProtocol::receiveUnsignedSmallInteger() {
    uint8_t command;
    uint8_t bytes = socket.recvall(&command, sizeof(uint8_t), &was_closed);
    if (was_closed && bytes != 0) throw LibError(errno, "Socket was closed while receiving message. Errno: ");
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