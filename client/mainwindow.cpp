#include "mainwindow.h"
#include "ui_mainwindow.h"


#include <QDebug>

MainWindow::MainWindow(QWidget *parent, COMMANDS* commands, command_t* create_or_join_command, command_t* player_command) :
    QDialog(parent),
    ui(new Ui::MainWindow)
{
    choose_soldier = new ChooseSoldier(this, commands, player_command);
    connect(choose_soldier, &ChooseSoldier::closeWindows, this, &MainWindow::handleClosingWindows);

    ui->setupUi(this);
    join_match = new JoinMatch(this, choose_soldier, commands, create_or_join_command);
    create_match = new CreateMatch(this, choose_soldier, commands, create_or_join_command);

    setWindowTitle(tr("Left 4 Dead"));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete join_match;
    delete create_match;
    delete choose_soldier;
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