#ifndef WINNING_SCREEN_H
#define WINNING_SCREEN_H

#include <QMainWindow>

namespace Ui {
class WinningScreen;
}

class WinningScreen : public QMainWindow
{
    Q_OBJECT

public:
    explicit WinningScreen(QWidget *parent = nullptr);
    ~WinningScreen();

private:
    Ui::WinningScreen *ui;
};

#endif // WINNING_SCREEN_H
