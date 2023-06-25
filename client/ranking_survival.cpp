#include "ranking_survival.h"
#include "ui_ranking_survival.h"

RankingSurvival::RankingSurvival(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RankingSurvival)
{
    ui->setupUi(this);
    setWindowTitle("Ranking in Survival Mode");
    ui->amount_infcted_killed->setText(QString::number(5));
    ui->bullets_shot->setText(QString::number(200));
    ui->gameplay_duration->setText(QString::number(10000) + " ms");


    adding_ranking();
}

void RankingSurvival::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Q || event->key() == Qt::Key_Escape)
        close();
}

void RankingSurvival::adding_ranking() {
    std::list<std::pair<QString, int>> listInfectedKillsTop10;
    std::list<std::pair<QString, int>> listAmmoUsedTop10;
    std::list<std::pair<QString, int>> listTimeAliveTop10;


    // Populate the lists with sample data
    listInfectedKillsTop10 = {
        {"user1", 55},
        {"user32", 40},
        {"user15", 37}
    };

    listAmmoUsedTop10 = {
        {"user2", 200},
        {"user4", 150},
        {"user1", 128}
    };

    listTimeAliveTop10 = {
        {"user2", 1000},
        {"user4", 780},
        {"user1", 600}
    };

    setting_up_ranking(listInfectedKillsTop10, QString("Infected Kills"));
    setting_up_ranking(listAmmoUsedTop10, QString("Ammo Used"));
    setting_up_ranking(listTimeAliveTop10, QString("Game Duration"));
}

void RankingSurvival::setting_up_ranking(std::list<std::pair<QString, int>>& list, QString title) {
    QVBoxLayout *layout = new QVBoxLayout();
    int rank = 1;

    QLabel *title_qlabel = new QLabel(title);
    title_qlabel->setAlignment(Qt::AlignHCenter);  // Set alignment to center
    QFont font;
    font.setPointSize(13); // Set the font size to 15 points
    title_qlabel->setFont(font);
    layout->addWidget(title_qlabel);


    for (const auto& user : list) {
        QLabel *label = new QLabel(QString::number(rank) + QChar(0x00B0) + " place -- " + QString::number(user.second));
        label->setAlignment(Qt::AlignHCenter);  // Set alignment to center
        layout->addWidget(label);
        ++rank;
    }

    ui->verticalLayout->addLayout(layout);
    QSpacerItem *spacerItem = new QSpacerItem(20, 45, QSizePolicy::Minimum, QSizePolicy::Expanding);
    ui->verticalLayout->addSpacerItem(spacerItem);
}

RankingSurvival::~RankingSurvival()
{
    delete ui;
}

