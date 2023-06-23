#ifndef LOSING_SCREEN_H
#define LOSING_SCREEN_H

#include <QMainWindow>

namespace Ui {
class LosingScreen;
}

class LosingScreen : public QMainWindow
{
    Q_OBJECT

public:
    explicit LosingScreen(QWidget *parent = nullptr);
    ~LosingScreen();

private:
    Ui::LosingScreen *ui;
};

#endif // LOSING_SCREEN_H
