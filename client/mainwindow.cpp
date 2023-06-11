#include "mainwindow.h"
#include "ui_mainwindow.h"


#include <QDebug>

MainWindow::MainWindow(QWidget *parent, COMMANDS* commands, command_t* final_command) :
    QDialog(parent),
    ui(new Ui::MainWindow)
{
    qDebug() << "MainWindow::MainWindow -- final_command is " << final_command;
    choose_soldier = new ChooseSoldier(this, commands, final_command);
    connect(choose_soldier, &ChooseSoldier::closeWindows, this, &MainWindow::handleClosingWindows);

    ui->setupUi(this);
    join_match = new JoinMatch(this, choose_soldier, commands, final_command);
    qDebug() << "MainWindow::MainWindow -- final_command is " << final_command;
    create_match = new CreateMatch(this, choose_soldier, commands, final_command);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete join_match;
    delete create_match;
}

ChooseSoldier* MainWindow::getChooseSoldier() {
    return choose_soldier;
}

JoinMatch* MainWindow::getJoinMatch() {
    return join_match;
}

CreateMatch* MainWindow::getCreateMatch() {
    return create_match;
}

void MainWindow::on_newMatch_clicked()
{
    //Me muevo a la siguiente pantalla:
    create_match->setModal(true);
    create_match->exec();
}


void MainWindow::on_joinMatch_clicked()
{
    join_match->setModal(true);
    join_match->exec();
}

void MainWindow::handleClosingWindows() {
    create_match->close();
    join_match->close();
    choose_soldier->close();

    this->close();
}
