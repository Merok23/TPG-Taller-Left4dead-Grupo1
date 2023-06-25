#ifndef SERVER_PROTOCOL_H
#define SERVER_PROTOCOL_H

#include <array>
#include <string>
#include <memory>

#include "../common/socket.h"
#include "action_moving.h"
#include "action_shooting.h"
#include "action_reloading.h"
#include "action_create_soldier_idf.h"
#include "action_create_soldier_p90.h"
#include "action_create_soldier_scout.h"
#include "action_cheat_infinite_hp.h"
#include "action_cheat_spawn_common_infected.h"
#include "action_cheat_kill_all_infected.h"


enum COMMANDS_TYPE {
    DEFAULT,
    CREATE_ROOM,
    JOIN_ROOM
};

typedef struct COMMANDS {
    COMMANDS_TYPE type;
    std::string room_name;
    uint32_t room_id;
    GameMode game_mode;
    COMMANDS() : 
        type(DEFAULT), room_name(""), room_id(0), game_mode(GameMode::SURVIVAL) {}
} command_t;


class ServerProtocol {
    private:
    Socket socket; /** < Socket de la conexión. */
    bool was_closed;  /** < Indica si el socket fue cerrado. */

    /**
     * @brief Envía un entero de 32 bits al cliente.
     *
     * @param number El entero de 32 bits a enviar.
     */
    void sendInteger(int32_t number);

    /**
     * @brief Envía una cadena de texto al cliente.
     *
     * @param string La cadena de texto a enviar.
     */
    void sendString(const std::string& string);

    /**
     * @brief Envía un entero sin signo de 32 bits al cliente.
     *
     * @param number El entero sin signo de 32 bits a enviar.
     */
    void sendUnsignedInteger(uint32_t number);

    /**
     * @brief Envía un booleano al cliente.
     *
     * @param boolean El booleano a enviar.
     */
    void sendBool(const bool& boolean);

    /**
     * @brief Envía las condiciones de finalización del juego al cliente.
     *
     * @param game_finished Indica si el juego ha terminado.
     * @param game_won Indica si los jugadores han ganado el juego.
     */
    void sendFinishConditions(const bool &game_finished, const bool &game_won);

    /**
     * @brief Recibe una cadena de texto del cliente.
     *
     * @return La cadena de texto recibida.
     */
    std::string receiveString();

    /**
     * @brief Recibe una acción de movimiento del cliente.
     *
     * @return Un puntero compartido a la acción de movimiento recibida.
     */
    std::shared_ptr<Action> receiveMoving();

    /**
     * @brief Recibe una acción de disparo del cliente.
     *
     * @return Un puntero compartido a la acción de disparo recibida.
     */
    std::shared_ptr<Action> receiveShooting();

    /**
     * @brief Recibe una acción de recarga del cliente.
     *
     * @return Un puntero compartido a la acción de recarga recibida.
     */
    std::shared_ptr<Action> receiveReloading();

    /**
     * @brief Recibe una acción de creación de soldado IDF del cliente.
     *
     * @return Un puntero compartido a la acción de creación de soldado IDF recibida.
     */
    std::shared_ptr<Action> receiveAddPlayer();

    /**
     * @brief Recibe una acción de creación de soldado P90 del cliente.
     *
     * @return Un puntero compartido a la acción de creación de soldado P90 recibida.
     */
    uint8_t receiveSmallUnsignedInt();
    /**
     * @brief Recibe un entero sin signo de 32 bits del cliente.
     *
     * @return El entero sin signo de 32 bits recibido.
     */
    uint32_t receieveUnsignedInteger();

    /**
     * @brief Recibe un entero de 8 bits del cliente.
     *
     * @return El entero de 8 bits recibido.
     */
    int8_t receiveSmallInt();

    /**
     * @brief Convierte un entero sin signo de 8 bits en un modo de juego.
     *
     * @param game_mode El entero sin signo de 8 bits que representa el modo de juego.
     * @return El modo de juego correspondiente.
     */
    GameMode intToGameMode(uint8_t game_mode);


    public:
    /**
     * @brief Constructor de la clase `ServerProtocol`.
     *
     * @param socket El socket para la comunicación con el cliente.
     */
    explicit ServerProtocol(Socket socket);

    /**
     * @brief Recibe una comando con la acción del cliente.
     *
     * @return Un puntero compartido a la acción recibida.
     */
    std::shared_ptr<Action> receiveAction();

    /**
     * @brief Recibe un comando del cliente.
     *
     * @return El comando recibido.
     */
    command_t receiveCommand();

    /**
     * @brief Envía el ID de la sala al cliente.
     *
     * @param room_id El ID de la sala.
     */
    void sendRoomId(uint32_t room_id);

    /**
     * @brief Envía una respuesta de unión al cliente.
     *
     * @param accepted Indica si se aceptó la unión.
     */
    void sendJoinResponse(bool accepted);

    /**
     * @brief Envía el modo de juego al cliente.
     *
     * @param game_mode El modo de juego.
     */
    void sendGameMode(GameMode game_mode);

    /**
     * @brief Envía el estado del juego al cliente.
     *
     * @param game_state El estado del juego para enviar.
     */
    void sendGameState(std::shared_ptr<GameStateForClient> game_state);

    /**
     * @brief Verifica si la comunicación con el cliente ha finalizado.
     *
     * @return `true` si la comunicación ha finalizado, `false` de lo contrario.
     */
    bool isFinished();

    /**
     * @brief Cierra el socket de comunicación con el cliente.
     */
    void closeSocket();
};
#endif
