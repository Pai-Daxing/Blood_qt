#ifndef PROTOCOLHELPER_H
#define PROTOCOLHELPER_H

#include <QObject>
#include "networkinterface.h"

class ProtocolHelper : public QObject
{
    Q_OBJECT
public:
    explicit ProtocolHelper(QObject *parent = 0);
    virtual bool parseNetData(ID_NET id, const QByteArray& in, void *out, QString &errmsg)=0;
    virtual void packageNetData(ID_NET id, const void *in, QByteArray &out) = 0;
    virtual void refreshGooIDKey( QString key ) = 0;
    virtual void lo_packageNetData(ID_NET id, const void *in, QByteArray &out);

    // 单机模式，封装返回数据包
    void lo_findNowCanCollectDonors(const void *in, QByteArray &out);
    void lo_plasmaCollectionSave(const void *in, QByteArray &out);
    void lo_findNurse(const void *in, QByteArray &out);
    void lo_findDonorPhoto(const void *in, QByteArray &out);
    void lo_findEquipments(QByteArray &out);
    void lo_findAnticoagulants(QByteArray &out);
    void lo_findSodiumChlorides(QByteArray &out);
    void lo_findServerTime(QByteArray &out);

private:
    QString             SUCCESS_STR;
    QString             LO_CODE;
    QString             LO_MSG;
};

#endif // PROTOCOLHELPER_H
