#ifndef TIME_H
#define TIME_H

#include <QThread>

class TimeThread : public QThread
{
    Q_OBJECT

public:
    static TimeThread* getInst();
    virtual  ~TimeThread();
    void inittime();

signals:
    void timerUpdate(QString str);

protected:
    virtual void run();

private:
    explicit TimeThread(QObject *parent = 0);
};
#endif // TIME_H
