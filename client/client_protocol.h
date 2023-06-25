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


	command_t& operator=(const command_t& other) {
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
	Socket socket; /** < Socket de la conexión. */
	bool was_closed; /** < Indica si el socket fue cerrado. */

	/**
	 * @brief Recibe un entero sin signo de 32 bits del cliente.
	 * 
	 * @return El entero sin signo de 32 bits recibido.
	*/
	uint32_t receieveUnsignedInteger();

	/**
	 * @brief Recibe una cadena de texto del cliente.
	 * 
	 * @return La cadena de texto recibida.
	*/
	std::string receiveString();

	/**
	 * @brief Recibe un entero de 32 bits del cliente.
	 * 
	 * @return El entero de 32 bits recibido.
	*/
	int32_t receiveInteger();

	/**
	 * @brief Envía un entero sin signo de 32 bits al cliente.
	 * 
	 * @param number El entero sin signo de 32 bits a enviar.
	*/
	void sendUnsignedInteger(uint32_t number);

	/**
	 * @brief Recibe un entero sin signo de 8 bits del cliente.
	 * 
	 * @return El entero sin signo de 8 bits recibido.
	*/
	uint8_t receiveUnsignedSmallInteger();

	/**
	 * @brief Envía un entero sin signo de 8 bits al cliente.
	 * 
	 * @param number El entero sin signo de 8 bits a enviar.
	*/
	void sendUnsignedSmallInteger(uint8_t number);

	/**
	 * @brief Envia un uint_8 indicando el comando de cheats
	*/
	void sendCheat(uint8_t cheat);


	/**
	 * @brief Envia una cadena de texto al cliente.
	*/
	void sendString(const std::string &string);

	/**
	 * @brief Envia el comando de crear sala al al servidor, junto con 
	 * 		el nombre de la partida y el modo de juego.
	*/
	void sendCreateRoom(const std::string &room_name, GameMode game_mode);

	/**
	 * @brief Envia el comando de unirse a una sala al servidor, junto con 
	 * 		el id de la sala.
	*/
	void sendJoinRoom(int room_id);

	/**
	 * @brief Envia el comando de moverse al servidor, junto con 
	 * 		la dirección de movimiento.
	*/
	void sendMoving(int8_t moving_x, int8_t moving_y);

	/**
	 * @brief Envia el comando de agregar un jugador al servidor, junto con 
	 * 		el arma del jugador.
	*/
	void sendAddPlayer(const std::string &weapon);

	/**
	 * @brief Envia el comando de disparar al servidor, junto con el valor
	 * 		que indica si esta disparando o dejo de dispara.
	*/
	void sendShooting(int shooting);

	/**
	 * @brief Envia el comando de recargar al servidor, junto con el valor
	 * 		que indica si esta recargando o dejo de recargar.
	*/
	void sendReloading(int reloading);

	/**
	 * @brief Transforma un string a un enum del tipo State.
	 * 
	 * @param state El string a transformar.
	 * 
	 * @return El enum del tipo State.
	*/
	State stringToState(const std::string &state);

	/**
	 * @brief Transforma un string a un enum del tipo EntityType.
	 * 
	 * @param entity_type El string a transformar.
	 * 
	 * @return El enum del tipo EntityType.
	*/
	EntityType stringToEntityType(const std::string &entity_type);

    public:

	/**
	 * @brief Constructor de la clase.
	 * 
	 * @param socket El socket de la conexión.
	 * 
	 */
	explicit ClientProtocol(Socket socket);


	/**
	 * @brief Envia el comando del cliente al servidor.
	 * 
	 * @param command El comando a enviar.
	*/
	void sendCommand(command_t command);

	 /**
     * @brief Verifica si la comunicación con el servidor ha finalizado.
     *
     * @return `true` si la comunicación ha finalizado, `false` de lo contrario.
     */
	bool isFinished();

	/**
	 * @brief Cierra el socket de la conexión.
	*/
	void closeSocket();

	/**
	 * @brief Recibe el ID de la sala a la que se ha unido el cliente.
	 * 
	 * @return El ID de la sala a la que se ha unido el cliente.
	*/
	uint32_t receiveRoomId();

	/**
	 * @brief Recibe el la respuesta a la petición de unirse a una partida.
	 * 
	 * @return true si se acepto la petición, false de lo contrario.
	*/
	bool receiveJoinResponse();

	/**
	 * @brief Recibe el modo de juego de la partida.
	 * 
	 * @return El modo de juego de la partida.
	*/
	GameMode receiveGameMode();

	/**
	 * @brief Recibe el estado de juego de la partida.
	 * 
	 * @return Un puntero compartido al estado de juego de la partida.
	*/

	std::shared_ptr<GameState> receiveGameState();
};
#endif