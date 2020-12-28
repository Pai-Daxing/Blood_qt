#include "netobj.h"


NetObj::NetObj(QObject *parent) :
    QObject(parent)
{
    m_netMrg = new QNetworkAccessManager(this);
}

NetObj &NetObj::getInstance()
{
    static NetObj obj;
    return obj;
}

NetReply *NetObj::postData( QUrl url,  const QByteArray &data )
{
    NetReply *netReply = new NetReply();
    netReply->post(url, data);

    return netReply;
}


NetReply *NetObj::postData( QUrl url, QIODevice *data )
{
    NetReply *netReply = new NetReply();
    netReply->post(url, data->readAll());

    return netReply;
}

NetReply *NetObj::getData(QUrl url)
{
    NetReply *netReply = new NetReply();
    netReply->get(url);

    return netReply;
}


QNetworkReply *NetObj::lowPostData(QUrl url,  const QByteArray &data )
{
    // check url

    QNetworkRequest req;
    req.setUrl( url );
    req.setHeader(QNetworkRequest::ContentTypeHeader,
                  "application/json");
    req.setHeader(QNetworkRequest::ContentLengthHeader,
                  data.size());

    return m_netMrg->post(req, data);
}


QNetworkReply *NetObj::lowGetData(QUrl url)
{
    // check url

    QNetworkRequest req;
    req.setUrl( url );

    return m_netMrg->get(req);
}
