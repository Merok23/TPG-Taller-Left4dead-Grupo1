#include <sstream>
#include <string>
#include "send_thread.h"

SendThread::SendThread(ClientProtocol& protocol, Queue<std::string>& queue) : 
    protocol(protocol), 
        queue_comandos(queue), 
            finished(false) {}

void SendThread::run() {
    std::string line;
    while (!finished) {
        try {
            line = queue_comandos.pop();
            if (protocol.isFinished()) {
                stop(); 
                break; 
            }
            std::istringstream iss(line);
            std::string action; 
            iss >> action;
            if (action == "create") {
                command_t command = command_t(); 
                command.type = ADD_PLAYER;
                protocol.sendCommand(command);
            } else if (action == "move") {
                // si presionan boton izqueirdo
                // "move -1 0"

                // si presionan boton derecho
                // move 1 0

                // si presionan boton arriba
                // move 0 1

                // si presionan boton abajo
                // move 0 -1

                // si dejan de presionar
                // move 0 0
                int x, y;
                iss >> x >> y;
                command_t command = command_t(); 
                command.type = MOVE_PLAYER;
                command.x_position = x;
                command.y_position = y;
                protocol.sendCommand(command);
            }
        } catch(const ClosedQueue &e) {
            if (finished) return; 
            std::cerr << "Error: " << e.what() << std::endl;
            finished = true;
        }
    }
}

void SendThread::stop() {
    finished = true;
}

