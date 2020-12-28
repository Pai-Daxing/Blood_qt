#ifndef NETREPLY_H
#define NETREPLY_H

#include <QObject>
#include <QTimer>
#include <QtNetwork/QNetworkReply>

// ms
static const int TIME_OUT = 10000;
const int TIMEOUT_CODE = 404;

class NetReply : public QObject
{
    Q_OBJECT

private:
    ~NetReply();

public:

    void emitGetData(quint16 statusCode, QByteArray data);
    void autoEmit(int st, const QByteArray &data);
    void post(QUrl &url, const QByteArray &data);
    void get(QUrl &url);

private slots:
    void onTimeOut();
    void onFinished();
    void onAutoEmit();

private:
    explicit NetReply();

    friend class NetworkInterface;
    friend class NetObj;
signals:
    void getData(quint16 statusCode, QByteArray data);

private:
    QUrl        m_url;
    QByteArray  m_data;
    int         m_st;   // 返回状态

    QTimer      *m_pTimer;

    QNetworkReply *m_pReply;
};

#endif // NETREPLY_H
