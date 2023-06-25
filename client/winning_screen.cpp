#include "winning_screen.h"
#include "ui_winning_screen.h"

WinningScreen::WinningScreen(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WinningScreen)
{
    ui->setupUi(this);
    setWindowTitle("You won!");
    ui->ranking->setVisible(true);
}

void WinningScreen::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Q || event->key() == Qt::Key_Escape)
        close();
}


void WinningScreen::on_ranking_clicked()
{
    RankingClearTheZone ranking;
    ranking.setModal(true);
    ranking.exec();
}

WinningScreen::~WinningScreen()
{
    delete ui;
}
