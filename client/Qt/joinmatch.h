#ifndef JOINMATCH_H
#define JOINMATCH_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class JoinMatch;
}

class JoinMatch : public QDialog
{
    Q_OBJECT

public:
    explicit JoinMatch(QWidget *parent = nullptr);
    ~JoinMatch();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::JoinMatch *ui;
};

#endif // JOINMATCH_H
