/***********************************************************************
* networkinterface.cpp
* Copyright(2015) all rights resever
* 创建NetworkInterface类，负责网络应用收发的接口
*
*

*
* Author              Date                Action
* whw                 2015/11/18          create
* llc                    2016/04/15        modified
*
***********************************************************************/
#include <QDebug>
#include "networkinterface.h"
#include "../DataMgr/datamgr.h"
#include "../DataMgr/cfg.h"
#include "protocolhelper.h"
#include "myurl.h"
#include "langcheng/urllang.h"
#include "langcheng/protocollang.h"

#ifdef __linux__
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#endif


//------------------------------------------------------------------------------


NetworkInterface::NetworkInterface(QObject *parent) :
    QObject(parent)
{
//    m_protocolHelper = new ProtocolHelper();
//    m_protocolHelper->refreshGooIDKey( Cfg::getInst().getUsrCfgStr( NW_key ) );

    QString strServerAdress = Cfg::getInst().getUsrCfgStr( NW_ServerAdress );
    setServerAdress( strServerAdress );

    m_pUrlLang = new UrlLang();
    m_pPrtLang = new ProtocolLang();

    refreshServerCfg();
}

NetworkInterface& NetworkInterface::getInst()
{
    static NetworkInterface netapp;
    return netapp;
}

void NetworkInterface::setServerAdress( QString adress )
{
    m_serverAdress = adress;
}

QString NetworkInterface::getServerAdress()
{
    return m_serverAdress;
}

void NetworkInterface::refreshServerCfg()
{
    SrvName srv = Cfg::getInst().getServerName();

    switch( srv )
    {
    case LANGCHENG:
        m_pCurUrlMan = ( MyUrl* )m_pUrlLang;
        m_protocolHelper = (ProtocolHelper*)m_pPrtLang;

        break;
    default:
        Q_ASSERT(0);
        break;
    }

    QString key = Cfg::getInst().getUsrCfgStr( NW_key );
    m_protocolHelper->refreshGooIDKey( key );

    QString strServerAdress = Cfg::getInst().getUsrCfgStr( NW_ServerAdress );
    setServerAdress( strServerAdress );
}

NetReply *NetworkInterface::sendData( ID_NET id,  void *data )
{
    if (N_ID_MAX <= id)
    {
        return NULL;
    }

    QByteArray sendData;
    QUrl url = QUrl( m_serverAdress + m_pCurUrlMan->getUrl( id ) );

    m_protocolHelper->packageNetData(id, data, sendData);

    int tmp = DataMgr::getInst().getUsrCfgInt( CFG_dataMgrSys );
    bool isNetConnected = (tmp == CFG_TRUE);

    if ( isNetConnected )
    {
        m_protocolHelper->packageNetData(id, data, sendData);

        return NetObj::getInstance().postData(url, sendData);
    }
    else    // 单机状态
    {
        m_protocolHelper->lo_packageNetData(id, data, sendData);

        NetReply *reply = new NetReply();
        reply->autoEmit(CONNECT_CODE, sendData);

        return reply;
    }
}


bool NetworkInterface::parseNetData(ID_NET id, const QByteArray& in, void *out, QString &errmsg)
{
    //Q_ASSERT(out);
    if ( NULL == out )
    {
        qDebug() << QString("%1 : %2").arg(__FILE__).arg(__LINE__);
    }

    return m_protocolHelper->parseNetData(id, in, out, errmsg);
}


//bool NetworkInterface::checkNetStatus()
//{
//#ifndef Q_WS_WIN32
//    bool ret = false;

//    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
//    if (0 > sockfd)
//    {
//        return false;
//    }
//    else
//    {
//        struct ifreq ifr;
//        memset(&ifr, 0, sizeof(ifr));
//        strcpy(ifr.ifr_name, "eth0");

//        if (0 != ioctl(sockfd, SIOCGIFFLAGS, &ifr))
//        {
//            //close(sockfd);
//            return false;
//        }
//        else
//        {
//            ret = ((ifr.ifr_flags & IFF_UP) && (ifr.ifr_flags & IFF_RUNNING));
//        }
//    }

//    //close(sockfd);

//    return ret;
//#else

//    return true;
//#endif
//}
