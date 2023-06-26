#ifndef RANKING_CLEARTHEZONE_H
#define RANKING_CLEARTHEZONE_H

#include <QDialog>
#include <QKeyEvent>
#include "game_state.h"
#include "graphics.h"

namespace Ui {
class RankingClearTheZone;
}

class RankingClearTheZone : public QDialog
{
    Q_OBJECT

public:
    explicit RankingClearTheZone(QWidget *parent = nullptr, EndingInfo *ending_info = nullptr);
    void keyPressEvent(QKeyEvent *event) override;
    ~RankingClearTheZone();

private:
    Ui::RankingClearTheZone *ui;
    EndingInfo *ending_info;
};

#endif // RANKING_CLEARTHEZONE_H
