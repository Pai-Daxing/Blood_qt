#ifndef UIADAPTOR_H
#define UIADAPTOR_H

#include <QObject>
#include <QQuickItem>
#include <QProcess>
#include "../AlarmMgr/alarmmgr.h"

class UiAdaptor : public QObject
{
    Q_OBJECT

public:
    explicit UiAdaptor(QObject *parent = nullptr);

    //////////////////////////////////////////
    ///   以下是供QML调用的接口
    /// //////////////////////////////////////
    Q_INVOKABLE QVariantList getParamSet();
    Q_INVOKABLE bool saveParam(QVariantList params);
    Q_INVOKABLE void saveConsequence(QVariantList consequence);

    Q_INVOKABLE void bootSelfTest(void);
    Q_INVOKABLE void bootChkFailed(void);
    Q_INVOKABLE void bootQuit(void);
    Q_INVOKABLE void startSelfTest(void);
    Q_INVOKABLE void fillfailed(void);
    Q_INVOKABLE void startDrawProc(void);
    Q_INVOKABLE void startDrawing(void);
    Q_INVOKABLE void confirmLine(void);
    Q_INVOKABLE void starDebug(void);
    Q_INVOKABLE void exitDebug(void);
    Q_INVOKABLE void confirmACDRdy(void);
    Q_INVOKABLE void dbSetBool(int index, short val);
    Q_INVOKABLE void dbSetBldPSpeed(short bldS);
    Q_INVOKABLE void dbSetAcdPSpeed(short acdS);
    Q_INVOKABLE void dbSetPresvPSpeed(short naclS);
    Q_INVOKABLE void dbSetBldPDir(short val);
    Q_INVOKABLE void popupalarmblood(void);
    Q_INVOKABLE void popupalarmpreparation(void);
    Q_INVOKABLE void popupalarmexit(void);
    Q_INVOKABLE void bldSpeedAdd(void);
    Q_INVOKABLE void bldSpeedReduce(void);
    Q_INVOKABLE void bldSpeedStart(void);
    Q_INVOKABLE void bldSpeedStop(void);
    Q_INVOKABLE void scaledOkOne(short num);
    Q_INVOKABLE void scaledOkTwo(short num1);
    Q_INVOKABLE void bldScaOkThree(short num2);
    Q_INVOKABLE void bldScaOkFour(short num3);
    Q_INVOKABLE void quitselftest(void);
    Q_INVOKABLE void colNPadd(void);
    Q_INVOKABLE void colNPred(void);
    Q_INVOKABLE void colNext(void);
    Q_INVOKABLE void colNPsta(void);
    Q_INVOKABLE void colNPstop(void);
     Q_INVOKABLE void endCollect(void);

    Q_INVOKABLE void scaledstart(void);
    Q_INVOKABLE void scaledexit(void);



    Q_INVOKABLE void stoppress(void);
    Q_INVOKABLE void execCmd(QString cmd);
    Q_INVOKABLE void paramOK(short num1,short num2,short num3,short num4,short num5,short num6);
    Q_INVOKABLE void paramsave(int num1,int num2,int num3,int num4,int num5,int num6);
    Q_INVOKABLE void resultp(int num1,int num2);


signals:
    void timerUpdate(QString str);
    void valveOfBloodChanged(bool newValue);            //“血液阀开关更新”信号 1开 0关
    void valveOfPlasmaChanged(bool newValue);           //“血浆阀开关更新”信号 1开 0关
    void valveOfNaClChanged(bool newValue);             //“盐水阀开关更新”信号 1开 0关
    void valveOfACDChanged(bool newValue);              //“抗凝阀开关更新”信号 1开 0关
    void valveOfPresvChanged(bool newValue);            //“保养液阀开关更新”信号 1开 0关
    void valveOfRBCChanged(bool newValue);              //“红细胞阀开关更新”信号 1开 0关
    void valveOfWasteChanged(bool newValue);            //“废液阀开关更新”信号 1开 0关
    void airDetectorOfBloodChanged(bool newValue);      //“血液空探更新”信号 1液体 0空气
    void airDetectorOfAcdChanged(bool newValue);        //“抗凝剂空探更新”信号 1液体 0空气
    void airDetectorOfPresvChanged(bool newValue);        //“抗凝剂空探更新”信号 1液体 0空气
    void dpmChanged(bool newValue);                     //“压力监测器状态更新”信号 1已安装 0未安装
    void leakChanged(bool newValue);                    //“漏夜监测器状态更新”信号 1已漏液 0未漏液
    void coverChanged(bool newValue);                   //“离心机盖状态更新”信号 1已关盖 0未关盖
    void lineSensorChanged(bool newValue);              //“管路探测器更新”信号 1发现红细胞 0未发现红细胞
    void versionChanged(qint16 newValue);
    void collecttimeChanged(qint16 newValue);
    void pressureOfDpmChanged(qint16 newValue);         //“压力监测值更新”信号
    void negapressureOfDpmChanged(qint16 a);
    void volumeOfPlasmaChanged(qint16 newValue);        //“血浆量更新”信号
    void volumeOfACDChanged(qint16 newValue);           //“抗凝剂量更新”信号
    void flowRateOfBloodPumpChanged(qint16 newValue);   //“血泵流速更新”信号
    void flowRateOfACDPumpChanged(qint16 newValue);     //“抗凝剂泵流速更新”信号
    void flowRateOfPresvPumpChanged(qint16 newValue);   //“保养液泵流速更新”信号
    void speedOfCentrifugeChanged(qint16 newValue);     //“离心机转速更新”信号
    void lineDetectorChanged(qint16 newValue);          //“管路探测器更新”信号

    void bloodChanged(qint16 newValue);
    void drawspeedChanged(qint16 newValue);
    void collectspeedChanged(qint16 newValue);
    void linecoffChanged(qint16 newValue);
    void bpaprateChanged(qint16 newValue);
    void prsspeedChanged(qint16 newValue);

    void bPrealChanged(qint16 newValue);
    void aPrealChanged(qint16 newValue);
    void nPrealChanged(qint16 newValue);

    void targetRateOfDrawChanged(qint16 newValue);
    void targetRateOfCollectChanged(qint16 newValue);

    void volumeOfNaClChanged(qint16 newValue);          //“盐水量更新”信号
    void volumeOfBloodChanged(qint16 newValue);         //“全血采集量量更新”信号
    void volumeOfBloodPgbarChanged(qint16 newValue);
    void volumeOfPresvChanged(qint16 newValue);         //“保养液量更新”信号
    void volumeOfSRBCChanged(qint16 newValue);          //“悬红量更新”信号
    void volumeOfSRBCPgbarChanged(qint16 newValue);     //"悬红量pgbar更新"
    void volumeOfSRBCVolChanged(qint16 newValue);      //"浓缩量更新"
    void stopButtonPressed();
    void netconnect();
    void netconnectfaild();
    void biganButtonPressed();
    void timeLenChanged(qint16 newValue);               //采集时间

    void showSelftTestAirDs();  //
    void showSelftTestVlvs();  //
    void showSelftTestPumps();  //
    void showSelftTestline();  //
    void showSelftTestCF();  //
    void showSelftTestDPM();  //
    void showSelftTestScales();  //
    void showSelftTestleak();  //

    void showSfChkMsg(QString str);      //安全自检信息

    void setCSS2StandBy();
    void setCSS2WaitCoverOpen();
    void setCSS2WaitCoverClose();
    void setCSS2Succeed();
    void setCSS2SelfTestFailed(QString errStr);
    void setCSS2Safe();
    void setCSS2SafeChk();
    void setCSS2SafeChkFailed(QString errStr);
    void setCSS2WaitCup();
    void setCSS2WaitLine();
    void setCSS2WaitACD();
    void setCSS2Prime();
    void cssFillFailed();
    void setCSS2ReadyDraw();
    void setCSS2Draw();
    void setCSS2Washing();
    void setCSS2Collect();
    void setCSS2Halt();
    void setCSS2CollectEnd();  //采集结束，等到用户确认结果
    void setCSSdrawpower();
    void setCSScollectpower();
    void setCSScontinueOrover();
    void button();

    void raiseAlarm(qint16 lv, QString str, QString details);
    void cancelAlarm();

    void UICmd(quint16 cmd, const short *params, unsigned char num);
//    void times();

public slots:

    //////////////////////////////////////////
    ///   以下是从系统其它模块发过来的信号处理槽
    /// //////////////////////////////////////

    void onCtrlSysStatusChanged(qint16 newStatus);

    void onUILoadCompleted();

    void onAlarmStart(AlarmInfo alarm);
    void onCancelAlarm(AlarmInfo alarm);
private:
    QProcess   *m_pExecProc;
//    void inittime(void);
//    void timerUpdate(void);


};

#endif // UIADAPTOR_H
