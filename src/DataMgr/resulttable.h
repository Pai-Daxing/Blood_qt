#ifndef RESULTTABLE_H
#define RESULTTABLE_H

#include <QLinkedList>
#include "dbtable.h"
#include "../Network/networkinterface.h"
#include <QDateTime>

enum COLLECT_STATE
{
    NORMAL,
    FATPLSM,
    REDPLSM,
    OTHERPLSM
};

struct RecRst
{
    QString donorId;      //献血码
    QDateTime bgtime;     //采集开始时间
    QDateTime edtime_m;   //制备开始时间
    QDateTime edtime_e;   //最终结束时间

    QString dposlId;       //耗材ID
    QString naclId;        //盐水ID
    QString acId;          //抗凝剂ID
    QString prsvId;        //红细胞保养液ID
    QString oprtrId;       //护士ID
    QString oprtrName;     //护士姓名
    QString machineId;     //机器ID

    quint16 timelen;        //采集时长
    quint16 timeLen_e;        //总时长

    QString collectionvlm;        //全血采集量
    QString enrivlm;       //洗涤盐水量
    QString acdVlm;        //抗凝剂用量
    QString plsmVlm;       //血浆收集量
    quint16 SRBCVlm;       //悬浮红细胞量
    quint16 prsvVlm;       //保养液量

    QString status;               // 上传状态

    RecRst operator &=( const  RecRst& rst )
    {
        this->donorId  = rst.donorId;
        this->bgtime   = rst.bgtime;
        this->edtime_m = rst.edtime_m;
        this->edtime_e = rst.edtime_e;
        this->dposlId  = rst.dposlId;
        this->naclId   = rst.naclId;
        this->acId     = rst.acId;
        this->prsvId   = rst.prsvId;
        this->oprtrId  = rst.oprtrId;
        this->oprtrName = rst.oprtrName;
        this->machineId = rst.machineId;

        this->timelen = rst.timelen;
        this->collectionvlm  = rst.collectionvlm;
        this->enrivlm = rst.enrivlm;
//        this->timeLen_e = rst.timeLen_e;

//
//        this->acdVlm  = rst.acdVlm;
//        this->plsmVlm = rst.plsmVlm;
//        this->SRBCVlm = rst.SRBCVlm;
//        this->prsvVlm = rst.prsvVlm;

//        this->status  = rst.status;

        return *this;
    }

    Result_t toNetFormat()
    {
        Result_t  rst;

//        rst.cycleTimes              = circleNum;
//        rst.onewayWeight        = plsacircleVlm;
//        rst.weight                   = plsaVlm;
//        rst.sodiumChlorideDose = naclVlm;
//        rst.anticoagulantDose   = acdVlm;

//        // 采浆状态: 0:正常, 1:脂浆, 2:红浆, 3:其他异常
//        if ( QObject::tr("正常") == collectState )
//        {
//            rst.collectState = 0;
//        }
//        else if ( QObject::tr("脂浆") == collectState )
//        {
//            rst.collectState = 1;
//        }
//        else if ( QObject::tr("红浆") == collectState )
//        {
//            rst.collectState = 2;
//        }
//        else if ( QObject::tr("其他异常") == collectState )
//        {
//            rst.collectState = 3;
//        }

//        rst.donorNo                 = donorId;
//        rst.beginDate               = bgtime.toString("hhmm");
//        rst.endDate                 = edtime.toString("hhmm");
//        rst.twoNeedle              = twoNeedle;
//        rst.adverseReaction      = adverseReaction;
//        rst.remark                   = notify;
//        rst.nurse                     = oprtrId ;

//        rst.equipmentSet          = dposlId;
//        rst.sodiumChloride        = naclId ;
//        rst.anticoagulantBatch    = acId;
//        rst.procbldVol            = bldVlm;

        return rst;
    }
};

class ResultTable:public DBTable
{
        Q_OBJECT

public:
    explicit ResultTable( QString strName );

    bool create();
    bool addRec( const  RecRst& rst );
    bool delRec( const  RecRst& rst );
    bool delRec( QDateTime dt1, QDateTime dt2 );
    QLinkedList< RecRst > * queryRec( QString id );
    QLinkedList< RecRst > * queryRec( QDateTime dt1, QDateTime dt2 );
};

#endif // RESULTTABLE_H
