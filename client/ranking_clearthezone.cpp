#include "ranking_clearthezone.h"
#include "ui_ranking_clearthezone.h"

RankingClearTheZone::RankingClearTheZone(QWidget *parent, EndingInfo *ending_info) :
    QDialog(parent),
    ui(new Ui::RankingClearTheZone),
    ending_info(ending_info)
{
    ui->setupUi(this);
    setWindowTitle("Ranking in Clear the Zone Mode");

    ui->amount_infcted_killed->setText(QString::number(ending_info->last_gs->statistics.getInfectedKilledInfo().second));
    ui->bullets_shot->setText(QString::number(ending_info->last_gs->statistics.getAmmoUsedInfo().second));
    ui->gameplay_duration->setText(QString::number(ending_info->last_gs->statistics.getGameTimeInfo().second) + " ms");

}

void RankingClearTheZone::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Q || event->key() == Qt::Key_Escape)
        close();
}


RankingClearTheZone::~RankingClearTheZone()
{
    delete ui;
}
