#ifndef LOSING_SCREEN_H
#define LOSING_SCREEN_H

#include <QMainWindow>
#include <QKeyEvent>
#include "ranking_clearthezone.h"
#include "ranking_survival.h"
#include "graphics.h"

namespace Ui {
class LosingScreen;
}

class LosingScreen : public QMainWindow
{
    Q_OBJECT

public:
    explicit LosingScreen(QWidget *parent = nullptr, EndingInfo *ending_info = nullptr);
    ~LosingScreen();

    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void on_ranking_clicked();

private:
    Ui::LosingScreen *ui;
    EndingInfo *ending_info;
};

#endif // LOSING_SCREEN_H
