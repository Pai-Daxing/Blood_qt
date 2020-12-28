#ifndef NETWORK_H
#define NETWORK_H

#include <QThread>
#include <QStringList>
#include <QMutex>
#include <QProcess>

class Network : public QThread
{
    Q_OBJECT
public:
    explicit Network(QThread* parent = 0);

    static Network& getInstance();

    Q_INVOKABLE void myOpenWlan(); //打开无线网卡
    Q_INVOKABLE void myScanWlan(); //扫描无线网络
     Q_INVOKABLE   void mySetWlan(QString user , QString pwd); //设置无线网络名及密码
     Q_INVOKABLE void cfgWlan0( QString ip, QString netmask, QString gw );
    Q_INVOKABLE void getip();

    //网络连接初始化
    void init();

    //打开网卡
    void openEth();  //打开有线网卡
    void openWlan(); //打开无线网卡
    //扫描网络
    void scanWlan(); //扫描无线网络
    //设置网络
    void setWlan(QString name ,QString pw); //设置无线网络名及密码
    void getWlan(); //获取无线网络设置的网络名及密码
    //连接网络
    void connectEth(); //连接有线网
    void connectWlan();//连接无线网

    QString getMACAddress();

    void setGatewayAdress( QString adr ) { m_gatewayAdress = adr; }
    void setHostIp( QString ip ) { m_HostIp = ip; }
    void setNetmask( QString netmask ) { m_netmask = netmask; }


signals:
    void wlanFound( QStringList list );
    void wlanSetting( QString name, QString pw );
    void connected();
    void localname(QString localHostName);
    void ipaddress(QString add);

protected:
    void run();

private:
    void cfgEth0( QString ip, QString netmask, QString gw );
//    void cfgWlan0( QString ip, QString netmask, QString gw );

    void myOpenEth();  //打开有线网卡
//    Q_INVOKABLE void myOpenWlan(); //打开无线网卡
//    Q_INVOKABLE void myScanWlan(); //扫描无线网络
//    void mySetWlan(); //设置无线网络名及密码
    void myGetWlan(); //获取无线网络设置的网络名及密码
    void myConnectEth(); //连接有线网
    void myConnectWlan();//连接无线网

    bool doCmd( QString cmd );


private:

    bool m_bOpenEth;
    bool m_bOpenWlan;
    bool m_bScanWlan;
    bool m_bSetWlan;
    bool m_bGetWlan;
    bool m_bConnectEth;
    bool m_bConnectWlan;

    QString m_routerName;
    QString m_routePsw;
    QString m_gatewayAdress;
    QString m_HostIp;
    QString m_netmask;

    mutable QMutex mutex;
    QProcess *m_pSetProc;
};

#endif // NETWORK_H
