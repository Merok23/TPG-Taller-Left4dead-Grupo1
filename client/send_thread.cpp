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
                protocol.sendAddPlayer();
            } else if (action == "move") {
                int x, y;
                iss >> x >> y;
                protocol.sendMoving(x, y); 
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

