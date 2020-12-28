#include "netobj.h"
#include "netreply.h"

//#include <QMessageBox>


NetReply::NetReply()
    : QObject(),
      m_pReply(0)
{
    m_pTimer = new QTimer(this);
    connect( m_pTimer, SIGNAL(timeout()), this, SLOT(onTimeOut()) );
}


NetReply::~NetReply()
{

}

void NetReply::post(QUrl &url, const QByteArray &data)
{
    m_url = url;
    m_data = data;

    m_pReply = NetObj::getInstance().lowPostData(m_url, m_data);
    if (NULL != m_pReply)
    {
        connect( m_pReply, SIGNAL(finished()), this, SLOT(onFinished()) );
    }

    m_pTimer->start(TIME_OUT);
}

void NetReply::get(QUrl &url)
{
    m_url = url;

    m_pReply = NetObj::getInstance().lowGetData(m_url);
    if ( NULL != m_pReply )
    {
        connect( m_pReply, SIGNAL(finished()), this, SLOT(onFinished()));
    }

    m_pTimer->start(TIME_OUT);
}


void NetReply::emitGetData(quint16 statusCode, QByteArray data)
{
    if ( NULL != m_pReply )
    {
        m_pReply->deleteLater();
        m_pReply = NULL;
    }

    this->deleteLater();

    emit getData(statusCode, data);
}


void NetReply::onTimeOut()
{
    QByteArray data;
    if ( NULL != m_pReply )
    {
        m_pReply->disconnect();
    }

    emitGetData( TIMEOUT_CODE, data );
}

void NetReply::onFinished()
{

    QVariant varStatusCode = m_pReply->attribute(
                QNetworkRequest::HttpStatusCodeAttribute);

    m_st = 0;
    if (varStatusCode.canConvert<int>())
    {
        m_st = varStatusCode.toInt();
    }

    QByteArray data = m_pReply->readAll();

    emitGetData(m_st, data);
}

void NetReply::autoEmit(int st, const QByteArray &data)
{
    QTimer *ptimer = new QTimer(this);
    connect( ptimer, SIGNAL(timeout()), this, SLOT(onAutoEmit()) );

    m_data = data;
    m_st = st;

    ptimer->start(100); //100ms后自动回复
}

void NetReply::onAutoEmit()
{
    emitGetData(m_st, m_data);
}
