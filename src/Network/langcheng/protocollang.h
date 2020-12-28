#ifndef PROTOCOLLANG_H
#define PROTOCOLLANG_H

#include <QObject>
#include "../protocolhelper.h"

class ProtocolLang : public ProtocolHelper
{
    Q_OBJECT
public:
    explicit ProtocolLang(QObject *parent = 0);
    bool parseNetData(ID_NET id, const QByteArray& in, void *out, QString &errmsg);
    void packageNetData(ID_NET id, const void *in, QByteArray &out);
    //void lo_packageNetData(ID_NET id, const void *in, QByteArray &out);


    void refreshGooIDKey( QString key )
    {
        m_GooIDKey = key;
    }

private:
    // 封装发送数据包
    void findNowCanCollectDonors( const void *in, QByteArray &out );
    void plasmaCollectionSave( const void *in, QByteArray &out );
    void findNurse( const void *in, QByteArray &out );
    void findDonorPhoto( const void *in, QByteArray &out );
    void sendDpStatus( const void *in, QByteArray &out );
    void packageGooidKey(QByteArray &out);

//    // 单机模式，封装返回数据包
//    void lo_findNowCanCollectDonors(const void *in, QByteArray &out);
//    void lo_plasmaCollectionSave(const void *in, QByteArray &out);
//    void lo_findNurse(const void *in, QByteArray &out);
//    void lo_findDonorPhoto(const void *in, QByteArray &out);
//    void lo_findEquipments(QByteArray &out);
//    void lo_findAnticoagulants(QByteArray &out);
//    void lo_findSodiumChlorides(QByteArray &out);
//    void lo_findServerTime(QByteArray &out);


    // 解析浆员信息
    bool onFindNowCanCollectDonors( QJsonValue &result, void *out );
    // 解析返回的采集记录
    bool plasmaCollectionSave( QJsonValue &result, void *out );
    // 解析四件套信息
    bool onFindEquipments( QJsonValue &result, void *out );
    // 解析抗凝剂信息
    bool onFindAnticoagulants( QJsonValue &result, void *out );
    // 解析氯化钠注射液信息
    bool onFindSodiumChlorides( QJsonValue &result, void *out );
    // 解析护士信息
    bool onFindNurse( QJsonValue &result, void *out );
    // 解析浆员照片信息
    bool onFindDonorPhoto( QJsonValue &result, void *out );
    // 获取系统时间
    bool onFindServerTime( QJsonValue &result, void *out );



private:
//    Json::FastWriter    m_jsWriter;
//    Json::Reader        m_jsReader;
    QString             m_GooIDKey;
};

#endif // PROTOCOLLANG_H
