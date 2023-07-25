#include "losing_screen.h"
#include "ui_losing_screen.h"

LosingScreen::LosingScreen(QWidget *parent, EndingInfo *ending_info) :
    QMainWindow(parent),
    ui(new Ui::LosingScreen),
    ending_info(ending_info)
{
    ui->setupUi(this);
    setWindowTitle("You lost!");
    ui->ranking->setVisible(true);
    if (ending_info->game_mode == TESTING || !ending_info->last_gs)
        ui->ranking->setVisible(false);
    
    setWindowIcon(QIcon(":/imgs/Left4Dead.png"));
}

void LosingScreen::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Q || event->key() == Qt::Key_Escape)
        close();
}

void LosingScreen::on_ranking_clicked()
{
    if (ending_info->last_gs && ending_info->game_mode == CLEAR_THE_ZONE) {
        RankingClearTheZone ranking(nullptr, ending_info);
        ranking.setModal(true);
        ranking.exec();
    } else if (ending_info->last_gs && ending_info->game_mode == SURVIVAL) {
        RankingSurvival ranking(nullptr, ending_info);
        ranking.setModal(true);
        ranking.exec();
    }
}

LosingScreen::~LosingScreen()
{
    delete ui;
}
