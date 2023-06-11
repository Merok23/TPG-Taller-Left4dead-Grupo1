#ifndef JOINMATCH_H
#define JOINMATCH_H

#include <QDialog>
#include <QRegExpValidator>
#include <QMessageBox>

#include "choosesoldier.h"
#include "client_protocol.h"


namespace Ui {
class JoinMatch;
}

class JoinMatch : public QDialog
{
    Q_OBJECT

public:
    explicit JoinMatch(QWidget *parent = nullptr, ChooseSoldier* choose_soldier = nullptr, 
                        COMMANDS* commands = nullptr, command_t* final_command = nullptr);
    ~JoinMatch();

signals:
    void matchCodeEntered(int code, COMMANDS* commands, command_t* final_command);
    void resetCommand(COMMANDS* commands, command_t* final_command);

private slots:
    void on_cancel_clicked();

    void on_choose_skin_clicked();

private:
    Ui::JoinMatch *ui;
    int initial_match_code;
    ChooseSoldier* choose_soldier;
    COMMANDS* commands;
    command_t* final_command;
};

#endif // JOINMATCH_H
