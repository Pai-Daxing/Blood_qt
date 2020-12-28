#ifndef PARAMMGR_H
#define PARAMMGR_H

#include <QObject>
#include <QFile>
#include <QIntValidator>
#include "../DataMgr/datastorage.h"
#include "../Protocol/commands.h"

class NIntValidator : public QIntValidator
{
    Q_OBJECT
public:
    explicit NIntValidator(QObject *parent = 0);
    NIntValidator(int min, int max, QObject *parent = 0);
    void fixup(QString &input) const;
    QValidator::State validate ( QString & input, int & pos ) const;
};

struct ParamSetting    //“设置采集参数”命令参数类型
{
    quint16 bloodVlm;    //采集目标量
    quint16 cSpeed;      //采集速度
    quint16 cRBCSpeed;   //收集红细胞速度
    quint16 lineDSens;    //管探灵敏度
    quint16 presvSpeed;   //保养液泵采集速度
    quint16 anti;         //抗凝比
    bool operator ==(const ParamSetting& that){
        return (bloodVlm == that.bloodVlm && cSpeed == that.cSpeed
                && cRBCSpeed == that.cRBCSpeed && lineDSens == that.lineDSens );
    }

    bool operator !=(const ParamSetting& that){
        return !(bloodVlm == that.bloodVlm && cSpeed == that.cSpeed
                 && cRBCSpeed == that.cRBCSpeed && lineDSens == that.lineDSens);
    }
};

struct RecRTParam
{
    quint16 bldVlm;        //全血采集量
    quint16 naclVlm;       //洗涤盐水量
    quint16 acdVlm;        //抗凝剂用量
    quint16 plsmVlm;       //血浆收集量
    quint16 SRBCVlm;       //悬浮红细胞量
    quint16 prsvVlm;       //保养液量    

    quint16 timeLen;        //时长
    quint16 pumpStopTime;   //泵停时长

    qint16 pumpSpeed;     //泵速度
    qint16 ACDpumpSpeed;  //抗凝泵速度
    qint16 presvPumpSpeed;  //保养液泵速度
    qint16 centrifugeSpeed; //离心机转速
    qint16 lineDetector;    //管探
    qint16 prsDPM;    //管探
    qint16 version;      //版本信息
    qint16 collecttime;  //采集时长
    qint16 blood;
    qint16 draw_speed;
    qint16 collect_speed;
    qint16 linecoff;
    qint16 bpap_rate;
    qint16 prs_speed;
    qint16 BPreal; //血泵实际速度
    qint16 APreal; //抗凝剂实际速度
    qint16 NPreal;  //保养液实际速度
    quint16 SRBCVol;       //浓缩量


};

typedef union {
  struct {
      unsigned Bld_V:  1;   //血液阀
      unsigned Plsm_V: 1;   //血浆阀
      unsigned NaCl_V: 1;   //盐水阀
      unsigned Presv_V:1;   //保养液阀
      unsigned RBC_V:  1;   //红细胞阀
      unsigned Waste_V:1;   //废液阀
      unsigned DPM:    1;
      unsigned Leak_D  :1;
      unsigned Cover   :1;
      unsigned Bld_airD:1;   //血液空探
      unsigned ACD_airD:1;   //抗凝剂空探
      unsigned Presv_airD:1; //保养液空探
      unsigned Line_D  :1;
      unsigned PumpOn  :1;
  };
  struct {
    unsigned w:32;
  };
} BoolParam_t;

class ParamMgr : public QObject
{
    Q_OBJECT

public:
    virtual ~ParamMgr();
    void   init(QObject* sender);

    /*获取参数管理器*/
    static ParamMgr* getInstance();

    void setPlasmaUnitToML(bool ml);
    bool isPlasmaUnitML();
    void setFromPowerOffFlag( bool isPf );
    /*获取采集运行实时数据*/

    /*获取采集结果*/
    bool   getRst(RecRst& rst)const;

    /*设置采浆信息*/

    /*设置/获取当次采集参数值*/
    void   getParamSetting(ParamSetting& params)const {params = m_params;} //获取采集参数值
    virtual bool   setParamSetting(const ParamSetting& params);                     //设置采集参数值（发射“采集参数设置值更新”信号）
    bool   setParamSettingsToDefault();                                     //设置采集参数值为用户缺省值（发射“采集参数设置值更新”信号）
    void   setParamSettingToLatest();                                       //设置采集参数值为最近用户设置值
    bool   setTargetDrawRate(qint16 value);                                 //设置采集速度（发射“采集速度设置值更新”信号）
    bool   setTargetCollectRate(qint16 value);                              //设置制备速度（发射“制备速度设置值更新”信号）
    bool   getTargetSwitchOfPump()const {return m_bPumpOn;}                //获取泵开关设置值
    bool   setTargetSwitchOfPump(bool value);                               //设置泵开关值（发射“泵启停设置值更新”信号）
    virtual bool sendStepDrawParam();                    //设置采集参数值（血浆置换分步发采集目标值）
    virtual void endDrawing();
    /*获取采集参数值设置范围*/
    const NIntValidator* getRangeOfPlsmVol() const {return &m_plsmVolRange;}
    const NIntValidator* getRangeOfPlsmCycVol() const {return &m_plsmCycVolRange;}
    const NIntValidator* getRangeOfNaclVol() const {return &m_naclVolRange;}
    const NIntValidator* getRangeOfNaclCycVol() const {return &m_naclCycRange;}
    NIntValidator* getRangeOfDrawRate() {return &m_drawRateRange;}
    NIntValidator* getRangeOfReturnRate() {return &m_rtnRateRange;}
    const NIntValidator* getRangeOfCuffPrs() const {return &m_cuffPrsRange;}
    const NIntValidator* getRangeOfAcFactor() const {return &m_acFactorRange;}
    const NIntValidator* getRangeOfSens() const {return &m_sensRange;}

    void setParamRange( NIntValidator* p, int bottom, int top );
signals:
    //以下信号由串口接收线程发射，请使用queue方式连接该信号
    void pressureOfDpmChanged(qint16 newValue);         //“压力监测值更新”信号
    void negapressureOfDpmChanged(qint16 a);     //“负压力监测值更新”信号
    void volumeOfPlasmaChanged(qint16 newValue);        //“血浆量更新”信号
    void volumeOfACDChanged(qint16 newValue);           //“抗凝剂量更新”信号
    void volumeOfNaClChanged(qint16 newValue);          //“盐水量更新”信号
    void volumeOfBloodChanged(qint16 newValue);         //“全血采集量量更新”信号
    void volumeOfBloodPgbarChanged(qint16 newValue);

    void volumeOfPresvChanged(qint16 newValue);         //“保养液量更新”信号
    void versionChanged(qint16 newValue);
    void collecttimeChanged(qint16 newValue);
    void volumeOfSRBCChanged(qint16 newValue);          //“悬红量更新”信号
    void volumeOfSRBCPgbarChanged(qint16 newValue);     //““悬红量pgbar更新”信号”
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

    void valveOfBloodChanged(bool newValue);            //“血液阀开关更新”信号 1开 0关
    void valveOfPlasmaChanged(bool newValue);           //“血浆阀开关更新”信号 1开 0关
    void valveOfNaClChanged(bool newValue);             //“盐水阀开关更新”信号 1开 0关
    void valveOfACDChanged(bool newValue);              //“抗凝阀开关更新”信号 1开 0关
    void valveOfPresvChanged(bool newValue);            //“保养液阀开关更新”信号 1开 0关
    void valveOfRBCChanged(bool newValue);              //“红细胞阀开关更新”信号 1开 0关
    void valveOfWasteChanged(bool newValue);            //“废液阀开关更新”信号 1开 0关
    void airDetectorOfBloodChanged(bool newValue);      //“血液空探更新”信号 1液体 0空气
    void airDetectorOfAcdChanged(bool newValue);        //“抗凝剂空探更新”信号 1液体 0空气
    void airDetectorOfPresvChanged(bool newValue);      //“保养液空探更新”信号 1液体 0空气
    void dpmChanged(bool newValue);                     //“压力监测器状态更新”信号 1已安装 0未安装
    void leakChanged(bool newValue);                    //“漏夜监测器状态更新”信号 1已漏液 0未漏液
    void coverChanged(bool newValue);                   //“离心机盖状态更新”信号 1已关盖 0未关盖
    void lineSensorChanged(bool newValue);              //“管路探测器更新”信号 1发现红细胞 0未发现红细胞
    void setDpmAlarmStatus(qint16 status);             // 压力报警状态信号 0：正常 1：预报警 2：报警       李立策20130709
    void pumpStatusChanged(bool on);                    //由下位机上发泵启停状态           李立策20131219
    void volumeSampleTip();                                  // 留样提示信号                        李立策20150508
    void COMdata(QString str);                               // 串口数据
    //以上信号由串口接收线程发射，请使用queue方式连接该信号

    void timeLenChanged(qint16 newValue);
    void timeOfPumpStopChanged(qint16 newValue);        //“泵停时间更新”信号

    //以下信号由调用“当次采集参数设置”接口的线程发射
    //void paramSettingChanged(ParamSetting params);      //“采集参数设置值更新”信号
    void targetRateOfDrawChanged(qint16 newValue);      //“采集速度设置值更新”信号
    void targetRateOfCollectChanged(qint16 newValue);    //“制备速度设置值更新”信号
    void targetSwitchOfPumpChanged(bool bOn);           //“泵启停设置值更新”信号
    void targetBldVlmChanged(qint16);
    //以上信号由调用“当次采集参数设置”接口的线程发射

    void unitChanged(bool isML);
public slots:
    /* 描述：更新实时参数数据。
       处理：发现变化时发送“**更新”信号
       主调：串口接收线程
    */
    void onSetDpmPrs(qint16 newValue);           //“压力监测值更新”信号
    void onSetPlasmaVlm(qint16 newValue);        //“血浆量更新”信号
    void onSetACDVlm(qint16 newValue);           //“抗凝剂量更新”信号
    void onSetNaClVlm(qint16 newValue);          //“盐水量更新”信号
    void onSetBPSpeed(qint16 newValue);          //“血泵流速更新”信号
    void onSetAPSpeed(qint16 newValue);          //“抗凝剂泵流速更新”信号
    void onSetPresvPSpeed(qint16 newValue);      //“保养液泵流速更新”信号
    void onSetCFSpeed(qint16 newValue);          //“离心机转速更新”信号
    void onSetLineDetector(qint16 newValue);     //“管路探测器更新”信号
    void onSetPresvVlm(qint16 newValue);         //“保养液量更新”信号
    void onSetBloodVlm(qint16 newValue);         //“全血采集量更新”信号
    void onSetBloodPgbarVlm(qint16 newValue);
    void onSetRBCVlm(qint16 newValue);           //“悬红量更新”信号
    void onSetRBCPgbarVlm(qint16 newValue);           //“悬红量更新”信号
    void onSetBoolParam(qint32 newValue);             //开关量更新信号
    void onComData(QString str);             //
    void onSetVersion(qint16 newValue);
    void onSetcollecttime(qint16 newValue);

    void onSetBlood(qint16 newValue);
    void onSetDraw_speed(qint16 newValue);
    void onSetCollect_speed(qint16 newValue);
    void onSetLinecoff(qint16 newValue);
    void onSetBpap_rate(qint16 newValue);
    void onSetPrs_speed(qint16 newValue);

    void onSetBPreal(qint16 newValue);
    void onSetAPreal(qint16 newValue);
    void onSetNPreal(qint16 newValue);



    void onColctBegin();    //"开始采集"信号
    void onColctEnd();      //"采集结束"信号

    void onDebugBegin(){m_bSendChange = true;};
    void onDebugEnd(){m_bSendChange = false; m_pRecRT->timeLen = -1;}; // 调试界面退出后，计时器清零 llc20150716

    //llc 20131205 包括“设置采集参数值为最近用户设置值”和重置采集时间等
    void onReturnFromPowerOff( bool bQuit );

    void saveIDs();
    void saveBeginTime();
protected:
    void timerEvent( QTimerEvent *event );
private:
    void saveLatestParamSetting(const ParamSetting& param);
    void saveLatestCuffSetting(bool bCuffStatus);
    void saveLatestPumpSetting(bool bPumpStatus);
    explicit ParamMgr(QObject *parent = 0);
private:
    qint16 m_nTimerId;
//    void Delay_MSec(unsigned int msec);

    RecRst     *m_pRecRst;
    RecRTParam *m_pRecRT;

    BoolParam_t m_BoolVar;

    bool   m_bSendChange;

    bool   m_bPumpOn;
    ParamSetting  m_params;

    RecRst m_rslt;  //最近一次采集结果

    NIntValidator m_plsmVolRange;
    NIntValidator m_plsmCycVolRange;
    NIntValidator m_naclVolRange;
    NIntValidator m_naclCycRange;
    NIntValidator m_drawRateRange;
    NIntValidator m_rtnRateRange;
    NIntValidator m_cuffPrsRange;
    NIntValidator m_acFactorRange;
    NIntValidator m_sensRange;
    NIntValidator m_plasRepVolRange;
    NIntValidator m_naclRepVolRange;

    QFile   m_paramFile; //用于掉电恢复，保存当前采集的参数
    bool    m_bQuitPowerOff; //掉电后开机，直接退出，采集时间处理标识
    bool    m_bCountTime;    // 掉电后开机,用户操作前不计算采集时长
    bool    m_bUnitML;
};

#endif // PARAMMGR_H
