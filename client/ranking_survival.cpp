#include "ranking_survival.h"
#include "ui_ranking_survival.h"

#include <QDebug>
#include <list>

RankingSurvival::RankingSurvival(QWidget *parent, EndingInfo *ending_info) :
    QDialog(parent),
    ui(new Ui::RankingSurvival),
    ending_info(ending_info)
{
    ui->setupUi(this);
    setWindowTitle("Ranking in Survival Mode");

    ui->amount_infcted_killed->setText(QString::number(ending_info->last_gs->statistics.getInfectedKilledInfo().second));
    ui->bullets_shot->setText(QString::number(ending_info->last_gs->statistics.getAmmoUsedInfo().second));
    ui->gameplay_duration->setText(QString::number(ending_info->last_gs->statistics.getGameTimeInfo().second) + " s");


    adding_ranking();
}

void RankingSurvival::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Q || event->key() == Qt::Key_Escape)
        close();
}

int layout_total = 0;
void RankingSurvival::adding_ranking() {
    setting_up_ranking(ending_info->last_gs->statistics.top_infected_kills, QString("Infected Kills"));
    setting_up_ranking(ending_info->last_gs->statistics.top_ammo_used, QString("Ammo Used"));
    setting_up_ranking(ending_info->last_gs->statistics.top_time_alive, QString("Game Duration"));
}

void RankingSurvival::setting_up_ranking(std::list<uint32_t>& list_ranking, QString title) {
    QVBoxLayout *layout = new QVBoxLayout();
    qDebug() << "entro con " << title;
    int rank = 1;

    QLabel *title_qlabel = new QLabel(title);
    title_qlabel->setAlignment(Qt::AlignHCenter);  // Set alignment to center
    QFont font;
    font.setPointSize(13); // Set the font size to 15 points
    title_qlabel->setFont(font);
    layout->addWidget(title_qlabel);

    for (const auto& element : list_ranking) {
        if (element != 0) {
            QLabel *label = new QLabel(QString::number(rank) + QChar(0x00B0) + " place -- " + QString::number(element));
            label->setAlignment(Qt::AlignHCenter);  // Set alignment to center
            layout->addWidget(label);
            ++rank;
        }
    }

    ui->verticalLayout->addLayout(layout);
    int layoutCount = ui->verticalLayout->count();
    if (layoutCount == layout_total+1) {
        qDebug() << "Layout added to ui->verticalLayout";
        layout_total++;
    } else {
        qDebug() << "Failed to add layout to ui->verticalLayout";
    }
    QSpacerItem *spacerItem = new QSpacerItem(20, 45, QSizePolicy::Minimum, QSizePolicy::Expanding);
    ui->verticalLayout->addSpacerItem(spacerItem);
}

RankingSurvival::~RankingSurvival()
{
    delete ui;
}

