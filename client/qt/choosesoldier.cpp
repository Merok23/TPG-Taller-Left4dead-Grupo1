#include "choosesoldier.h"
#include "ui_choosesoldier.h"

ChooseSoldier::ChooseSoldier(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChooseSoldier)
{
    ui->setupUi(this);
    radio_buttons_checked = false;
}

ChooseSoldier::~ChooseSoldier()
{
    delete ui;
}

//QMessageBox::information(this, "Creating new match", "Creation of match successful. You can close this window now.");

void ChooseSoldier::on_start_game_clicked()
{
    QString soldier_name;
    QList<QRadioButton *> radioButtons = ui->soldier_box->findChildren<QRadioButton *>(); // Get all radio buttons in the groupBox
    for (auto radioButton : radioButtons) {
        if (radioButton->isChecked()) { // Check if the radio button is checked
            radio_buttons_checked = true; // If at least one is checked, set the flag to false and break out of the loop
            soldier_name = radioButton->text();
            break;
        }
    }

    if (!radio_buttons_checked) {
        QMessageBox::warning(this, "Choosing Soldier", "Please choose a soldier to represent you in battle");
    }
    else {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Choosing Soldier", "Are you sure you want to start the game?", QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            emit soldierChosen(soldier_name);
            emit closeWindows();
        }
    }
}


void ChooseSoldier::on_cancel_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Choosing Soldier", "Are you sure you want to cancel?", QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        close();
    }
}

