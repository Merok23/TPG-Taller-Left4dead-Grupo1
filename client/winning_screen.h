#ifndef WINNING_SCREEN_H
#define WINNING_SCREEN_H

#include <QMainWindow>
#include <QKeyEvent>

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
    
private:
    Ui::WinningScreen *ui;
};

#endif // WINNING_SCREEN_H
