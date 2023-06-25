#include "ranking_clearthezone.h"
#include "ui_ranking_clearthezone.h"

RankingClearTheZone::RankingClearTheZone(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RankingClearTheZone)
{
    ui->setupUi(this);
    setWindowTitle("Ranking in Clear the Zone Mode");

    ui->amount_infcted_killed->setText(QString::number(5));
    ui->bullets_shot->setText(QString::number(200));
    ui->gameplay_duration->setText(QString::number(10000) + " ms");

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
