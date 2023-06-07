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
            protocol.sendCommand(command);
            if (protocol.isFinished()) {
                stop(); 
                break; 
            }
        } catch(const ClosedQueue &e) {
            if (finished) return; 
            std::cerr << "Error: " << e.what() << std::endl;
            finished = true;
        } catch (const LibError &e) {
            std::cerr << "Error: " << e.what() << std::endl;
            finished = true;
        }
    }
}

void SendThread::stop() {
    finished = true;
}

