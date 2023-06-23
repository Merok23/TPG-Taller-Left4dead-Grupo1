#ifndef LOSING_SCREEN_H
#define LOSING_SCREEN_H

#include <QMainWindow>
#include <QKeyEvent>

namespace Ui {
class LosingScreen;
}

class LosingScreen : public QMainWindow
{
    Q_OBJECT

public:
    explicit LosingScreen(QWidget *parent = nullptr);
    ~LosingScreen();

    void keyPressEvent(QKeyEvent *event) override;


private:
    Ui::LosingScreen *ui;
};

#endif // LOSING_SCREEN_H
