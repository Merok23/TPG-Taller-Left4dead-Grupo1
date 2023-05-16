#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(tr("Main Menu"));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    SecondDialog secDialog;
    secDialog.setModal(true);
    secDialog.exec();
}


void MainWindow::on_pushButton_2_clicked()
{
    JoinMatch joinMatch;
    joinMatch.setModal(true);
    joinMatch.exec();
}

