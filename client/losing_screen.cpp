#include "losing_screen.h"
#include "ui_losing_screen.h"

LosingScreen::LosingScreen(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LosingScreen)
{
    ui->setupUi(this);
    setWindowTitle("You lost!");
}

void LosingScreen::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Q || event->key() == Qt::Key_Escape)
        close();
}


LosingScreen::~LosingScreen()
{
    delete ui;
}
