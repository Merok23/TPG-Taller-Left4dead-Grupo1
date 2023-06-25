#ifndef WINNING_SCREEN_H
#define WINNING_SCREEN_H

#include <QMainWindow>
#include <QKeyEvent>
#include "ranking_clearthezone.h"
#include "ranking_survival.h"

namespace Ui {
class WinningScreen;
}

class WinningScreen : public QMainWindow
{
    Q_OBJECT

public:
    explicit WinningScreen(QWidget *parent = nullptr);
    ~WinningScreen();

    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void on_ranking_clicked();
    
private:
    Ui::WinningScreen *ui;
};

#endif // WINNING_SCREEN_H
