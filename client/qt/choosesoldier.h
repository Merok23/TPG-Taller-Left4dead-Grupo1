#ifndef CHOOSESOLDIER_H
#define CHOOSESOLDIER_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class ChooseSoldier;
}

class ChooseSoldier : public QDialog
{
    Q_OBJECT

public:
    explicit ChooseSoldier(QWidget *parent = nullptr);
    ~ChooseSoldier();

signals:
    void soldierChosen(QString soldier_name);
    void closeWindows();

private slots:
    void on_start_game_clicked();

    void on_cancel_clicked();

private:
    Ui::ChooseSoldier *ui;
    bool radio_buttons_checked;

    QString match_name;
    int mode_code;
    int match_code;
};

#endif // CHOOSESOLDIER_H
