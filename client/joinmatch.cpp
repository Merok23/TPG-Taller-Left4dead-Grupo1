#include "joinmatch.h"
#include "ui_joinmatch.h"

#include <QDebug>

JoinMatch::JoinMatch(QWidget *parent, ChooseSoldier* choose_soldier, COMMANDS* commands, command_t* create_or_join_command) :
    QDialog(parent)
{
    ui = new Ui::JoinMatch;
    ui->setupUi(this);

    //only allow numbers in the match code
    validator = new QRegExpValidator(QRegExp("[0-9]*"), this);
    ui->match_code_input->setValidator(validator);

    QString text = ui->match_code_input->text();
    this->initial_match_code = text.toInt();
    this->commands = commands;
    this->create_or_join_command = create_or_join_command;
    this->choose_soldier = choose_soldier;

    setWindowTitle(tr("Join Match"));
}

JoinMatch::~JoinMatch()
{
    delete ui;
    delete validator;
}

void JoinMatch::on_cancel_clicked()
{
    emit resetCommand(this->commands, this->create_or_join_command);
    close();
}


void JoinMatch::on_choose_skin_clicked()
{
    //Validating data

    QString text = ui->match_code_input->text();
    int match_code_input = text.toInt();

    if (match_code_input == this->initial_match_code) {
        QMessageBox::warning(this, "Creating new match", "Please fill out all fields");
    } else {
        emit matchCodeEntered(match_code_input, this->commands, this->create_or_join_command);
        choose_soldier->setModal(true);
        choose_soldier->exec();
    }
}
