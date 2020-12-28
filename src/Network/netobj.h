#ifndef NetObj_H
#define NetObj_H

#include <QObject>
#include <QtNetwork>
#include <QMap>

#include "netreply.h"

typedef QMap<QNetworkReply *, NetReply *> ReplyMap;


class NetObj : public QObject
{
    Q_OBJECT
private:
    explicit NetObj(QObject *parent = 0);

public:
    friend class NetReply;

    static NetObj &getInstance();

    NetReply *postData( QUrl url,  const QByteArray &data );
    NetReply *postData( QUrl url,  QIODevice *data );
    NetReply *getData(QUrl url);

private:
    QNetworkReply *lowPostData(QUrl url,  const QByteArray &data );
    QNetworkReply *lowGetData(QUrl url);


private:
    QNetworkAccessManager   *m_netMrg;
};

#endif // NetObj_H
