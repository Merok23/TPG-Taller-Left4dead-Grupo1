#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>
#include "creatematch.h"
#include "joinmatch.h"
#include "choosesoldier.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QDialog
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr, int* i = nullptr);
    ~MainWindow();

    ChooseSoldier* getChooseSoldier();
    CreateMatch* getCreateMatch();
    JoinMatch* getJoinMatch();
    bool joiningMatch();

    void handleClosingWindows();

private slots:
    void on_newMatch_clicked();
    void on_joinMatch_clicked();

private:
    Ui::MainWindow *ui;
    ChooseSoldier* choose_soldier;
    JoinMatch* join_match;
    CreateMatch* create_match;
};

#endif // MAINWINDOW_H
