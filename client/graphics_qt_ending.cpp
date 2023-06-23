#include "graphics_qt_ending.h"

void GraphicsQtEnding::run(bool user_won) {
    int argc = 0;
    char* argv[1];
    QApplication a(argc, argv);

    if (user_won) {
        WinningScreen ws;
        ws.show();
        a.exec();
    } else {
        LosingScreen ls;
        ls.show();
        a.exec();
    }
}
