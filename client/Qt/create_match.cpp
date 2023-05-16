#include "create_match.h"
#include "ui_seconddialog.h"
#include <QMessageBox>

SecondDialog::SecondDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SecondDialog)
{
    ui->setupUi(this);
    setWindowTitle(tr("Create match"));

    initial_match_name = ui->lineEdit->text();
    initial_dial_value = ui->dial->value();
    radio_buttons_checked = false;
}

SecondDialog::~SecondDialog()
{
    delete ui;
}

void SecondDialog::on_dial_valueChanged(int value)
{
    QString message;
    switch (value) {
    case 0:
        message = "0 - For little children";
        break;
    case 1:
        message = "1 - Easy";
        break;
    case 2:
        message = "2 - Difficult";
        break;
    case 3:
        message = "3 - Are you crazy?";
        break;
    case 4:
        message = "4 - Nightmare";
        break;
        // add more cases for each option
    }
    ui->label_show_dif->setText(message);
}


void SecondDialog::on_buttonBox_rejected()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Creating new match", "Are you sure you want to cancel?", QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        close();
    }
}


void SecondDialog::on_buttonBox_accepted()
{
    QList<QRadioButton *> radioButtons = ui->groupBox_radio_buttons->findChildren<QRadioButton *>(); // Get all radio buttons in the groupBox
    for (auto radioButton : radioButtons) {
        if (radioButton->isChecked()) { // Check if the radio button is checked
            radio_buttons_checked = true; // If at least one is checked, set the flag to false and break out of the loop
            break;
        }
    }

    if (ui->lineEdit->text() == initial_match_name ||
        ui->dial->value() == initial_dial_value ||
        !radio_buttons_checked) {
        QMessageBox::warning(this, "Creating new match", "Please fill out every required (*) field");
    }

    else {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Creating new match", "Are you sure you want to create the new match?", QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes) {

            QMessageBox::information(this, "Creating new match", "Creation of match successful. You can close this window now.");
        }
    }
}

