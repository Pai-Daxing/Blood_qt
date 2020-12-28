#ifndef BTTHREAD_H
#define BTTHREAD_H

#include <QThread>

class BtThread: public QThread
{
    Q_OBJECT

public:
    explicit BtThread(QObject *parent = 0);
    static BtThread* getInst();
    virtual  ~BtThread();

signals:
    void stopButtonPressed();

protected:
    virtual void run();

private:


    int keys_fd;
};


#endif // BTTHREAD_H
