#ifndef __GRAPHICS_QT_H__
#define __GRAPHICS_QT_H__

#include <QApplication>
#include <QDebug>
#include "mainwindow.h"
#include "client_enum.h"
#include "client_protocol.h"

class GraphicsQt {
public:
    void run(COMMANDS* commands, command_t* final_command);
    
private:
};

#endif //__GRAPHICS_QT_H__
