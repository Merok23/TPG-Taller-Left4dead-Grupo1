#include <sstream>
#include <string>
#include "send_thread.h"

SendThread::SendThread(ClientProtocol& protocol, Queue<command_t>& queue) : 
    protocol(protocol), 
        queue_comandos(queue), 
            finished(false) {}

void SendThread::run() {
    command_t command;
    while (!finished) {
        try {
            command = queue_comandos.pop();
            if (protocol.isFinished()) {
                stop(); 
                break; 
            }
            protocol.sendCommand(command);
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

