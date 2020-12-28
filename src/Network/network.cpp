#include "network.h"
#include "../DataMgr/datamgr.h"
#include "../DataMgr/cfg.h"
#include <QNetworkAddressEntry>
#include <QFile>
#include <QNetworkConfigurationManager>
#include <QHostInfo>

// 定义每次设置最多等3s
#define  MAX_SET_TIME  3000

Network::Network(QThread* parent):
    QThread(parent)
{
    m_bOpenEth     = false;
    m_bOpenWlan    = false;
    m_bScanWlan    = false;
    m_bSetWlan     = false;
    m_bGetWlan     = false;
    m_bConnectEth  = false;
    m_bConnectWlan = false;

    m_HostIp             = Cfg::getInst().getUsrCfgStr(NW_hostIp );
    m_gatewayAdress = Cfg::getInst().getUsrCfgStr( NW_gatewayAdress );
    m_netmask          = Cfg::getInst().getUsrCfgStr( NW_netmask );

    start( QThread::LowestPriority );

    m_pSetProc = new QProcess();
    m_pSetProc->moveToThread( this );
}

void Network::init() //modified by zouyun 2013.5.20
{
    if (DataMgr::getInst().getUsrCfgInt(CFG_dataMgrSys))
    {
        if ( CFG_YES == (CFG_BOOL)(Cfg::getInst().getUsrCfgStr( NW_wlan ).toInt()) )
        {
            m_bOpenWlan = true;
            m_bConnectWlan = true;
        }
        else
        {
            m_bOpenEth = true;
            m_bConnectEth = true;
        }
    }
}

Network& Network::getInstance()
{
    static Network p;
    return p;
}

void Network::run()
{
    while(1)
    {
        if ( m_bOpenWlan )
        {
            myOpenWlan();

            QMutexLocker locker(&mutex);
            m_bOpenWlan = false;
            locker.unlock();
        }
        if ( m_bOpenEth )
        {
            myOpenEth();

            QMutexLocker locker(&mutex);
            m_bOpenEth = false;
            locker.unlock();
        }
        if ( m_bConnectEth )
        {
            myConnectEth();

            QMutexLocker locker(&mutex);
            m_bConnectEth = false;
            locker.unlock();
        }
        if ( m_bConnectWlan )
        {
            myConnectWlan();

            QMutexLocker locker(&mutex);
            m_bConnectWlan = false;
            locker.unlock();
        }
        if ( m_bScanWlan )
        {
            myScanWlan();

            QMutexLocker locker(&mutex);
            m_bScanWlan = false;
            locker.unlock();
        }
        if ( m_bSetWlan )
        {
//            mySetWlan(UserName , psk);

            QMutexLocker locker(&mutex);
            m_bSetWlan = false;
            locker.unlock();
        }
        if ( m_bGetWlan )
        {
            myGetWlan();

            QMutexLocker locker(&mutex);
            m_bGetWlan = false;
            locker.unlock();
        }

        sleep(2);
    }
}

void Network::openEth()
{
    QMutexLocker locker(&mutex);
    m_bOpenEth = true;
    locker.unlock();
}

void Network::openWlan()
{
    QMutexLocker locker(&mutex);
    m_bOpenWlan = true;
    locker.unlock();
}

void Network::scanWlan()
{
    QMutexLocker locker(&mutex);
    m_bScanWlan = true;
    locker.unlock();
}

void Network::setWlan(QString name, QString pw)
{
    m_routerName = name;
    m_routePsw   = pw;
    QMutexLocker locker(&mutex);
    m_bSetWlan = true;
    locker.unlock();
}

void Network::getWlan()
{
    QMutexLocker locker(&mutex);
    m_bGetWlan = true;
    locker.unlock();
}

void Network::connectEth()
{
    QMutexLocker locker(&mutex);
    m_bConnectEth = true;
    locker.unlock();
}

void Network::connectWlan()
{
    QMutexLocker locker(&mutex);
    m_bConnectWlan = true;
    locker.unlock();
}

void Network::myOpenEth()
{
    cfgEth0( m_HostIp, m_netmask, m_gatewayAdress );

#ifndef Q_WS_WIN32

        system("wpa_cli -i wlan0 down");
        system("wpa_cli -i eth0 up");
//    doCmd( "ifconfig wlan0 down" );
//    doCmd( "ifconfig eth0 up" );
#endif
}

void Network::myOpenWlan()
{
//    cfgWlan0( m_HostIp, m_netmask, m_gatewayAdress );

#ifndef Q_WS_WIN32

    system("wpa_cli -i wlan0 scan");
//    system("wpa_cli -i eth0 down");
    qDebug("dakai");

//    doCmd( "ifconfig wlan0 down" );
//    doCmd( "ifconfig eth0 up" );
#endif
}

void Network::myScanWlan()
{
    QStringList list;
#ifndef Q_WS_WIN32
//    ::system("iwlist wlan0 scan >/tmp/tmp &");
        system("rm temp ssid.txt");
    system("wpa_cli -i wlan0 scan_result > /home/pi/temp");
    system("awk '{print $5}' /home/pi/temp > /home/pi/ssid.txt");
    QFile pp("/home/pi/ssid.txt");
    pp.open(QFile::ReadOnly);
    sleep(1);
    QString a = pp.readAll();
//    int count = a.count("ESSID:");
//    for (int i = 1; i <= count; ++i)
//    {
//   //     int t = i * 2 - 1;
//        list << a.section('\n', i, i);
//    }
//    qDebug("xunwen ");
    list << a.split("\n");
//    list << a.split(",");
    qDebug()<<list;

#else
    qDebug("iwlist wlan0 scan");
    list << "linksys" << "ngl" << "ngl2";
#endif

    emit wlanFound( list );
}

void Network::mySetWlan(QString UserName , QString psk)
{
//    QString cmd = "setwlan.sh " + m_routerName + " " + m_routePsw;
//#ifndef Q_WS_WIN32
//    ::system(cmd.toLatin1().data());
//#else
//    qDebug(cmd.toLatin1().data());
//#endif
    system("sed -i /ssid/d /etc/wpa_supplicant/wpa_supplicant.conf");
    QThread::msleep(100);
    system("sed -i /psk/d /etc/wpa_supplicant/wpa_supplicant.conf");
    QThread::msleep(100);



    QString addUser = tr("sed -i 6i\\ssid=\\\"%1\\\" /etc/wpa_supplicant/wpa_supplicant.conf").arg(UserName);
    QString addPwd = tr("sed -i 7i\\psk=\\\"%1\\\" /etc/wpa_supplicant/wpa_supplicant.conf").arg(psk);

    qDebug() << addUser.toLatin1();
    system(addUser.toLatin1());
    QThread::msleep(100);
    qDebug() << addPwd;
    system(addPwd.toLatin1());
}

void Network::myGetWlan()
{
    QString name, pw;
#ifndef Q_WS_WIN32
    QFile pp("/etc/wpa_supplicant.conf");
    pp.open(QFile::ReadOnly);
    QString a = pp.readAll();
    name = a.section('"', 1, 1);
    pw = a.section('"', 3, 3);
#endif

    emit wlanSetting( name, pw );
}

void Network::myConnectEth()
{
    cfgEth0( m_HostIp, m_netmask, m_gatewayAdress );

    emit connected();
}

void Network::myConnectWlan()
{
    cfgWlan0( m_HostIp, m_netmask, m_gatewayAdress );

    emit connected();
}

// 获得MAC地址
QString Network::getMACAddress()
{
    QList<QNetworkInterface>  NetList; //网卡链表
    NetList = QNetworkInterface::allInterfaces();//获取所有网卡信息

    int NetCount = 0; //网卡个数
    NetCount = NetList.count();   //统计网卡个数

    QNetworkInterface thisNet;  //所要使用的网卡
    for(int i = NetCount - 1; i >=0; i--) //遍历所有网卡
    {
        if(NetList[i].isValid()) //判断该网卡是否是合法
        {
            thisNet = NetList[i]; //将该网卡置为当前网卡
            break;
        }
    }
    return ( thisNet.hardwareAddress() ); //获取该网卡的MAC
}

void Network::getip()
{
    QString add;
    QString localHostName = QHostInfo::localHostName();

    qDebug() <<"localHostName:"<<localHostName;
    emit localname(localHostName);

    QList<QHostAddress> list = QNetworkInterface::allAddresses();
        foreach (QHostAddress address, list)
        {
           if(address.protocol() == QAbstractSocket::IPv4Protocol)
                //我们使用IPv4地址
                add = address.toString();
           qDebug() << add;
           emit ipaddress(add);
        }
}

void Network::cfgEth0( QString ip, QString netmask, QString gw )
{
    QString cmd1 = "ifconfig eth0 " + ip + " netmask " + netmask;
    QString cmd2 = "route add default gw " + gw;

#ifndef Q_WS_WIN32
//    doCmd( cmd1 );
//    doCmd( cmd2 );
    //    ::system(cmd1.toAscii());
    //    ::system(cmd2.toAscii());
#else
    qDebug("udhcpc -ieth0");
#endif
}

void Network::cfgWlan0( QString ip, QString netmask, QString gw )
{
    QString cmd1 = "sudo ifconfig wlan0 " + ip + " netmask " + netmask;
    QString cmd2 = "sudo route add default gw " + gw;
//#ifndef Q_WS_WIN32
//    QString cmdWlan0 = "/usr/sbin/wpa_supplicant -Dwext -iwlan0 -c/etc/wpa_supplicant.conf";

    //    ::system("/usr/sbin/wpa_supplicant -Dwext -iwlan0 -c/etc/wpa_supplicant.conf &");
    //    sleep(3);
    //    ::system(cmd1.toAscii());
    //    ::system(cmd2.toAscii());

    //doCmd( cmdWlan0 );
//    m_pSetProc->start( cmdWlan0 );

//    if ( !m_pSetProc->waitForFinished( MAX_SET_TIME ) )
//    {
//        qDebug()<< cmdWlan0 << "failed";
//    }

    system(cmd1.toLatin1());
    system(cmd2.toLatin1());
//#else
//    qDebug("/usr/sbin/wpa_supplicant -Dwext -iwlan0 -c/etc/wpa_supplicant.conf &, udhcpc -iwlan0");
//#endif
}

bool Network::doCmd( QString cmd )
{
    QProcess tmpProc;
    bool rt = true;

#ifndef Q_WS_WIN32

    tmpProc.start(cmd);

    if ( !tmpProc.waitForFinished( MAX_SET_TIME ) )
    {
        qDebug()<< cmd << "failed";

        rt = false;
    }

#else
    qDebug()<< cmd;
#endif

    return rt;
}


