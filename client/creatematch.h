#ifndef CREATEMATCH_H
#define CREATEMATCH_H

#include <QDialog>
#include <QMessageBox>
#include <QString>

#include "choosesoldier.h"
#include "client_protocol.h"

namespace Ui {
class CreateMatch;
}

class CreateMatch : public QDialog
{
    Q_OBJECT

public:
    explicit CreateMatch(QWidget *parent = nullptr, ChooseSoldier* choose_soldier = nullptr, 
                        COMMANDS* commands = nullptr, command_t* final_command = nullptr);
    ~CreateMatch();

signals:
    void matchInfoEntered(QString match_name, int mode_code, COMMANDS* commands, command_t* final_command);
    void resetCommand(COMMANDS* commands, command_t* final_command);

private slots:
    void on_dial_valueChanged(int value);

    void on_cancel_clicked();

    void on_choose_skin_clicked();

private:
    Ui::CreateMatch *ui;

    QString initial_match_name;
    int initial_dial_value;
    ChooseSoldier* choose_soldier;

    COMMANDS* commands;
    command_t* final_command;
};

#endif // CREATEMATCH_H
