#ifndef JOINMATCH_H
#define JOINMATCH_H

#include <QDialog>
#include <QRegExpValidator>
#include <QMessageBox>

#include "choosesoldier.h"

namespace Ui {
class JoinMatch;
}

class JoinMatch : public QDialog
{
    Q_OBJECT

public:
    explicit JoinMatch(QWidget *parent = nullptr, ChooseSoldier* choose_soldier = nullptr, int* i = nullptr);
    ~JoinMatch();

signals:
    void matchCodeEntered(int code);
    void resetCommand(int*);

private slots:
    void on_cancel_clicked();

    void on_choose_skin_clicked();

private:
    Ui::JoinMatch *ui;
    int initial_match_code;
    ChooseSoldier* choose_soldier;
    int* i;
};

#endif // JOINMATCH_H
