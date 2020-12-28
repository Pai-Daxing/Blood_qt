#ifndef LEDTEST_H
#define LEDTEST_H

#include <QWidget>

namespace Ui {
class ledtest;
}

class ledtest : public QWidget
{
    Q_OBJECT

public:
    explicit ledtest(QWidget *parent = 0);
    ~ledtest();

private:
    Ui::ledtest *ui;
};

#endif // LEDTEST_H
