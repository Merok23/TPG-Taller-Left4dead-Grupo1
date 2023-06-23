#include "winning_screen.h"
#include "ui_winning_screen.h"

WinningScreen::WinningScreen(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WinningScreen)
{
    ui->setupUi(this);
    setWindowTitle("You won!");
}

WinningScreen::~WinningScreen()
{
    delete ui;
}
