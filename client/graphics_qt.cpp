#include "graphics_qt.h"

void GraphicsQt::run(COMMANDS* commands, command_t* create_or_join_command, command_t* player_command) {
    int argc = 0;
    char* argv[1];
    QApplication app(argc, argv);

    MainWindow main_window(nullptr, commands, create_or_join_command, player_command);
    main_window.show();
    JoinMatch* joinMatch = main_window.getJoinMatch();

    // Establish connection between JoinMatch and main.cpp
    QObject::connect(joinMatch, &JoinMatch::matchCodeEntered, [](int code, COMMANDS* commands, 
                                                                command_t* create_or_join_command) {
        if (commands && create_or_join_command) {
            *create_or_join_command = commands->joinRoom(code);
        }
        // Process the match code in main.cpp
    });

    QObject::connect(joinMatch, &JoinMatch::resetCommand, [](COMMANDS* commands, command_t* create_or_join_command) {
        
    });


    CreateMatch* createMatch = main_window.getCreateMatch();

    // Establish connection between JoinMatch and main.cpp
    QObject::connect(createMatch, &CreateMatch::matchInfoEntered, [](QString match_name, int mode_code, COMMANDS* commands, 
                                                                        command_t* create_or_join_command) {
        qDebug() << "Match name entered in main.cpp:" << match_name << " and mode: " <<mode_code;
        if (commands && create_or_join_command) {
            switch(mode_code) {
                case 1: //testing
                *create_or_join_command = commands->createRoom(match_name.toStdString(), GameMode::TESTING);
                break;
                case 2: //surviving
                *create_or_join_command = commands->createRoom(match_name.toStdString(), GameMode::SURVIVAL);
                break;
                case 3: //clear the zone
                *create_or_join_command = commands->createRoom(match_name.toStdString(), GameMode::CLEAR_THE_ZONE);
                break;
            }
           // qDebug() << "command->code ahora vale " << command->code;
        }
        // Process the match code in main.cpp
    });

    QObject::connect(createMatch, &CreateMatch::resetCommand, [](COMMANDS* commands, command_t* create_or_join_command) {
        
    });


    ChooseSoldier* chooseSoldier = main_window.getChooseSoldier();

    // Establish connection between JoinMatch and main.cpp
    QObject::connect(chooseSoldier, &ChooseSoldier::soldierChosen, [](QString soldier_name, COMMANDS* commands, command_t* player_command) {
        qDebug() << "Match name entered in main.cpp:" << soldier_name;
        if (commands && player_command) {
            *player_command = commands->addPlayer(soldier_name.toStdString());
        }// Process the match code in main.cpp
    });

    app.exec();;
}
