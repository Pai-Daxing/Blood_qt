#ifndef NETCFG_H
#define NETCFG_H

#include <QObject>
#include <QSettings>

#define PLASMA_SET_FILE  ("./Datas/network.ini")




enum NETWORKSETTING
{
    NW_wlan,                  //是否设置为无线连接
    NW_hostIp,               //主机的ip
    NW_gatewayAdress,   //网关
    NW_netmask,            //子网掩码
    NW_key,                   //密钥
    NW_ServerAdress       //服务器地址
};

class NetCfg : public QObject
{
    Q_OBJECT
    public:

    static NetCfg& getInst();
    //获取指定字符型配置项的用户设置值（如果指定的配置项不存在，返回空）
    QString  getUsrCfgStr(NETWORKSETTING id);

    //设置指定字符型配置项的用户设置值（如果指定的配置项不存在，返回false）
    void setUsrCfgStr(NETWORKSETTING id, QString value);

private:
    NetCfg( QObject *parent = 0 );

signals:
    
public slots:

private:
    QSettings *m_pCfgSetting;
    QHash< int, QString > m_Hash;
};

#endif // NETCFG_H
