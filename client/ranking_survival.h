#ifndef RANKING_SURVIVAL_H
#define RANKING_SURVIVAL_H

#include <QDialog>
#include <QKeyEvent>
#include <QVBoxLayout>
#include <QLabel>
#include <QFont>
#include <list>

namespace Ui {
class RankingSurvival;
}

class RankingSurvival : public QDialog
{
    Q_OBJECT

public:
    explicit RankingSurvival(QWidget *parent = nullptr);
    ~RankingSurvival();


    void keyPressEvent(QKeyEvent *event) override;
    
private:
    Ui::RankingSurvival *ui;

    void adding_ranking();
    void setting_up_ranking(std::list<std::pair<QString, int>>& list, QString title);
};

#endif // RANKING_SURVIVAL_H
