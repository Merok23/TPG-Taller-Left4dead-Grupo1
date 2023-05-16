#include "joinmatch.h"
#include "ui_joinmatch.h"

JoinMatch::JoinMatch(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::JoinMatch)
{
    ui->setupUi(this);
    setWindowTitle(tr("Join match"));
}

JoinMatch::~JoinMatch()
{
    delete ui;
}

void JoinMatch::on_buttonBox_accepted()
{
    QMessageBox::information(this, "Joining match", "Joined match successfully. You can close this window now.");
}


void JoinMatch::on_buttonBox_rejected()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Joining match", "Are you sure you want to cancel?", QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        close();
    }
}
