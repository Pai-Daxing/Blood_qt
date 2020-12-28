#include "barcode.h"
#include <QFile>
#include <QTextStream>
#include <QKeyEvent>
#include <QDebug>

BarcodeThread::BarcodeThread(QObject *parent):
    QThread(parent)
{
}

BarcodeThread::~BarcodeThread()
{

}

BarcodeThread* BarcodeThread::getInst()
{
    static BarcodeThread* inst = 0;
    if (0 == inst)
    {
        inst = new BarcodeThread();
        if (inst)
        {
            inst->start();
        }
    }

    return inst;
}

void BarcodeThread::run()
{
    while(1)
    {
        QFile pp("/dev/input/event1");
        pp.open(QFile::ReadOnly);
        QString str = pp.readAll();
        qDebug()<<"s:"<<str;
 //       QString str = "5";

  //      emit barcodeUpdate(str);
        msleep(1000);
    }
}

//Barcode::Barcode(QObject *parent):
//    QObject(parent)
//{
//}

//Barcode::~Barcode()
//{

//}

//Barcode* Barcode::getInst()
//{
//    static Barcode *pBarcode = 0;

//    if ( NULL == pBarcode )
//    {
//        pBarcode = new Barcode();
//    }


//    return pBarcode;
//}


//void Barcode::keyPressEvent(QKeyEvent *keyValue)
//{
//    if(keyValue->key() == Qt::Key_Return)//enter
//    {
//        emit barcodeUpdate(str);
//        str.clear();
//    }
//    //else str += keyValue->text();
//}
