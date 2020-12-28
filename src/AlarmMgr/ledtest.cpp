#include "ledtest.h"
#include "ui_ledtest.h"

ledtest::ledtest(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ledtest)
{
    ui->setupUi(this);
}

ledtest::~ledtest()
{
    delete ui;
}
