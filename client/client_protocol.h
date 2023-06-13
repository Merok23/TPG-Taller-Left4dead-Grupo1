#ifndef CLIENT_PROTOCOL_H
#define CLIENT_PROTOCOL_H
#include <memory>
#include <string>
#include <vector>
#include "../common/socket.h"
#include "game_state.h"

typedef struct command_t {
	Commands type;
	std::string room_name;
	GameMode game_mode;
	std::string weapon;
	int8_t moving_x;
	int8_t moving_y;
	bool shooting;
	bool reloading;
	uint32_t room_id;


	command_t operator=(const command_t& other) {
        type = other.type;
        room_name = other.room_name;
        game_mode = other.game_mode;
        weapon = other.weapon;
        moving_x = other.moving_x;
        moving_y = other.moving_y;
        shooting = other.shooting;
        reloading = other.reloading;
        room_id = other.room_id;
        return *this;
    }

} command_t;

struct COMMANDS {

	command_t createRoom(const std::string &name, GameMode game_mode)
	{
		command_t command;
		command.type = CREATE_ROOM;
		command.room_name = name;
		command.game_mode = game_mode;
		return command;
	}

	command_t joinRoom(uint32_t id)
	{
		command_t command;
		command.type = JOIN_ROOM;
		command.room_id = id;
		return command;
	}

	command_t addPlayer(const std::string &weapon)
	{
		command_t command;
		command.type = ADD_PLAYER;
		command.weapon = weapon;
		return command;
	}

	command_t setDirectionOfMovement(int8_t x, int8_t y)
	{
		command_t command;
		command.type = MOVE_PLAYER;
		command.moving_x = x;
		command.moving_y = y;
		return command;
	}

	command_t setShooting(bool shoot)
	{
		command_t command;
		command.type = SHOOT_PLAYER;
		command.shooting = shoot;
		return command;
	}

	command_t setReloading(bool reload)
	{
		command_t command;
		command.type = RELOAD_PLAYER;
		command.reloading = reload;
		return command;
	}

	command_t cheatInfiniteHitpoints()
	{
		command_t command;
		command.type = CHEAT_INFINITE_HITPOINTS;
		return command;
	}

	command_t cheatSpawnCommonInfected()
	{
		command_t command;
		command.type = CHEAT_SPAWN_COMMON_INFECTED;
		return command;
	}

	command_t cheatKillAllInfected()
	{
		command_t command;
		command.type = CHEAT_KILL_ALL_INFECTED;
		return command;
	}
};

class ClientProtocol {
    private:
	Socket socket;
	bool was_closed;

	uint32_t receieveUnsignedInteger();
	std::string receiveString();
	int32_t receiveInteger();
	void sendUnsignedInteger(uint32_t number);
	uint8_t receiveUnsignedSmallInteger();
	void sendUnsignedSmallInteger(uint8_t number);
	void sendCheat(uint8_t cheat);
	void sendString(const std::string &string);
	void sendCreateRoom(const std::string &room_name, GameMode game_mode);
	void sendJoinRoom(int room_id);
	void sendMoving(int8_t moving_x, int8_t moving_y);
	void sendAddPlayer(const std::string &weapon);
	void sendShooting(int shooting);
	void sendReloading(int reloading);
	State stringToState(const std::string &state);
	WeaponType stringToWeapon(const std::string &weapon);
	EntityType stringToEntityType(const std::string &entity_type);

    public:
	explicit ClientProtocol(Socket socket);
	void sendCommand(command_t command);
	bool isFinished();
	void closeSocket();
	uint32_t receiveRoomId();
	bool receiveJoinResponse();

	std::shared_ptr<GameState> receiveGameState();
};
#endif