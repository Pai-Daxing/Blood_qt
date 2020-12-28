#ifndef STATUSMGR_H
#define STATUSMGR_H

#include<QObject>
#include "../Protocol/status.h"
#include "../Protocol/alarms.h"

typedef struct _TestErrMsg{
    ErrorCode code;
    QString str;
} TestErrMsg;

class StatusMgr : public QObject
{
    Q_OBJECT

public:
    enum
    {
        SelftestItemNum = 15,      //自检项目个数
        SatyChkItemNum = 7,        //采集安全检查项目个数
    };
public:
    void   init(QObject* sender);
    /*获取状态管理器*/
    static StatusMgr& getInstance();

    /*获取控制系统当前状态值*/
    ControlSystemStatus getControlSystemStatus()const {return m_curStatus;}
     /*获取控制系统前一个状态值*/
    ControlSystemStatus getPreControlSystemStatus()const {return m_preStatus;}
//    /*查询自检是否通过*/
//    bool  isSelftestPassed()const {return SelftestItemNum == m_count_ST;};
//    /*查询采集安全检查是否通过*/
//    bool  isSafytestPassed()const {return SatyChkItemNum == m_count_CLT;};

    WorkStatus getCurWorkStatus() { return m_workingStatus; }
    void setWorkStatus( WorkStatus ws ){ m_workingStatus = ws; }

    int getSTErrNo(){return mSTErrNo;}
    QString getErrStr();

    bool isQuitDrawed() { return mbIsQuitDraw; }
    void setQuitDrawed( bool qd ){ mbIsQuitDraw = qd; }
signals:
    /*描述：“控制系统状态改变”信号
        主调：串口接收线程
        槽函数连接方式：请使用queue方式连接该信号
       */
    void controlSystemStatusChanged(qint16 newStatus);
    void controlSystemConnected(qint16 newStatus); //和控制系统建立了通信连接

    void enterAlarmPause();
    void leaveAlarmPause();

    void colctBegin();
    void colctPauseRecover(); //从报警暂停恢复为采集暂停
    void colctEnd();
    void respStepOver();

    void enterDebug();
    void leaveDebug();

public slots:
    /*描述：更新控制系统实时状态。
       处理：发现变化时发送“控制系统状态改变”信号
       主调：串口接收线程
    */
    void onSetControlSystemStatus(qint16 newStatus);

    void updateErrNo(qint16 no);
private slots:
    /* 描述：“控制系统状态改变”信号的槽函数
         处理：维护自检结果
   */
    void onControlSystemStatusChanged(qint16 newStatus);

private:
    explicit StatusMgr(QObject *parent = 0);

private:
    ControlSystemStatus m_curStatus;  //控制系统当前状态
    ControlSystemStatus m_preStatus;  //控制系统前一个状态
    int mSTErrNo;                     //自检错误码
    WorkStatus               m_workingStatus;  // 工作状态， lilice  20130805
    bool mbIsQuitDraw;              //放弃本次采集标志位    lilice 20150513
};


#endif // STATUSMGR_H
