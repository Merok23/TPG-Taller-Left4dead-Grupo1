#include "losing_screen.h"
#include "ui_losing_screen.h"

LosingScreen::LosingScreen(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LosingScreen)
{
    ui->setupUi(this);
    setWindowTitle("You lost!");
}

LosingScreen::~LosingScreen()
{
    delete ui;
}
