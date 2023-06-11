#include "joinmatch.h"
#include "ui_joinmatch.h"

#include <QDebug>

JoinMatch::JoinMatch(QWidget *parent, ChooseSoldier* choose_soldier, int* i) :
    QDialog(parent),
    ui(new Ui::JoinMatch),
    choose_soldier(choose_soldier)
{
    ui->setupUi(this);

    //only allow numbers in the match code
    QRegExpValidator* validator = new QRegExpValidator(QRegExp("[0-9]*"), this);
    ui->match_code_input->setValidator(validator);

    QString text = ui->match_code_input->text();
    this->initial_match_code = text.toInt();
    this->i = i;

    qDebug() << "*i vale" << *i;
}

JoinMatch::~JoinMatch()
{
    delete ui;
}

void JoinMatch::on_cancel_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Creating new match", "Are you sure you want to cancel?", QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        emit resetCommand(i);
        close();
    }
}


void JoinMatch::on_choose_skin_clicked()
{
    //Validating data

    QString text = ui->match_code_input->text();
    int match_code_input = text.toInt();

    if (match_code_input == this->initial_match_code) {
        QMessageBox::warning(this, "Creating new match", "Please fill out all fields");
    } else {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Creating new match", "Are you sure you want to move on to create new player?", QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            emit matchCodeEntered(match_code_input);
            choose_soldier->setModal(true);
            choose_soldier->exec();
        }
    }
}

