#ifndef RANKING_CLEARTHEZONE_H
#define RANKING_CLEARTHEZONE_H

#include <QDialog>
#include <QKeyEvent>

namespace Ui {
class RankingClearTheZone;
}

class RankingClearTheZone : public QDialog
{
    Q_OBJECT

public:
    explicit RankingClearTheZone(QWidget *parent = nullptr);
    void keyPressEvent(QKeyEvent *event) override;
    ~RankingClearTheZone();

private:
    Ui::RankingClearTheZone *ui;
};

#endif // RANKING_CLEARTHEZONE_H
