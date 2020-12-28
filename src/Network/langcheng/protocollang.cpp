/***********************************************************************
* ProtocolLang.cpp
* Copyright all resever(2015)
*
* 帮助解析网络返回来的数据格式
*
* Author              Date               Action
* lilice              2015/11/19          create

***********************************************************************/
#include "protocollang.h"
#include "../../DataMgr/datamgr.h"
#include "../../DataMgr/cfg.h"
#include <QJsonValue>
#include <QJsonObject>




ProtocolLang::ProtocolLang(QObject *parent) :
    ProtocolHelper(parent)
{    
    m_GooIDKey = Cfg::getInst().getUsrCfgStr( NW_key );
}


//------------------------------------------------------------------------------
void ProtocolLang::packageNetData(ID_NET id, const void *in, QByteArray &out)
{
    out.clear();

    switch (id)
    {
    case N_DONOR:
        findNowCanCollectDonors(in, out);
        break;
    case N_RESULT:
        plasmaCollectionSave(in, out);
        break;
    case N_NURSE:
        findNurse(in, out);
        break;
    case N_DONORPIC:
        findDonorPhoto(in, out);
        break;
    case N_STATUS:
        sendDpStatus(in, out);
        break;
    case N_DISPOSABLE:
    case N_ACD:
    case N_NACL:
    case N_TIME:
        packageGooidKey(out);
        break;
    default:
        break;
    }
}

void ProtocolLang::findNowCanCollectDonors( const void *in, QByteArray &out )
{
    //Q_ASSERT(in);
    if ( NULL == in )
    {
        qDebug() << QString("%1 : %2").arg(__FILE__).arg(__LINE__);
    }

    Donor_t *data = (Donor_t *)in;

    QJsonObject obj;
    obj.insert( "gooidKey",    QJsonValue(m_GooIDKey) );
    obj.insert( "dorOrRegNo",  QJsonValue(data->id) );
    obj.insert( "PAGE_NUMBER", QJsonValue(data->pageNumber) );
    obj.insert( "PAGE_SIZE",   QJsonValue(data->pageSize) );

    out.append( QJsonDocument(obj).toJson() );
}

void ProtocolLang::plasmaCollectionSave( const void *in, QByteArray &out )
{
    //Q_ASSERT(in);
    if ( NULL == in )
    {
        qDebug() << QString("%1 : %2").arg(__FILE__).arg(__LINE__);
    }

    Result_t *data = (Result_t *)in;

    QJsonObject obj;
    obj.insert( "gooidKey",           QJsonValue(m_GooIDKey) );
    obj.insert( "cycleTimes",         QJsonValue(data->cycleTimes) );
    obj.insert( "onewayWeight",       QJsonValue(data->onewayWeight) );
    obj.insert( "weight",             QJsonValue(data->weight) );
    obj.insert( "anticoagulantDose",  QJsonValue(data->anticoagulantDose) );
    obj.insert( "sodiumChlorideDose", QJsonValue(data->sodiumChlorideDose) );
    obj.insert( "collectState",       QJsonValue(data->collectState) );
    obj.insert( "equipmentSetNum",    QJsonValue(data->equipmentSetNum) );
    obj.insert( "anticoagulantNum",   QJsonValue(data->anticoagulantNum) );
    obj.insert( "sodiumChlorideNum",  QJsonValue(data->sodiumChlorideNum) );

    obj.insert( "donorNo",            QJsonValue(data->donorNo) );
    obj.insert( "beginDate",          QJsonValue(data->beginDate) );
    obj.insert( "endDate",            QJsonValue(data->endDate) );
    obj.insert( "twoNeedle",          QJsonValue(data->twoNeedle) );
    obj.insert( "adverseReaction",    QJsonValue(data->adverseReaction) );
    obj.insert( "remark",             QJsonValue(data->remark) );

    obj.insert( "nurse",              QJsonValue(data->nurse) );
    obj.insert( "equipmentSet",       QJsonValue(data->equipmentSet) );
    obj.insert( "anticoagulantBatch", QJsonValue(data->anticoagulantBatch) );
    obj.insert( "sodiumChloride",     QJsonValue(data->sodiumChloride) );

    out.append( QJsonDocument(obj).toJson() );
}

void ProtocolLang::findNurse( const void *in, QByteArray &out )
{
    //Q_ASSERT(in);
    if ( NULL == in )
    {
        qDebug() << QString("%1 : %2").arg(__FILE__).arg(__LINE__);
    }

    Nurse_t *data = (Nurse_t *)in;

    QJsonObject obj;
    obj.insert( "gooidKey",    QJsonValue(m_GooIDKey) );
    obj.insert( "userName",    QJsonValue(data->id) );
    obj.insert( "PAGE_NUMBER", QJsonValue(data->pageNumber) );
    obj.insert( "PAGE_SIZE",   QJsonValue(data->pageSize) );

    out.append( QJsonDocument(obj).toJson() );
}

void ProtocolLang::findDonorPhoto( const void *in, QByteArray &out )
{
    //Q_ASSERT(in);
    if ( NULL == in )
    {
        qDebug() << QString("%1 : %2").arg(__FILE__).arg(__LINE__);
    }

    DonorPic_t *data = (DonorPic_t *)in;

    QJsonObject obj;
    obj.insert( "gooidKey",    QJsonValue(m_GooIDKey) );
    obj.insert( "donorNo",    QJsonValue(data->id) );

    out.append( QJsonDocument(obj).toJson() );
}

void ProtocolLang::sendDpStatus( const void *in, QByteArray &out )
{
    if ( NULL == in )
    {
        qDebug() << QString("%1 : %2").arg(__FILE__).arg(__LINE__);
    }

    DpStatus_t *data = (DpStatus_t *)in;

    QJsonObject obj;
    obj.insert( "gooidKey",    QJsonValue(m_GooIDKey) );
    obj.insert( "dpStatus",    QJsonValue(data->st) );

    out.append( QJsonDocument(obj).toJson() );
}

void ProtocolLang::packageGooidKey(QByteArray &out)
{  
    QJsonObject obj;
    obj.insert( "gooidKey", QJsonValue(m_GooIDKey) );

    out.append( QJsonDocument(obj).toJson() );
}



//------------------------------------------------------------------------------
bool ProtocolLang::parseNetData(ID_NET id, const QByteArray& in, void *out, QString &errmsg)
{
    //Q_ASSERT(out);
    if ( NULL == out )
    {
        qDebug() << QString("%1 : %2").arg(__FILE__).arg(__LINE__);
    }

    QJsonDocument doc = QJsonDocument::fromJson(in);
    if ( doc.isNull() ){
        return false;
    }

    QJsonObject root = doc.object();

    qDebug() << "parseNetData: id[" << id << "]\n"
             << root;

    // 返回的网络数据必须具备的两个个字段
    if ( root["msg"].isNull()
         || root["result"].isNull() )
    {
        return false;
    }

    // 保存返回信息 msg 到 errmsg
    errmsg = root["msg"].toString();

    // 获取返回结果
    QJsonValue result = root["result"];


    switch (id)
    {
    case N_DONOR:
        return onFindNowCanCollectDonors(result, out);
    case N_RESULT:
        return plasmaCollectionSave(result, out);
    case N_DISPOSABLE:
        return onFindEquipments(result, out);
    case N_ACD:
        return onFindAnticoagulants(result, out);
    case N_NACL:
        return onFindSodiumChlorides(result, out);
    case N_NURSE:
        return onFindNurse(result, out);
    case N_DONORPIC:
        return onFindDonorPhoto(result, out);
    case N_TIME:
        return onFindServerTime(result, out);
    default:
        return false;
    }
}

// 解析浆员信息
bool ProtocolLang::onFindNowCanCollectDonors( QJsonValue &result, void *out )
{
    InDonor_t *data = (InDonor_t *)out;
    QJsonObject value;
    QJsonArray array = result.toArray();

    // result 应该为数组
    if ( array.isEmpty() ){
        return false;
    }

    // 只取第一个
    value = array[0].toObject();

    if ( !value["donorNo"].isNull() )
    {
        data->id = value["donorNo"].toString();
    }

    if ( !value["donorName"].isNull() )
    {
        data->name = value["donorName"].toString();
    }

    if ( !value["bloodType"].isNull() )
    {
        data->bloodType = value["bloodType"].toString();
    }

    if ( !value["createdDate"].isNull() )
    {
        data->creDate = value["createdDate"].toString();
    }

    if ( !value["idCard"].isNull() )
    {
        data->idCard = value["idCard"].toString();
    }

    if ( !value["processNo"].isNull() )
    {
        data->processNo = value["processNo"].toString();
    }

    if ( !value["remark"].isNull() )
    {
        data->remark = value["remark"].toString();
    }

    if ( !value["collectTip"].isNull() )
    {
        data->tip = value["collectTip"].toString();
    }

    if ( !value["address"].isNull() )
    {
        data->address = value["address"].toString();
    }

    if ( !value["phone"].isNull() )
    {
        data->phone = value["phone"].toString();
    }

    if ( !value["sex"].isNull() )
    {
        QString sex = value["sex"].toString();
        if ( QString("M") == sex )
        {
            data->sex = tr("男");
        }
        else if ( QString("W") == sex )
        {
            data->sex = tr("女");
        }
        else
        {
            data->sex = "";
        }
    }

    if ( !value["changeless"].isNull() )
    {
        QString sate = value["changeless"].toString();
        if ( QString("Y") == sate )
        {
            data->state = tr("固定");
        }
        else if ( QString("N") == sate )
        {
            data->state = tr("非固定");
        }
        else if ( QString("NEW") == sate )
        {
            data->state = tr("新浆员");
        }
        else
        {
            data->state = "";
        }
    }


    return true;
}

// 解析返回的采集记录
bool ProtocolLang::plasmaCollectionSave( QJsonValue &result, void *out )
{
    InResult_t *data = (InResult_t *)out;

    data->code = result.toString();

    // 判断返回的code是否为正确值(包含)
    if ( !data->code.contains( PLASMA_REPLY_CODE_OK ) )
    {
        return false;
    }

    return true;
}

// 解析四件套信息(可能存在多件)  SPLIT_SYMBOL
bool ProtocolLang::onFindEquipments( QJsonValue &result, void *out )
{
    InDisposable_t *data = (InDisposable_t *)out;

    bool bRet = false;

    QJsonObject value;
    QJsonArray array = result.toArray();

    // result 应该为数组
    if ( array.isEmpty() ){
        return false;
    }

    quint16 size = array.size();
    quint16 i;
    for( i = 0; i < size; i++ )
    {
        value = array[i].toObject();

        // 两个字段同时存在才认为该条信息有意义
        if ( value["equipmentSet"].isNull()
             || value["equipmentName"].isNull() )
        {
            continue;
        }

        if (bRet) //多余1套，每套间使用分隔符隔离
        {
            data->id.append(SPLIT_SYMBOL);
            data->name.append(SPLIT_SYMBOL);
        }

        data->id.append(value["equipmentSet"].toString());
        data->name.append(value["equipmentName"].toString());

        bRet = true;
    }

    return bRet;
}

// 解析抗凝剂信息
bool ProtocolLang::onFindAnticoagulants( QJsonValue &result, void *out )
{
    InACD_t *data = (InACD_t *)out;

    bool bRet = false;

    QJsonObject value;
    QJsonArray array = result.toArray();

    // result 应该为数组
    if ( array.isEmpty() ){
        return false;
    }

    quint16 size = array.size();
    quint16 i;
    for( i = 0; i < size; i++ )
    {
        value = array[i].toObject();

        // 两个字段同时存在才认为该条信息有意义
        if ( value["anticoagulantBatch"].isNull()
             || value["anticoagulantName"].isNull() )
        {
            continue;
        }

        if (bRet) //多余1套，每套间使用分隔符隔离
        {
            data->id.append(SPLIT_SYMBOL);
            data->name.append(SPLIT_SYMBOL);
        }

        data->id.append(value["anticoagulantBatch"].toString());
        data->name.append(value["anticoagulantName"].toString());

        bRet = true;
    }

    return bRet;
}

// 解析氯化钠注射液信息
bool ProtocolLang::onFindSodiumChlorides( QJsonValue &result, void *out )
{
    InNacl_t *data = (InNacl_t *)out;

    bool bRet = false;

    QJsonObject value;
    QJsonArray array = result.toArray();

    // result 应该为数组
    if ( array.isEmpty() ){
        return false;
    }

    quint16 size = array.size();
    quint16 i;
    for( i = 0; i < size; i++ )
    {
        value = array[i].toObject();

        // 两个字段同时存在才认为该条信息有意义
        if ( value["sodiumChloride"].isNull()
             || value["sodiumChlorideName"].isNull() )
        {
            continue;
        }

        if (bRet) //多余1套，每套间使用分隔符隔离
        {
            data->id.append(SPLIT_SYMBOL);
            data->name.append(SPLIT_SYMBOL);
        }

        data->id.append(value["sodiumChloride"].toString());
        data->name.append(value["sodiumChlorideName"].toString());

        bRet = true;
    }

    return bRet;
}

// 解析护士信息
bool ProtocolLang::onFindNurse( QJsonValue &result, void *out )
{
    InNurse_t *data = (InNurse_t *)out;
    QJsonObject value;
    QJsonArray array = result.toArray();

    // result 应该为数组
    if ( array.isEmpty() ){
        return false;
    }

    // 只取第一个
    value = array[0].toObject();

    if ( !value["userName"].isNull() )
    {
        data->id = value["userName"].toString();
    }

    if ( !value["realName"].isNull() )
    {
        data->name = value["realName"].toString();
    }

    if ( !value["phone"].isNull() )
    {
        data->phone = value["phone"].toString();
    }

    if ( !value["sex"].isNull() )
    {
        QString sex = value["sex"].toString();
        if ( QString("M") == sex )
        {
            data->sex = tr("男");
        }
        else if ( QString("W") == sex )
        {
            data->sex = tr("女");
        }
        else
        {
            data->sex = "";
        }
    }

    return true;
}

// 解析浆员照片信息
bool ProtocolLang::onFindDonorPhoto( QJsonValue &result, void *out )
{
    InDonorPic_t *data = (InDonorPic_t *)out;
    QJsonObject value;

    value = result.toObject(); // 此处 result 不是数组，只有一个值

    if ( !value["donorNo"].isNull() )
    {
        data->id = value["donorNo"].toString();
    }

    if ( !value["frontPhoto"].isNull() )
    {
        data->pic = value["frontPhoto"].toString();
    }

    return true;
}

// 解析服务器时间
bool ProtocolLang::onFindServerTime( QJsonValue &result, void *out )
{
    InTime_t *data = (InTime_t *)out;
    QJsonObject value;

    value = result.toObject(); // 此处 result 不是数组，只有一个值

    if ( !value["serverTime"].isNull() )
    {
        data->time = value["serverTime"].toString();
    }

    return true;
}

