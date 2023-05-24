#include <sstream>
#include "send_thread.h"

SendThread::SendThread(ClientProtocol& protocol, Queue<std::string>& queue) : protocol(protocol), queue_comandos(queue), finished(false) {}

void SendThread::run() {
    std::string line = "";
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
                command_t command; 
                command.type = ADD_PLAYER;
                command.x_position = 0;
                command.y_position = 0;
                command.room_id = 0;
                command.room_name = "";
                protocol.sendCommand(command);
            } else if (action == "move") {
                int x, y;
                iss >> x >> y;
                command_t command; 
                command.type = MOVE_PLAYER;
                command.x_position = x;
                command.y_position = y;
                command.room_id = 0;
                command.room_name = "";
                protocol.sendCommand(command);
            }
        } catch(std::runtime_error& e) {
            std::string message = e.what();
            if (message.compare("The queue is closed") == 0) {
                finished = true;
            } 
        }
    }
}

void SendThread::stop() {
    finished = true;
}

