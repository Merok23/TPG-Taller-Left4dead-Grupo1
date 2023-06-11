#ifndef CREATEMATCH_H
#define CREATEMATCH_H

#include <QDialog>
#include <QMessageBox>
#include <QString>
#include "choosesoldier.h"

namespace Ui {
class CreateMatch;
}

class CreateMatch : public QDialog
{
    Q_OBJECT

public:
    explicit CreateMatch(QWidget *parent = nullptr, ChooseSoldier* choose_soldier = nullptr, int* i = nullptr);
    ~CreateMatch();

signals:
    void matchInfoEntered(QString match_name, int mode_code);
    void resetCommand(int* i);

private slots:
    void on_dial_valueChanged(int value);

    void on_cancel_clicked();

    void on_choose_skin_clicked();

private:
    Ui::CreateMatch *ui;

    QString initial_match_name;
    int initial_dial_value;
    ChooseSoldier* choose_soldier;

    int* i;
};

#endif // CREATEMATCH_H
