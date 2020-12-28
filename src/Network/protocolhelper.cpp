/***********************************************************************
* protocolhelper.cpp
* Copyright all resever(2015)
*
* 帮助解析网络返回来的数据格式
*
* Author              Date               Action
* lilice              2015/11/19          create

***********************************************************************/
#include "protocolhelper.h"
#include "../DataMgr/datamgr.h"

ProtocolHelper::ProtocolHelper(QObject *parent) :
    QObject(parent)
{    
    SUCCESS_STR = QString("success");
    LO_CODE = QString("success");
    LO_MSG = QString(QObject::tr("单机模式，自动返回"));
}


//------------------------------------------------------------------------------
void ProtocolHelper::lo_packageNetData(ID_NET id, const void *in, QByteArray &out)
{
     out.clear();

    switch (id)
    {
    case N_DONOR:
        //自己构建返回值
        lo_findNowCanCollectDonors(in, out);
        break;
    case N_RESULT:
        lo_plasmaCollectionSave(in, out);
        break;
    case N_NURSE:
        lo_findNurse(in, out);
        break;
    case N_DONORPIC:
        lo_findDonorPhoto(in, out);
        break;
    case N_DISPOSABLE:
        lo_findEquipments(out);
        break;
    case N_ACD:
        lo_findAnticoagulants(out);
        break;
    case N_NACL:
        lo_findSodiumChlorides(out);
        break;
    case N_TIME:
        lo_findServerTime(out);
        break;
    default:
        break;
    }
}

void ProtocolHelper::lo_findNowCanCollectDonors(const void *in, QByteArray &out)
{
    Donor_t *data = (Donor_t *)in;
    out.clear();

    QJsonObject result;
    result.insert( "donorNo",    QJsonValue(data->id) );
    result.insert( "donorName",  QJsonValue("") );
    result.insert( "sex",        QJsonValue("") );
    result.insert( "bloodType",  QJsonValue("") );
    result.insert( "createdDate", QJsonValue("") );
    result.insert( "idCard",      QJsonValue("") );
    result.insert( "processNo",   QJsonValue(data->id) );
    result.insert( "changeless",  QJsonValue("") );
    result.insert( "remark",      QJsonValue("") );
    result.insert( "collectTip",  QJsonValue("") );
    result.insert( "address",     QJsonValue("") );
    result.insert( "phone",       QJsonValue("") );

    QJsonObject root;
    root.insert( "code",      QJsonValue(LO_CODE) );
    root.insert( "msg",       QJsonValue(LO_MSG) );
    root.insert( "result",    QJsonValue(result).toArray() );// 数组

    out.append( QJsonDocument(root).toJson() );
}

void ProtocolHelper::lo_plasmaCollectionSave(const void *in, QByteArray &out)
{
    QByteArray body;
    out.clear();

    //plasmaCollectionSave(in, body);

    QJsonObject root;
    QJsonObject result;
    QJsonDocument doc = QJsonDocument::fromJson(body);
    if ( !doc.isObject() ){
        return;
    }

    result = doc.object();
    result.remove("gooidKey");

    root.insert( "code",      QJsonValue(LO_CODE) );
    root.insert( "msg",       QJsonValue(LO_MSG) );
    root.insert( "result",    QJsonValue(result).toArray() );// 数组

    out.append( QJsonDocument(root).toJson() );
}

void ProtocolHelper::lo_findNurse(const void *in, QByteArray &out)
{
    Nurse_t *data = (Nurse_t *)in;
    out.clear();

    QJsonObject root;
    QJsonObject result;

    result.insert( "userName", QJsonValue(data->id) );
    result.insert( "realName", QJsonValue("") );
    result.insert( "sex",      QJsonValue("") );
    result.insert( "phone",    QJsonValue("") );

    root.insert( "code",      QJsonValue(LO_CODE) );
    root.insert( "msg",       QJsonValue(LO_MSG) );
    root.insert( "result",    QJsonValue(result).toArray() );   // 数组

    out.append( QJsonDocument(root).toJson() );
}

void ProtocolHelper::lo_findDonorPhoto(const void *in, QByteArray &out)
{
    DonorPic_t *data = (DonorPic_t *)in;
    out.clear();

    QJsonObject root;
    QJsonObject result;

    result.insert( "donorNo", QJsonValue(data->id) );
    result.insert( "frontPhoto", QJsonValue("") );

    root.insert( "code",      QJsonValue(LO_CODE) );
    root.insert( "msg",       QJsonValue(LO_MSG) );
    root.insert( "result",    result );// 注意：不是数组

    out.append( QJsonDocument(root).toJson() );
}

void ProtocolHelper::lo_findEquipments(QByteArray &out)
{
    out.clear();

    QJsonObject root;
    QJsonObject result;

    result.insert( "equipmentSet",  QJsonValue("") );
    result.insert( "equipmentName", QJsonValue("") );

    root.insert( "code",      QJsonValue(LO_CODE) );
    root.insert( "msg",       QJsonValue(LO_MSG) );
    root.insert( "result",    QJsonValue(result).toArray() );// 数组

    out.append( QJsonDocument(root).toJson() );
}

void ProtocolHelper::lo_findAnticoagulants(QByteArray &out)
{
    out.clear();

    QJsonObject root;
    QJsonObject result;

    result.insert( "anticoagulantBatch", QJsonValue("") );
    result.insert( "anticoagulantName",  QJsonValue("") );

    root.insert( "code",      QJsonValue(LO_CODE) );
    root.insert( "msg",       QJsonValue(LO_MSG) );
    root.insert( "result",    QJsonValue(result).toArray() );// 数组

    out.append( QJsonDocument(root).toJson() );
}

void ProtocolHelper::lo_findSodiumChlorides(QByteArray &out)
{
    out.clear();

    QJsonObject root;
    QJsonObject result;

    result.insert( "sodiumChloride",      QJsonValue("") );
    result.insert( "sodiumChlorideName",  QJsonValue("") );

    root.insert( "code",      QJsonValue(LO_CODE) );
    root.insert( "msg",       QJsonValue(LO_MSG) );
    root.insert( "result",    QJsonValue(result).toArray() );// 数组

    out.append( QJsonDocument(root).toJson() );
}

void ProtocolHelper::lo_findServerTime(QByteArray &out)
{
    out.clear();

    QDateTime data = QDateTime::currentDateTime();

    QJsonObject root;
    QJsonObject result;

    result.insert( "serverTime",      data.toString("yyyyMMddhhmm0ss") );

    root.insert( "code",      QJsonValue(LO_CODE) );
    root.insert( "msg",       QJsonValue(LO_MSG) );
    root.insert( "result",    result );//注意：不是数组

    out.append( QJsonDocument(root).toJson() );
}

