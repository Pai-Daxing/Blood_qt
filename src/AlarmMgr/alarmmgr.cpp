#include "alarmmgr.h"
#include "alarmstr.h"
#include "../DataMgr/datastorage.h"
#include"../DataMgr/datamgr.h"
#include </home/slrom/qtworks/led/wiringPi/wiringPi.h>
#include <qdatetime.h>

const AlarmInfo AlarmMgr::m_sAlarmInfoTable[AlmType_MAX] = {
    //类型                       级别                   栓锁
    {ALM_none,                  AlmLev_none,     Alalat_none},
    {ALM_ComError,              AlmLev_high,     ALARM_AUTOB},

    {ALM_centrHigh,        AlmLev_high,     ALARM_LATCH},//离心机速度过高(采血)
    {ALM_centrLow,         AlmLev_mid,      ALARM_LATCH},//离心机速度过低(采血)
    {ALM_bldPump_Error,    AlmLev_high,     ALARM_LATCH},//血泵方向错误(采血)   //血泵方向错误
    {ALM_bldPump_High,     AlmLev_mid,      ALARM_LATCH},//血泵速度过高
    {ALM_bldPump_Low,      AlmLev_mid,      ALARM_LATCH},    //血泵速度过低
    {ALM_acdPump_Low,      AlmLev_mid,      ALARM_LATCH},    //抗凝剂泵速度过低
    {ALM_acdPump_High,     AlmLev_mid,      ALARM_LATCH},    //抗凝剂泵速度过高
    {ALM_acdPump_Error,    AlmLev_high,     ALARM_LATCH},    //抗凝剂泵方向错误
    {ALM_prsvPump_Low,     AlmLev_mid,      ALARM_LATCH},    //保养液泵速度过低
    {ALM_prsvPump_High,    AlmLev_mid,      ALARM_LATCH},    //保养液泵速度过高
    {ALM_prsvPump_Error,   AlmLev_high,     ALARM_LATCH},    //保养液泵方向错误
    {ALM_cupLink,          AlmLev_mid,      ALARM_LATCH},    //离心杯漏液
    {ALM_coverOpen,        AlmLev_mid,      ALARM_LATCH},    //离心机盖未关闭
    {ALM_Vlv1_OpenError,   AlmLev_mid,      ALARM_AUTOB},     //盐水阀打开失败
    {ALM_Vlv1_CloseError,  AlmLev_mid,      ALARM_AUTOB},     //盐水阀关闭失败
    {ALM_Vlv2_OpenError,   AlmLev_mid,      ALARM_AUTOB},     //血液阀打开失败
    {ALM_Vlv2_CloseError,  AlmLev_mid,      ALARM_AUTOB},     //血液阀关闭失败
    {ALM_Vlv3_OpenError,   AlmLev_mid,      ALARM_AUTOB},     //血浆阀打开失败
    {ALM_Vlv3_CloseError,  AlmLev_mid,      ALARM_AUTOB},     //血浆阀关闭失败
    {ALM_Vlv4_CloseError,  AlmLev_mid,      ALARM_AUTOB},     //血浆阀关闭失败
    {ALM_Vlv4_OpenError,   AlmLev_mid,      ALARM_AUTOB},     //血浆阀打开失败
    {ALM_Vlv5_CloseError,  AlmLev_mid,      ALARM_AUTOB},     //血浆阀关闭失败
    {ALM_Vlv5_OpenError,   AlmLev_mid,      ALARM_AUTOB},     //血浆阀打开失败
    {ALM_Vlv6_CloseError,  AlmLev_mid,      ALARM_LATCH},     //血浆阀关闭失败
    {ALM_Vlv6_OpenError,   AlmLev_mid,      ALARM_LATCH},     //血浆阀打开失败
    {ALM_plsmweigh_Error,  AlmLev_mid,      ALARM_LATCH},     //血浆重量不正常
    {ALM_acdweigh_Error,   AlmLev_mid,      ALARM_LATCH},     //抗凝剂重量不正常
    {ALM_tooLong_Draw,     AlmLev_mid,      ALARM_LATCH},     //采血过程太长
    {ALM_tooLong_RBC,      AlmLev_mid,      ALARM_LATCH},     //红细胞制备时间太长
    {ALM_acdLineAir,       AlmLev_mid,      ALARM_AUTOB},     //抗凝剂管路发现空气
    {ALM_donorLineAir,     AlmLev_high,      ALARM_AUTOB},     //血员管路发现空气
    {ALM_presvLineAir,     AlmLev_high,      ALARM_AUTOB},     //保养液管路发现空气
    {ALM_DPMopen,          AlmLev_low,      ALARM_AUTOB},    //管路压力监测器打开
    {ALM_pressLow,         AlmLev_low,      ALARM_AUTOB},    //采血压力过低
    {ALM_pressHigh,        AlmLev_low,      ALARM_AUTOB},    //采血压力过高
    {ALM_buttonpress,      AlmLev_high,     ALARM_BUTTON},
};

AlarmMgr::AlarmMgr(QObject *parent) :
    QObject(parent),
    m_curType(ALM_none)
{
}

void AlarmMgr::init(QObject *sender)
{
    connect(sender, SIGNAL(setAlarmType(qint16)), this, SLOT(onSetAlarmType(qint16)));

    qRegisterMetaType<AlarmInfo>( );
    connect(this, SIGNAL(triggerAlarm(AlarmInfo)), this, SLOT(onTriggerAlarm(AlarmInfo)));
    connect(this, SIGNAL(cancelAlarm(AlarmInfo)), this, SLOT(onCancelAlarm(AlarmInfo)));
}

AlarmMgr& AlarmMgr::getInstance()
{
    static AlarmMgr instance;
    return instance;
}

void AlarmMgr::onSetAlarmType(qint16 newType)  //报警类型
{
    qint16  curType = (qint16)m_curType;
    if (newType != curType)
    {
        m_curType = (AlarmType)newType;
        if (ALM_none == m_curType)
        {   //清除当前报警
            emit cancelAlarm(m_sAlarmInfoTable[curType]);
        }
        else
        {   //触发新报警
            emit triggerAlarm(m_sAlarmInfoTable[newType]);
        }
    }
}

void AlarmMgr::onTriggerAlarm(const AlarmInfo &info)
{
    //报警存储
    AlarmRec alm;
    alm.time    = QDateTime::currentDateTime();
    alm.mid     = DataMgr::getInst().getUsrCfgStr(CFG_devID);
    alm.str      = AlarmString::getInstance().getStr( info.type ); ;
    alm.action = 1;

    DataStorage::getInstance().saveData( alm );
}

void AlarmMgr::onCancelAlarm(const AlarmInfo &info)
{
    //报警存储
    AlarmRec alm;
    alm.time    = QDateTime::currentDateTime();
    alm.mid     = DataMgr::getInst().getUsrCfgStr(CFG_devID);
    alm.str      = AlarmString::getInstance().getStr( info.type ); ;
    alm.action = 0;
    pinMode(7,OUTPUT);
    digitalWrite(7,HIGH);

    DataStorage::getInstance().saveData( alm );

}

