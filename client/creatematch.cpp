#include "creatematch.h"
#include "ui_creatematch.h"

CreateMatch::CreateMatch(QWidget *parent, ChooseSoldier* choose_soldier, 
                        COMMANDS* commands, command_t* create_or_join_command) :
    QDialog(parent),
    ui(new Ui::CreateMatch),
    choose_soldier(choose_soldier)
{
    ui->setupUi(this);
    setWindowTitle(tr("Create match"));


    initial_match_name = ui->match_name_input->toPlainText();
    initial_dial_value = 0;

    this->commands = commands;
    this->create_or_join_command = create_or_join_command;
}

CreateMatch::~CreateMatch()
{
    delete ui;
}

void CreateMatch::on_dial_valueChanged(int value)
{
    QString message;
    switch (value) {
    case 0:
        message = "Please select game mode.";
        break;
    case 1:
        message = "0 - Peaceful mode. \n\nNo enemies will be spawned. Just enjoy a stroll in an apocalyptic setting.";
        break;
    case 2:
        message = "1 - Survival mode. \n\nEnemies will spawn randomly. There is no end, just an endless challenge of endurance.";
        break;
    case 3:
        message = "2 - Clear the zone mode. \n\nA set number of enemies will spawn. If you and your party defeat all of them, you won.";
        break;
    }

    ui->mode_description->setText(message);
}


void CreateMatch::on_cancel_clicked()
{
    emit resetCommand(this->commands, this->create_or_join_command);
    close();
}


void CreateMatch::on_choose_skin_clicked()
{
    //Validating data
    if (ui->match_name_input->toPlainText() == initial_match_name ||
        ui->dial->value() == initial_dial_value) {
        QMessageBox::warning(this, "Creating new match", "Please fill out all fields");
    } else {
        emit matchInfoEntered(ui->match_name_input->toPlainText(), ui->dial->value(), this->commands, this->create_or_join_command);
        choose_soldier->setModal(true);
        choose_soldier->exec();
    }
}
