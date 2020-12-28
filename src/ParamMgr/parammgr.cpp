#include "../global.h"
#include<QTimerEvent>
#include<QDebug>
#include "parammgr.h"
#include<qdatetime.h>
#include"../StatusMgr/statusmgr.h"
#include"../DataMgr/datamgr.h"
#include "../SerialApp/serialapp.h"
#include "../DataMgr/netdatamgr.h"
#include "../DataMgr/cfg.h"
#include <QTime>


NIntValidator::NIntValidator(QObject *parent) :
    QIntValidator(parent)
{
}

NIntValidator::NIntValidator(int min, int max, QObject *parent) :
    QIntValidator(min, max, parent)
{

}

void NIntValidator::fixup(QString &input) const
{
    input = QString("%1").arg(bottom());
}

QValidator::State NIntValidator::validate ( QString & input, int & pos ) const
{
    if ( !input.isEmpty() )
    {
        input = QString("%1").arg( input.toInt() );
    }
    return QIntValidator::validate( input, pos );
}

const int gSampleVol = 80;             //留样提示容量
const int gFirstRoundVol = 270;   //第一循环的处理量，即采样提示范围
const int gMinPlasmaVol =100;      //血浆置换每次最小允许量
const int gTareTargetPlasmaVol = 20;      //目标值误差范围
const int gPerbagDefaultVol = 600;         //转移量缺省值，如果设置参数非法，则使用该值
ParamMgr::ParamMgr(QObject *parent) :
    QObject(parent),
    m_nTimerId(0),
    m_bSendChange(true),
    m_bPumpOn(false),
    m_plsmVolRange(100, 1000),
    m_plsmCycVolRange(100, 400),
    m_naclVolRange(0, 500),
    m_naclCycRange(0, 500),
    m_drawRateRange(20, TOP_RATE_CE),
    m_rtnRateRange(20, TOP_RATE_CE),
    m_cuffPrsRange(40, 99),
    m_acFactorRange(8, 16),
    m_sensRange(80, 95),
    m_plasRepVolRange(100, 5000),
    m_naclRepVolRange(0, 5000),
    m_bQuitPowerOff(false),
    m_bCountTime(true)
{
    m_params.bloodVlm  = DataMgr::getInst().getUsrCfgInt(CFG_targetVlm);
    m_params.cSpeed    = DataMgr::getInst().getUsrCfgInt(CFG_collectSpeed);
    m_params.cRBCSpeed = DataMgr::getInst().getUsrCfgInt(CFG_collectRBCSpeed);
    m_params.lineDSens = DataMgr::getInst().getUsrCfgInt(CFG_lineDSens);
    m_bUnitML = (ml == DataMgr::getInst().getUsrCfgInt(CFG_weightUnit));

    m_pRecRst   = new RecRst();
    m_pRecRT    = new RecRTParam();
    m_BoolVar.w = 0;

    m_paramFile.setFileName("./Datas/CFG/ParamFile");
}

ParamMgr::~ParamMgr()
{
    if (m_nTimerId != 0)
    {
        killTimer(m_nTimerId);
    }
}

void ParamMgr::init(QObject* sender)
{
    connect(sender, SIGNAL(setBoolParam(qint32)),this,    SLOT(onSetBoolParam(qint32)));
    connect(sender, SIGNAL(setAPSpeed(qint16)),this,      SLOT(onSetAPSpeed(qint16)));
    connect(sender, SIGNAL(setBPSpeed(qint16)),this,      SLOT(onSetBPSpeed(qint16)));
    connect(sender, SIGNAL(setPresvPSpeed(qint16)),this,  SLOT(onSetPresvPSpeed(qint16)));
    connect(sender, SIGNAL(setLineDetector(qint16)),this, SLOT(onSetLineDetector(qint16)));
    connect(sender, SIGNAL(setDpm(qint16)),this,          SLOT(onSetDpmPrs(qint16)));
    connect(sender, SIGNAL(setCFSpeed(qint16)),this,      SLOT(onSetCFSpeed(qint16)));
    connect(sender, SIGNAL(setACDVlm(qint16)),this,       SLOT(onSetACDVlm(qint16)));
    connect(sender, SIGNAL(setNaClVlm(qint16)),this,      SLOT(onSetNaClVlm(qint16)));
    connect(sender, SIGNAL(setPlasmaVlm(qint16)),this,    SLOT(onSetPlasmaVlm(qint16)));
    connect(sender, SIGNAL(setPresvVlm(qint16)),this,     SLOT(onSetPresvVlm(qint16)));
    connect(sender, SIGNAL(setBloodVlm(qint16)),this,     SLOT(onSetBloodVlm(qint16)));
    connect(sender, SIGNAL(setBloodVlm(qint16)),this,     SLOT(onSetBloodPgbarVlm(qint16)));
    connect(sender, SIGNAL(setRBCVlm(qint16)),this,       SLOT(onSetRBCVlm(qint16)));
    connect(sender, SIGNAL(setRBCVlm(qint16)),this,       SLOT(onSetRBCPgbarVlm(qint16)));
    connect(sender, SIGNAL(COMStr(QString)),this,        SLOT(onComData(QString)));
    connect(sender, SIGNAL(setVersion(qint16)),this,        SLOT(onSetVersion(qint16)));
    connect(sender, SIGNAL(setCollecttime(qint16)),this,    SLOT(onSetcollecttime(qint16)));

    connect(sender, SIGNAL(setBlood(qint16)),this,    SLOT(onSetBlood(qint16)));
    connect(sender, SIGNAL(setDraw_speed(qint16)),this,    SLOT(onSetDraw_speed(qint16)));
    connect(sender, SIGNAL(setCollect_speed(qint16)),this,    SLOT(onSetCollect_speed(qint16)));
    connect(sender, SIGNAL(setLinecoff(qint16)),this,    SLOT(onSetLinecoff(qint16)));
    connect(sender, SIGNAL(setBpap_rate(qint16)),this,    SLOT(onSetBpap_rate(qint16)));
    connect(sender, SIGNAL(setPrs_speed(qint16)),this,    SLOT(onSetPrs_speed(qint16)));

    connect(sender, SIGNAL(setBPreal(qint16)),this,    SLOT(onSetBPreal(qint16)));
    connect(sender, SIGNAL(setAPreal(qint16)),this,    SLOT(onSetAPreal(qint16)));
    connect(sender, SIGNAL(setNPreal(qint16)),this,    SLOT(onSetNPreal(qint16)));

    connect(&StatusMgr::getInstance(), SIGNAL(colctBegin()), this, SLOT(onColctBegin()));
    connect(&StatusMgr::getInstance(), SIGNAL(colctEnd()), this, SLOT(onColctEnd()));
    connect(&StatusMgr::getInstance(), SIGNAL(enterDebug()), this, SLOT(onDebugBegin()));
    connect(&StatusMgr::getInstance(), SIGNAL(leaveDebug()), this, SLOT(onDebugEnd()));

    m_nTimerId = startTimer(1000);
}

ParamMgr* ParamMgr::getInstance()
{
    static ParamMgr *pParamMgr = 0;

    if ( NULL == pParamMgr )
    {
        pParamMgr = new ParamMgr();
    }


    return pParamMgr;
}

void ParamMgr::setFromPowerOffFlag( bool isPf )
{
    // 如果是掉电后重启则先不计时间
    m_bCountTime = !isPf;

    setParamSettingToLatest();
}

void ParamMgr::setPlasmaUnitToML(bool ml)
{
    if ( (m_bUnitML && !ml ) || (!m_bUnitML && ml) )
    {
        m_bUnitML = ml;
        emit unitChanged( m_bUnitML );
    }
}

bool ParamMgr::isPlasmaUnitML()
{
    return m_bUnitML;
}

void ParamMgr::setParamRange( NIntValidator* p, int bottom, int top )
{
    p->setRange( bottom, top );
}

/***********************************************************************
*  外部接口，掉电恢复，需恢复上次采集参数设置，采集开始时间以及时长
*  而采集结果数据由下位机保存，不作处理
*
* Author              Date               Action
* lilice              2013/12/05          create
***********************************************************************/
void ParamMgr::onReturnFromPowerOff( bool bQuit )
{
    ////这句话得仔细测试
    m_pRecRst->bgtime = QDateTime::fromTime_t(DataMgr::getInst().getUsrCfgInt( CFG_beginTime ));
    m_pRecRT->timeLen = DataMgr::getInst().getUsrCfgInt( CFG_timeLen );

    quint32 ntime = QDateTime::currentDateTime().toTime_t();

    if ( bQuit )
    {
        m_bQuitPowerOff = true;
    }
    else
    {        
        m_pRecRT->timeLen = ntime - m_pRecRst->bgtime.toTime_t();

        if ( m_pRecRT->timeLen >= 28800)  //大于8小时的就从头开始计算
        {
            m_pRecRT->timeLen = 0;
            m_pRecRst->bgtime = QDateTime::fromTime_t(ntime);
        }
    }

    m_pRecRst->donorId = DataMgr::getInst().getUsrCfgStr(CFG_donorIdSet); //供浆员ID录入设置值
    m_pRecRst->dposlId = DataMgr::getInst().getUsrCfgStr(CFG_dspslIdSet); //耗材ID录入设置值
    m_pRecRst->acId    = DataMgr::getInst().getUsrCfgStr(CFG_acdIdSet );     //抗凝剂ID录入设置值
    m_pRecRst->naclId  = DataMgr::getInst().getUsrCfgStr(CFG_salineIdSet );  //盐水ID录入设置值
    m_pRecRst->oprtrId = DataMgr::getInst().getUsrCfgStr(CFG_oprtrIdset);   //操作者ID录入设置值

    m_bCountTime = true;
}

void ParamMgr::onSetDpmPrs(qint16 newValue)
{
    if (m_bSendChange &&
            newValue != m_pRecRT->prsDPM)
    {
        // 0:无报警 1：预报警 2：报警
        //根据下位机的判断条件做了修改，上下位机应一直保持统一     李立策20130710
        qint16 status = 0;
        m_pRecRT->prsDPM = newValue;
        emit pressureOfDpmChanged(newValue);


        if((newValue) < 0)
        {
            qint16 a = qAbs(newValue);
            emit negapressureOfDpmChanged(a);
        }

        if (  CSS_drawing == StatusMgr::getInstance().getControlSystemStatus() )
        {
            // 出现高压或者低压报警时，机器状态是报警暂停，不会进入这里
            if ( newValue <= -40 )
            {
                status = 1;
            }
        }

        if( CSS_alarm_paused !=  StatusMgr::getInstance().getControlSystemStatus() )
        {
            // 避免出现报警时，压力条颜色恢复默认值
            emit setDpmAlarmStatus( status );
        }
    }
}

//void ParamMgr::Delay_MSec(unsigned int msec)
//{
//    QTime _Timer = QTime::currentTime().addMSecs(msec);

//    while( QTime::currentTime() < _Timer )

//    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
//}

void ParamMgr::onSetPlasmaVlm(qint16 newValue)
{
    if ( m_bSendChange && newValue != m_pRecRT->plsmVlm)
    {
        if ( m_bUnitML )
        {
           // m_pRecRT->plsmVlm = ( qint16 )(newValue/ML_G_RATE + 0.5);
            m_pRecRT->plsmVlm = ( qint16 )(newValue);
        }
        else
        {
            m_pRecRT->plsmVlm = newValue;
        }

        emit volumeOfPlasmaChanged(m_pRecRT->plsmVlm);

      //      qDebug("a=%d",newValue);


    }
    else if( CSS_ready_draw == StatusMgr::getInstance().getControlSystemStatus() )
    {
        m_pRecRT->plsmVlm = newValue;
        emit volumeOfPlasmaChanged(m_pRecRT->plsmVlm);

      //      qDebug("b=%d",newValue);




    }
}
void ParamMgr::onSetACDVlm(qint16 newValue)
{
    if (m_bSendChange &&
            newValue != m_pRecRT->acdVlm)
    {
        m_pRecRT->acdVlm = newValue;
        emit volumeOfACDChanged(newValue);
    }
}

void ParamMgr::onSetNaClVlm(qint16 newValue)
{
    if (m_bSendChange &&
            newValue != m_pRecRT->naclVlm)
    {
        m_pRecRT->naclVlm = newValue;
        emit volumeOfNaClChanged(newValue);
    }
}
//“保养液量更新”信号
void ParamMgr::onSetPresvVlm(qint16 newValue)
{
    if (m_bSendChange &&
            newValue != m_pRecRT->prsvVlm)
    {
        m_pRecRT->naclVlm = newValue;
        emit volumeOfPresvChanged(newValue);
    }
}

void ParamMgr::onSetVersion(qint16 newValue)
{
    if (m_bSendChange &&
            newValue != m_pRecRT->version)
    {
        m_pRecRT->version = newValue;
        emit versionChanged(newValue);
      //  qDebug("%d",newValue);
    }
}

void ParamMgr::onSetcollecttime(qint16 newValue)
{
    if(m_bSendChange &&
            newValue != m_pRecRT->collecttime)
    {
        m_pRecRT->collecttime = newValue;
        emit collecttimeChanged(newValue);
    }
}

//“全血采集量更新”信号
void ParamMgr::onSetBloodVlm(qint16 newValue)
{
    if (m_bSendChange &&
            newValue != m_pRecRT->bldVlm)
    {
        m_pRecRT->naclVlm = newValue;
        emit volumeOfBloodChanged(newValue);
    }
}
//“全血采集pgbar量更新”信号
void ParamMgr::onSetBloodPgbarVlm(qint16 newValue)
{
    if (m_bSendChange &&
            newValue != m_pRecRT->bldVlm)
    {
        m_pRecRT->naclVlm = newValue;
        emit volumeOfBloodPgbarChanged(newValue);
    }
}

//“悬红量更新”信号
void ParamMgr::onSetRBCVlm(qint16 newValue)
{
    if (m_bSendChange &&
            newValue != m_pRecRT->SRBCVlm)
    {
        m_pRecRT->naclVlm = newValue;
        emit volumeOfSRBCChanged(newValue);
    }
}
void ParamMgr::onSetRBCPgbarVlm(qint16 newValue)
{
    if (m_bSendChange &&
            newValue != m_pRecRT->SRBCVlm)
    {
        m_pRecRT->naclVlm = newValue;
        emit volumeOfSRBCPgbarChanged(newValue);
    }
}

void ParamMgr::onSetBPSpeed(qint16 newValue)
{
    if (m_bSendChange &&
            newValue != m_pRecRT->pumpSpeed)
    {
        m_pRecRT->pumpSpeed = newValue;
        emit flowRateOfBloodPumpChanged(newValue);
    }
}

void ParamMgr::onSetAPSpeed(qint16 newValue)
{
    if (m_bSendChange &&
            newValue != m_pRecRT->ACDpumpSpeed)
    {
        m_pRecRT->ACDpumpSpeed = newValue;
        emit flowRateOfACDPumpChanged(newValue);
    }
}

void ParamMgr::onSetPresvPSpeed(qint16 newValue)
{
    if (m_bSendChange &&
            newValue != m_pRecRT->presvPumpSpeed)
    {
        m_pRecRT->presvPumpSpeed = newValue;
        emit flowRateOfPresvPumpChanged(newValue);
    }
}

void ParamMgr::onSetCFSpeed(qint16 newValue)
{
    if (m_bSendChange &&
            newValue != m_pRecRT->centrifugeSpeed)
    {
        m_pRecRT->centrifugeSpeed = newValue;
        emit speedOfCentrifugeChanged(newValue);
    }
}

void ParamMgr::onSetLineDetector(qint16 newValue)
{
    if (m_bSendChange &&
            newValue != m_pRecRT->lineDetector)
    {
        m_pRecRT->lineDetector = newValue;
        emit lineDetectorChanged(newValue);
    }
}

void ParamMgr::onSetBlood(qint16 newValue)
{
    if (m_bSendChange &&
            newValue != m_pRecRT->blood)
    {
        m_pRecRT->blood = newValue;
        emit bloodChanged(newValue);
    }
}

void ParamMgr::onSetDraw_speed(qint16 newValue)
{
    if (m_bSendChange &&
            newValue != m_pRecRT->draw_speed)
    {
        m_pRecRT->draw_speed = newValue;
        emit drawspeedChanged(newValue);
    }
}

void ParamMgr::onSetCollect_speed(qint16 newValue)
{
    if (m_bSendChange &&
            newValue != m_pRecRT->collect_speed)
    {
        m_pRecRT->collect_speed = newValue;
        emit collectspeedChanged(newValue);
    }
}

void ParamMgr::onSetLinecoff(qint16 newValue)
{
    if (m_bSendChange &&
            newValue != m_pRecRT->linecoff)
    {
        m_pRecRT->linecoff = newValue;
        emit linecoffChanged(newValue);
    }
}

void ParamMgr::onSetBpap_rate(qint16 newValue)
{
    if (m_bSendChange &&
            newValue != m_pRecRT->bpap_rate)
    {
        m_pRecRT->bpap_rate = newValue;
        emit bpaprateChanged(newValue);
    }
}

void ParamMgr::onSetPrs_speed(qint16 newValue)
{
    if (m_bSendChange &&
            newValue != m_pRecRT->prs_speed)
    {
        m_pRecRT->prs_speed = newValue;
        emit prsspeedChanged(newValue);
    }
}

void ParamMgr::onSetBPreal(qint16 newValue)
{
    if (m_bSendChange &&
            newValue != m_pRecRT->BPreal)
    {
        m_pRecRT->BPreal = newValue;
        emit bPrealChanged(newValue);
    }
}

void ParamMgr::onSetAPreal(qint16 newValue)
{
    if (m_bSendChange &&
            newValue != m_pRecRT->APreal)
    {
        m_pRecRT->APreal = newValue;
        emit aPrealChanged(newValue);
    }
}

void ParamMgr::onSetNPreal(qint16 newValue)
{
    if (m_bSendChange &&
            newValue != m_pRecRT->NPreal)
    {
        m_pRecRT->NPreal = newValue;
        emit nPrealChanged(newValue);
    }
}



void ParamMgr::onSetBoolParam(qint32 newValue)
{
    if (!m_bSendChange)
        return;

    BoolParam_t tmp;
    tmp.w = newValue;

    if (tmp.Bld_V != m_BoolVar.Bld_V){
        emit valveOfBloodChanged(tmp.Bld_V);
    }

    if (tmp.Plsm_V != m_BoolVar.Plsm_V){
        emit valveOfPlasmaChanged(tmp.Plsm_V);
    }

    if (tmp.NaCl_V != m_BoolVar.NaCl_V){
        emit valveOfNaClChanged(tmp.NaCl_V);
    }

//    if (tmp.ACD_V != m_BoolVar.ACD_V){
//        emit valveOfACDChanged(tmp.ACD_V);
//    }
    if (tmp.Presv_V != m_BoolVar.Presv_V){
        emit valveOfPresvChanged(tmp.Presv_V);
    }
    if (tmp.RBC_V != m_BoolVar.RBC_V){
        emit valveOfRBCChanged(tmp.RBC_V);
    }
    if (tmp.Waste_V != m_BoolVar.Waste_V){
        emit valveOfWasteChanged(tmp.Waste_V);
    }

    if (tmp.Bld_airD != m_BoolVar.Bld_airD){
        emit airDetectorOfBloodChanged(tmp.Bld_airD);
    }

    if (tmp.ACD_airD != m_BoolVar.ACD_airD){
        emit airDetectorOfAcdChanged(tmp.ACD_airD);
    }

    if (tmp.Presv_airD != m_BoolVar.Presv_airD){
        emit airDetectorOfPresvChanged(tmp.Presv_airD);
    }

    if (tmp.DPM != m_BoolVar.DPM){
        emit dpmChanged(tmp.DPM);
    }

    if (tmp.Leak_D != m_BoolVar.Leak_D){
        emit leakChanged(tmp.Leak_D);
    }

    if (tmp.Cover != m_BoolVar.Cover){
        emit coverChanged(tmp.Cover);
    }

    if (tmp.Line_D != m_BoolVar.Line_D){
        emit lineSensorChanged(tmp.Line_D);
    }

    if (tmp.PumpOn != m_BoolVar.PumpOn){
        emit pumpStatusChanged(tmp.PumpOn);
    }

    m_BoolVar.w = newValue;
}

void ParamMgr::onComData(QString str)
{
    emit COMdata(str);
}

void ParamMgr::timerEvent(QTimerEvent */*event*/)
{
    if (!m_bSendChange)
        return;

    if (m_pRecRT->pumpSpeed > 0 || m_pRecRT->pumpSpeed < 0)
    {
        if (m_pRecRT->pumpStopTime != 0)
        {
            m_pRecRT->pumpStopTime = 0;
            emit timeOfPumpStopChanged(m_pRecRT->pumpStopTime);
        }
    }
    else
    {
        m_pRecRT->pumpStopTime++;
        emit timeOfPumpStopChanged(m_pRecRT->pumpStopTime);
    }

    if ( m_bCountTime )
    {
        m_pRecRT->timeLen++;
        emit timeLenChanged(m_pRecRT->timeLen);

        //  每5s记录一次采集时间，掉电重启之后要用     llc 20131205
        if ( 1 == m_pRecRT->timeLen%5  )
            DataMgr::getInst().setUsrCfgInt( CFG_timeLen,  (qint32)m_pRecRT->timeLen );
    }
}

void ParamMgr::onColctBegin()
{
    m_bSendChange = true;
}

void ParamMgr::saveBeginTime()
{
    m_pRecRst->bgtime = QDateTime::currentDateTime();
    DataMgr::getInst().setUsrCfgInt( CFG_beginTime,  (qint32)m_pRecRst->bgtime.toTime_t() );
}

void ParamMgr::saveIDs()
{
    DataMgr::getInst().setUsrCfgStr(CFG_donorIdSet, m_pRecRst->donorId); //供浆员ID录入设置值
    DataMgr::getInst().setUsrCfgStr(CFG_dspslIdSet, m_pRecRst->dposlId); //耗材ID录入设置值
    DataMgr::getInst().setUsrCfgStr(CFG_acdIdSet, m_pRecRst->acId);        //抗凝剂ID录入设置值
    DataMgr::getInst().setUsrCfgStr(CFG_salineIdSet, m_pRecRst->naclId);  //盐水ID录入设置值
    DataMgr::getInst().setUsrCfgStr(CFG_oprtrIdset, m_pRecRst->oprtrId);   //操作者ID录入设置值
}

void ParamMgr::onColctEnd()
{
    m_bSendChange = false;

    // 更新耗材编号和数量
    m_pRecRst->dposlId = NetDataMgr::getInst().getCurDisposable().id;
    m_pRecRst->acId    = NetDataMgr::getInst().getCurADC().id;
    m_pRecRst->naclId  = NetDataMgr::getInst().getCurNacl().id;

    // 护士编号和姓名
    m_pRecRst->oprtrId = NetDataMgr::getInst().getNurse().id;
    m_pRecRst->oprtrName = NetDataMgr::getInst().getNurse().name;

    // 浆员id
    m_pRecRst->donorId = NetDataMgr::getInst().getDonor().id;
    m_rslt.machineId = DataMgr::getInst().getUsrCfgStr( CFG_devID );

    m_rslt.bgtime  = m_pRecRst->bgtime;
    m_rslt.donorId = m_pRecRst->donorId;
    m_rslt.dposlId = m_pRecRst->dposlId;
    m_rslt.acId    = m_pRecRst->acId;
    m_rslt.naclId  = m_pRecRst->naclId;
    m_rslt.oprtrId = m_pRecRst->oprtrId;
    m_rslt.oprtrName = m_pRecRst->oprtrName;
    m_rslt.plsmVlm = m_pRecRT->plsmVlm;
    m_rslt.acdVlm  = m_pRecRT->acdVlm;
    m_rslt.enrivlm = m_pRecRT->SRBCVol;
    m_rslt.collectionvlm  = m_pRecRT->bldVlm;

//    if ( m_bQuitPowerOff )
//    {
//        m_rslt.edtime.setTime_t( m_pRecRst->bgtime + m_pRecRT->timeLen );
//        m_bQuitPowerOff = false;
//    }
//    else
//    {
//        m_rslt.edtime    = QDateTime::currentDateTime();
//    }

//    m_rslt.timeLen_e = m_pRecRT->timeLen;
//    m_rslt.circleNum = m_nCycleNumber;

    m_pRecRT->pumpStopTime = -1;
    m_pRecRT->prsDPM = -1;
    m_pRecRT->plsmVlm = -1;
    m_pRecRT->acdVlm = -1;
    m_pRecRT->naclVlm = -1;
    m_pRecRT->pumpSpeed = -1;
    m_pRecRT->ACDpumpSpeed = -1;
    m_pRecRT->centrifugeSpeed = -1;
    m_pRecRT->lineDetector = -1;
    m_pRecRT->timeLen = -1;

    m_pRecRst->dposlId = "";
    m_pRecRst->acId    = "";
    m_pRecRst->naclId  = "";
    m_pRecRst->donorId = "";
}

bool ParamMgr::getRst(RecRst &rst) const
{
    rst = m_rslt;

//    rst.timeLen    = rst.timeLen/60; // 以分钟为单位保存到外部
//    rst.oprtrName = NetDataMgr::getInst().getNurse().name; // 每次重新获取护士名
//    rst.oprtrId      = NetDataMgr::getInst().getNurse().id; // 每次重新获取护士名
//    m_pRecRst->oprtrId       = rst.oprtrId;
    return true;
}

void ParamMgr::setParamSettingToLatest()
{
//    if (m_paramFile.open(QIODevice::ReadOnly))
//    {
//        qint64 rLen = sizeof(ParamSetting) + sizeof(bool) + sizeof(bool);
//        char* pBuf = new char[rLen];
//        bool bSuccess = (rLen == m_paramFile.read(pBuf, rLen));
//        m_paramFile.close();

//        if (bSuccess)
//        {
//            ParamSetting params = *(ParamSetting*)pBuf;
//            bool bCuff = *(bool*)(pBuf + sizeof(ParamSetting));
//            bool bPump = *(bool*)(pBuf + sizeof(ParamSetting) + sizeof(bool));
//            setParamSetting(params);
//            setTargetSwitchOfCuff(bCuff);
//            setTargetSwitchOfPump(bPump);
//        }
//        else
//        {
//            qDebug() << "read latest param :paramsetting failed";
//            setParamSettingsToDefault();
//            setTargetSwitchOfCuff(false);
//            setTargetSwitchOfPump(true);
//        }
//        delete [] pBuf;
//    }
//    else
//    {
//        qDebug()<< "read latest param open failed";
//    }
}

bool ParamMgr::setParamSettingsToDefault()
{
//    ParamSetting params;
//    params.acFactor = DataMgr::getInst().getUsrCfgInt(CFG_ACFactor);
//    params.cuffPrs  = DataMgr::getInst().getUsrCfgInt(CFG_cuffPrs);
//    params.drawRate = DataMgr::getInst().getUsrCfgInt(CFG_drawRate);
//    params.returnRate = DataMgr::getInst().getUsrCfgInt(CFG_returnRate);
//    params.lineDSens = DataMgr::getInst().getUsrCfgInt(CFG_lineDSens);
//    params.naclCycVol = DataMgr::getInst().getUsrCfgInt(CFG_NaClCycVol);
//    params.naclVol  = DataMgr::getInst().getUsrCfgInt(CFG_NaClVol);
//    params.plsmCycVol = DataMgr::getInst().getUsrCfgInt(CFG_plsmCycVol);
//    params.plsmVol = DataMgr::getInst().getUsrCfgInt(CFG_plsmVol);
//    setTargetSwitchOfCuff(false);
//    setTargetSwitchOfPump(true);
//    return setParamSetting(params);
}

bool ParamMgr::setParamSetting(const ParamSetting& params)
{
    ParamSetting tmparam;

    tmparam = params;

    bool ret = SerialApp::getInstance().send(CMD_set_params,(const CmdParam*)(&tmparam), sizeof(tmparam)/sizeof(CmdParam));
    if (ret)
    {
        if (m_params.cSpeed != params.cSpeed)
        {
            m_params.cSpeed = params.cSpeed;
            emit targetRateOfDrawChanged(params.cSpeed);
        }
        if (m_params.cRBCSpeed != params.cRBCSpeed)
        {
            m_params.cRBCSpeed = params.cRBCSpeed;
            emit targetRateOfCollectChanged(params.cRBCSpeed);
        }
        if (m_params.bloodVlm != params.bloodVlm)
        {
            m_params.bloodVlm = params.bloodVlm;
            emit targetBldVlmChanged(params.bloodVlm);
        }
        m_params = params;
        //emit paramSettingChanged(m_params);

        saveLatestParamSetting(m_params);
    }

    return ret;
}

bool ParamMgr::setTargetDrawRate(qint16 value)
{
    bool ret = true;
    if (value != m_params.cSpeed)
    {
        CmdParam param = value;
        ret = SerialApp::getInstance().send(CMD_set_drawRate, &param, 1);
        if(ret)
        {
            m_params.cSpeed = value;
            emit targetRateOfDrawChanged(value);
            saveLatestParamSetting(m_params);
        }
    }

    return ret;
}

bool ParamMgr::setTargetCollectRate(qint16 value)
{
    bool ret = true;
    if (value != m_params.cRBCSpeed)
    {
        CmdParam param = value;
        ret = SerialApp::getInstance().send(CMD_set_collectRBCRate, &param, 1);
        if(ret)
        {
            m_params.cRBCSpeed = value;
            emit targetRateOfCollectChanged(value);
            saveLatestParamSetting(m_params);
        }
    }

    return ret;
}

bool ParamMgr::setTargetSwitchOfPump(bool value)
{
    bool ret = true;
    if (value != m_bPumpOn)
    {
        CmdParam param_status = value;

        ret =  SerialApp::getInstance().send(CMD_set_pumpStatus, &param_status, 1);
        if (ret)
        {
            m_bPumpOn = value;
            emit targetSwitchOfPumpChanged(value);
            saveLatestPumpSetting(m_bPumpOn);
        }
    }

    return ret;
}

void ParamMgr::saveLatestParamSetting(const ParamSetting &param)
{
    if (m_paramFile.open(QIODevice::ReadWrite))
    {
        if (m_paramFile.seek(0))
        {
            qint64 wLen = sizeof(ParamSetting);
            if (wLen != m_paramFile.write((char*)&param, wLen))
            {
                qDebug() << "write latest param :paramsetting failed";
            }
            else
            {
                m_paramFile.flush();
            }
        }
        m_paramFile.close();
    }
}

void ParamMgr::saveLatestPumpSetting(bool bPumpStatus)
{
    if (m_paramFile.open(QIODevice::ReadWrite))
    {
        if (m_paramFile.seek(sizeof(ParamSetting) + sizeof(bool)))
        {
            qint64 wLen = sizeof(bool);
            if (wLen != m_paramFile.write((char*)&bPumpStatus, wLen))
            {
                qDebug() << "write latest param :pumpstatus failed";
            }
            else
            {
                m_paramFile.flush();
            }
        }
        m_paramFile.close();
    }
}

void ParamMgr::endDrawing()
{
}

bool ParamMgr::sendStepDrawParam()
{
    return true;
}
