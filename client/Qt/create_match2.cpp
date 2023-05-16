#include "create_match2.h"
#include "ui_create_match2.h"

create_match2::create_match2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::create_match2)
{
    ui->setupUi(this);
}

create_match2::~create_match2()
{
    delete ui;
}
