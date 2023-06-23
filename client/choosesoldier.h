#ifndef CHOOSESOLDIER_H
#define CHOOSESOLDIER_H

#include <QDialog>
#include <QMessageBox>
#include "client_protocol.h"

namespace Ui {
class ChooseSoldier;
}

class ChooseSoldier : public QDialog
{
    Q_OBJECT

public:
    explicit ChooseSoldier(QWidget *parent = nullptr, COMMANDS* commands = nullptr, 
                            command_t* player_command = nullptr);
    ~ChooseSoldier();

signals:
    void soldierChosen(QString soldier_name, COMMANDS* command, command_t* player_command);
    void closeWindows();

private slots:
    void on_start_game_clicked();

    void on_cancel_clicked();

private:
    Ui::ChooseSoldier *ui;
    bool radio_buttons_checked;

    QString match_name;
    int mode_code;
    int match_code;

    COMMANDS* commands;
    command_t* player_command;
};

#endif // CHOOSESOLDIER_H