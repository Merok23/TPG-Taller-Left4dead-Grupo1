#ifndef CREATE_MATCH2_H
#define CREATE_MATCH2_H

#include <QDialog>

namespace Ui {
class create_match2;
}

class create_match2 : public QDialog
{
    Q_OBJECT

public:
    explicit create_match2(QWidget *parent = nullptr);
    ~create_match2();

private:
    Ui::create_match2 *ui;
};

#endif // CREATE_MATCH2_H
