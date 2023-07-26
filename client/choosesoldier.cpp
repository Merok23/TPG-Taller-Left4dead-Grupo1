#include "choosesoldier.h"
#include "ui_choosesoldier.h"

ChooseSoldier::ChooseSoldier(QWidget *parent, COMMANDS* commands, command_t* player_command) :
    QDialog(parent),
    ui(new Ui::ChooseSoldier)
{
    ui->setupUi(this);
    radio_buttons_checked = false;
    this->player_command = player_command;
    this->commands = commands;
    setWindowTitle(tr("Choose Soldier"));
    this->initial_player_name = ui->player_name_input->toPlainText();
}

ChooseSoldier::~ChooseSoldier()
{
    delete ui;
}

void ChooseSoldier::on_start_game_clicked()
{
    QString soldier_weapon;
    QList<QRadioButton *> radioButtons = ui->soldier_box->findChildren<QRadioButton *>(); // Get all radio buttons in the groupBox
    for (auto radioButton : radioButtons) {
        if (radioButton->isChecked()) { // Check if the radio button is checked
            radio_buttons_checked = true; // If at least one is checked, set the flag to false and break out of the loop
            soldier_weapon = radioButton->text();
            break;
        }
    }

    if (!radio_buttons_checked ||
        ui->player_name_input->toPlainText() == initial_player_name) {
        QMessageBox::warning(this, "Choosing Soldier", "Please choose a soldier to represent you in battle and give him a name");
    }
    else {
        emit soldierChosen(soldier_weapon, ui->player_name_input->toPlainText(), this->commands, this->player_command);
        emit closeWindows();
    }
}


void ChooseSoldier::on_cancel_clicked()
{
    close();
}
