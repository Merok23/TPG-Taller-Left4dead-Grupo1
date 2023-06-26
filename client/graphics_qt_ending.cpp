#include "graphics_qt_ending.h"

void GraphicsQtEnding::run(EndingInfo ending_info) {
    int argc = 0;
    char* argv[1];
    QApplication a(argc, argv);

    if (ending_info.user_won) {
        WinningScreen ws(nullptr, &ending_info);
        ws.show();
        a.exec();
    } else {
        LosingScreen ls(nullptr, &ending_info);
        ls.show();
        a.exec();
    }
}
