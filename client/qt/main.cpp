#include <QApplication>
#include <QDebug>
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    int i = 1;
    MainWindow main_window(nullptr, &i);
    main_window.show();
    JoinMatch* joinMatch = main_window.getJoinMatch();

    // Establish connection between JoinMatch and main.cpp
    QObject::connect(joinMatch, &JoinMatch::matchCodeEntered, [](int code) {
        qDebug() << "Match code entered in main.cpp:" << code;
        // Process the match code in main.cpp
    });

    QObject::connect(joinMatch, &JoinMatch::resetCommand, [](int* i) {
        if (i) {
            *i = 2;
            qDebug() << "JoinMatch::resetCommand -- i ahora vale " << *i;
        }
    });


    CreateMatch* createMatch = main_window.getCreateMatch();

    // Establish connection between JoinMatch and main.cpp
    QObject::connect(createMatch, &CreateMatch::matchInfoEntered, [](QString match_name, int mode_code) {
        qDebug() << "Match name entered in main.cpp:" << match_name << " and mode: " <<mode_code;
        // Process the match code in main.cpp
    });

    QObject::connect(createMatch, &CreateMatch::resetCommand, [](int* i) {
        if (i) {
            *i = 3;
            qDebug() << "CreateMatch::resetCommand -- i ahora vale " << *i;
        }
    });


    ChooseSoldier* chooseSoldier = main_window.getChooseSoldier();

    // Establish connection between JoinMatch and main.cpp
    QObject::connect(chooseSoldier, &ChooseSoldier::soldierChosen, [](QString soldier_name) {
        qDebug() << "Match name entered in main.cpp:" << soldier_name;
        // Process the match code in main.cpp
    });

    return app.exec();;
}
