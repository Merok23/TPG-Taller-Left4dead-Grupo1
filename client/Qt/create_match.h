#ifndef CREATE_MATCH_H
#define CREATE_MATCH_H

#include <QDialog>

namespace Ui {
class SecondDialog;
}

class SecondDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SecondDialog(QWidget *parent = nullptr);
    ~SecondDialog();

private slots:
    void on_dial_valueChanged(int value);

    void on_buttonBox_rejected();

    void on_buttonBox_accepted();

private:
    Ui::SecondDialog *ui;
    QString initial_match_name;
    int initial_dial_value;
    bool radio_buttons_checked;
};

#endif // CREATE_MATCH_H
