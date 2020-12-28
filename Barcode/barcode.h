#ifndef BARCODE_H
#define BARCODE_H

#include <QThread>
#include <QObject>

class QFile;

class BarcodeThread : public QThread
{
    Q_OBJECT

public:
    static BarcodeThread* getInst();
    virtual  ~BarcodeThread();

signals:
    void barcodeUpdate(QString str);

protected:
    virtual void run();

private:
    explicit BarcodeThread(QObject *parent = 0);
};
//class QKeyEvent;

//class Barcode : public QObject
//{
//    Q_OBJECT

//public:
//    static Barcode* getInst();
//    virtual  ~Barcode();

//    void keyPressEvent(QKeyEvent *);

//    QString str;

//signals:
//    void barcodeUpdate(QString str);

//private:
//    explicit Barcode(QObject *parent = 0);
//};

#endif // BARCODE_H
