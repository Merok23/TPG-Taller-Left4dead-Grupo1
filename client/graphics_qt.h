#ifndef __GRAPHICS_QT_H__
#define __GRAPHICS_QT_H__

#include <QApplication>
#include <QDebug>
#include "mainwindow.h"
#include "client_enum.h"
#include "client_protocol.h"

class GraphicsQt {
public:
    void run(COMMANDS* commands, command_t* create_or_join_command, command_t* player_command);
    
private:
};

#endif //__GRAPHICS_QT_H__
