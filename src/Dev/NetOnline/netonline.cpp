#include "netonline.h"
#include <QNetworkConfigurationManager>




NetOnline::NetOnline(QObject *parent) :
    QThread(parent)
{

}

NetOnline::~NetOnline()
{

}

NetOnline* NetOnline::getInst()
{
    static NetOnline* inst = 0;
    if (0 == inst)
    {
        inst = new NetOnline();
        if (inst)
        {
            inst->start();
        }
    }

    return inst;
}


void NetOnline::run()
{
    while(1)
    {
            QNetworkConfigurationManager mgr;
            if(!mgr.isOnline())
            {
                emit netconnect();
            }
            else
            {
                emit netconnectfaild();
            }
        msleep(100);
    }
}
