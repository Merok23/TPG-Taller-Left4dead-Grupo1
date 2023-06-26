#include "winning_screen.h"
#include "ui_winning_screen.h"

WinningScreen::WinningScreen(QWidget *parent, EndingInfo *ending_info) :
    QMainWindow(parent),
    ui(new Ui::WinningScreen),
    ending_info(ending_info)
{
    ui->setupUi(this);
    setWindowTitle("You won!");
    ui->ranking->setVisible(true);
    if (ending_info->game_mode == TESTING)
        ui->ranking->setVisible(false);
}

void WinningScreen::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Q || event->key() == Qt::Key_Escape)
        close();
}


void WinningScreen::on_ranking_clicked()
{
    if (ending_info->game_mode == CLEAR_THE_ZONE) {
        RankingClearTheZone ranking(nullptr, ending_info);
        ranking.setModal(true);
        ranking.exec();
    } else if (ending_info->game_mode == SURVIVAL) {
        RankingSurvival ranking(nullptr, ending_info);
        ranking.setModal(true);
        ranking.exec();
    }
}

WinningScreen::~WinningScreen()
{
    delete ui;
}
