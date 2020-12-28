/*****************************************************************************************
Copyright:   all reserved
Filename:    alarmmgr.h
Author:      邹韵         version：1.0    Date：2012/9/
Description: 报警管理模块
             主要功能：
             1.报警静态信息管理：定义了系统使用的各种报警类型，以及各报警类型的报警静态信息表(如报警级别
                              、报警故障描述文字、报警故障原因文字、报警故障处理措施文字等)。
             2.报警实时信息管理：接收外部发射的"设置当前报警类型"信号并更新当前报警类型，在当前报警发
                              生变化时,向外部发射"触发*报警"或"关闭*报警"信号。外部也可随时向本模
                              块查询当前报警信息。
FuncionList:
             1.getInstance:   获取模块对象的引用。本模块为单件对象，外部必须通过本接口获取模块对象。
             2.init:          模块初始化函数，完成外部信号和内部槽函数的连接。
             3.getAlarmInfo:  获取当前报警的信息。
             4.triggerAlarm:  发射“触发*报警”信号。建议信号接收者以异步方式处理该信号。
             5.cancelAlarm:   发射“关闭*报警”信号。建议信号接收者以异步方式处理该信号。
             6.onSetAlarmType:处理外部"设置当前报警类型"信号(setAlarmType)的槽函数。
History:
             Date         Author         Modification

*****************************************************************************************/
#ifndef ALARMMGR_H
#define ALARMMGR_H

#include <QObject>
#include <QMetaType>
#include "../Protocol/alarms.h"

/*报警级别：决定报警的处理策略*/
enum AlarmLevel
{
    AlmLev_none = 0x00,
    AlmLev_high,             //高级
    AlmLev_mid,              //中级
    AlmLev_low,              //低级
};
enum AlarmLatch
{
    Alalat_none = 0x00,
    ALARM_AUTOB,             //不栓锁
    ALARM_LATCH,             //栓锁
    ALARM_BUTTON,            //按键栓锁(这是一个独立的栓锁状态)
};

/*报警信息：定义每个报警所包含的信息结构*/
struct AlarmInfo
{
    AlarmType    type;       //类型
    AlarmLevel   level;      //级别
    AlarmLatch   latch;      //栓锁
};
Q_DECLARE_METATYPE(AlarmInfo);

/*报警管理类*/
class AlarmMgr : public QObject
{
    Q_OBJECT

public:
    void   init(QObject* sender);

    /*获取报警管理器*/
    static AlarmMgr& getInstance();

    /*获取当前报警信息*/
    const AlarmInfo& getAlarmInfo()const  {return m_sAlarmInfoTable[m_curType];};

signals:
    /*触发报警信号
        info：该报警项静态信息
        主调：串口接收线程
        槽函数连接方式：请使用queue方式连接该信号
        */
    void triggerAlarm(const AlarmInfo& info);
    /*取消报警信号
        info：该报警项静态信息
        主调：串口接收线程
        槽函数连接方式：请使用queue方式连接该信号
        */
    void cancelAlarm(const AlarmInfo& info);

public slots:
    /*描述：更新报警模块实时状态。
        处理：发现变化时发送“触发报警”信号
        主调：串口接收线程
       */
    void onSetAlarmType(qint16 newType);

private slots:
    /*描述：报警信号的槽函数
        处理：报警存储 （报警音由UI线程处理）
        */
    void onTriggerAlarm(const AlarmInfo& info);

    void onCancelAlarm(const AlarmInfo& info);

private:
    explicit AlarmMgr(QObject *parent = 0);

private:
    AlarmType m_curType; //当前报警类型

    const static AlarmInfo m_sAlarmInfoTable[AlmType_MAX];  //报警静态信息表
};

#endif // ALARMMGR_H
