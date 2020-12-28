#include "time.h"
#include </home/slrom/qtworks/led/wiringPi/wiringPi.h>
#include </home/slrom/qtworks/led/wiringPi/wiringPiI2C.h>

#define SlaveAddress (0x32)

int fd,year,mon,day,hour,min,sec,week,val;


TimeThread::TimeThread(QObject *parent):
    QThread(parent)
{
}

TimeThread::~TimeThread()
{

}

TimeThread* TimeThread::getInst()
{
    static TimeThread* inst = 0;
    if (0 == inst)
    {
        inst = new TimeThread();
        if (inst)
        {
            inst->start();
        }
    }

    return inst;
}

void TimeThread::inittime()
{
    year = wiringPiI2CReadReg8(fd,0x06);
    mon = wiringPiI2CReadReg8(fd,0x05);
    day = wiringPiI2CReadReg8(fd,0x04);
    hour = wiringPiI2CReadReg8(fd,0x02);
    min = wiringPiI2CReadReg8(fd,0x01);
    sec = wiringPiI2CReadReg8(fd,0x00);
    week = wiringPiI2CReadReg8(fd,0x03);

    QString info = QString("%1").arg(hour,0,10);
    int tmp = info.toInt();
    val = tmp^128;
}

void TimeThread::run()
{
    wiringPiSetup();
    fd = wiringPiI2CSetup(SlaveAddress);
    if (fd >= 0)
    {
     //   qDebug("fd = %d\n",fd);
        while(1)
        {
            inittime();
            QString str;
            str.sprintf("%x:%x:%x\n20%x/%x/%x",val,min,sec,year,mon,day);
            emit timerUpdate(str);
            delay(1000);
        }
    }
    else
    {
        qDebug("IIC初始化失败");
    }
}
