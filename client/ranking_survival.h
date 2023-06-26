#ifndef RANKING_SURVIVAL_H
#define RANKING_SURVIVAL_H

#include <QDialog>
#include <QKeyEvent>
#include <QVBoxLayout>
#include <QLabel>
#include <QFont>
#include <list>
#include "game_state.h"
#include "graphics.h"

namespace Ui {
class RankingSurvival;
}

class RankingSurvival : public QDialog
{
    Q_OBJECT

public:
    explicit RankingSurvival(QWidget *parent = nullptr, EndingInfo *ending_info = nullptr);
    ~RankingSurvival();


    void keyPressEvent(QKeyEvent *event) override;
    
private:
    Ui::RankingSurvival *ui;
    EndingInfo *ending_info;

    void adding_ranking();
    void setting_up_ranking(std::list<uint32_t>& list_ranking, QString title);
};

#endif // RANKING_SURVIVAL_H
