#include "btthread.h"
#include <linux/input.h>
#include <sys/fcntl.h>
#include <unistd.h>
#include </home/slrom/qtworks/led/wiringPi/wiringPi.h>

int inputpin = 2;

BtThread::BtThread(QObject *parent) :
    QThread(parent),
    keys_fd(-1)
{
//    keys_fd = open("/dev/input/event0", O_RDONLY);

//    if (keys_fd <= 0)
//    {
//        qDebug("open /dev/input/event0 error! \n");
//    }
//    else
//    {
//        qDebug("open /dev/input/event0\n");
//    }
}

BtThread::~BtThread()
{

}

BtThread* BtThread::getInst()
{
    static BtThread* inst = 0;
    if (0 == inst)
    {
        inst = new BtThread();
        if (inst)
        {
            inst->start();
        }
    }

    return inst;
}


void BtThread::run()
{
    while(1)
    {

        if(HIGH == digitalRead(inputpin))
        {
            emit stopButtonPressed();
        }
        msleep(100);
    }
}
