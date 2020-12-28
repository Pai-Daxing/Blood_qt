#ifndef NETONLINE_H
#define NETONLINE_H


#include <QThread>

class NetOnline: public QThread
{
    Q_OBJECT

public:
    explicit NetOnline(QObject *parent = 0);
    static NetOnline* getInst();
    virtual  ~NetOnline();

signals:
    void netconnect();
    void netconnectfaild();

protected:
    virtual void run();

private:


    int keys_fd;
};
#endif // NETONLINE_H
