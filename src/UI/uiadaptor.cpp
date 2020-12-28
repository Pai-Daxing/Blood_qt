#include "../ParamMgr/parammgr.h"
#include "../StatusMgr/statusmgr.h"
#include "../SerialApp/serialapp.h"
#include "../AlarmMgr/alarmstr.h"
#include "../Dev/button/btthread.h"
#include "../Dev/NetOnline/netonline.h"
#include "../Dev/Time/time.h"
#include "uiadaptor.h"
#include </home/slrom/qtworks/led/wiringPi/wiringPi.h>


UiAdaptor::UiAdaptor(QObject *parent) : QObject(parent)
{
    m_pExecProc = new QProcess();


    //调试界面的更新信号
    connect( TimeThread::getInst(), &TimeThread::timerUpdate, this, &UiAdaptor::timerUpdate);
    connect( ParamMgr::getInstance(), &ParamMgr::valveOfBloodChanged, this, &UiAdaptor::valveOfBloodChanged);          //“血液阀开关更新”信号 1开 0关
    connect( ParamMgr::getInstance(), &ParamMgr::valveOfPlasmaChanged, this, &UiAdaptor::valveOfPlasmaChanged);        //“血浆阀开关更新”信号 1开 0关
    connect( ParamMgr::getInstance(), &ParamMgr::valveOfNaClChanged, this, &UiAdaptor::valveOfNaClChanged);            //“盐水阀开关更新”信号 1开 0关
    connect( ParamMgr::getInstance(), &ParamMgr::valveOfACDChanged, this, &UiAdaptor::valveOfACDChanged);              //“抗凝阀开关更新”信号 1开 0关
    connect( ParamMgr::getInstance(), &ParamMgr::valveOfPresvChanged, this, &UiAdaptor::valveOfPresvChanged);            //“保养液阀开关更新”信号 1开 0关
    connect( ParamMgr::getInstance(), &ParamMgr::valveOfRBCChanged, this, &UiAdaptor::valveOfRBCChanged);              //“红细胞阀开关更新”信号 1开 0关
    connect( ParamMgr::getInstance(), &ParamMgr::valveOfWasteChanged, this, &UiAdaptor::valveOfWasteChanged);            //“废液阀开关更新”信号 1开 0关
    connect( ParamMgr::getInstance(), &ParamMgr::airDetectorOfBloodChanged, this, &UiAdaptor::airDetectorOfBloodChanged);  //“血液空探更新”信号 1液体 0空气
    connect( ParamMgr::getInstance(), &ParamMgr::airDetectorOfAcdChanged, this, &UiAdaptor::airDetectorOfAcdChanged);      //“抗凝剂空探更新”信号 1液体 0空气
    connect( ParamMgr::getInstance(), &ParamMgr::airDetectorOfPresvChanged, this, &UiAdaptor::airDetectorOfPresvChanged);      //“抗凝剂空探更新”信号 1液体 0空气
    connect( ParamMgr::getInstance(), &ParamMgr::dpmChanged, this, &UiAdaptor::dpmChanged);                     //“压力监测器状态更新”信号 1已安装 0未安装
    connect( ParamMgr::getInstance(), &ParamMgr::leakChanged, this, &UiAdaptor::leakChanged);                   //“漏夜监测器状态更新”信号 1已漏液 0未漏液
    connect( ParamMgr::getInstance(), &ParamMgr::coverChanged, this, &UiAdaptor::coverChanged);                 //“离心机盖状态更新”信号 1已关盖 0未关盖
    connect( ParamMgr::getInstance(), &ParamMgr::lineSensorChanged, this, &UiAdaptor::lineSensorChanged);       //“管路探测器更新”信号 1发现红细胞 0未发现红细胞

    connect( ParamMgr::getInstance(), &ParamMgr::versionChanged, this, &UiAdaptor::versionChanged);
    connect( ParamMgr::getInstance(), &ParamMgr::collecttimeChanged, this, &UiAdaptor::collecttimeChanged);

    connect( ParamMgr::getInstance(), &ParamMgr::pressureOfDpmChanged, this, &UiAdaptor::pressureOfDpmChanged);
    connect( ParamMgr::getInstance(), &ParamMgr::negapressureOfDpmChanged, this, &UiAdaptor::negapressureOfDpmChanged);//“压力监测值更新”信号
    connect( ParamMgr::getInstance(), &ParamMgr::volumeOfPlasmaChanged, this, &UiAdaptor::volumeOfPlasmaChanged);        //“血浆量更新”信号
    connect( ParamMgr::getInstance(), &ParamMgr::volumeOfACDChanged, this, &UiAdaptor::volumeOfACDChanged);        //“血浆量更新”信号
    connect( ParamMgr::getInstance(), &ParamMgr::flowRateOfBloodPumpChanged, this, &UiAdaptor::flowRateOfBloodPumpChanged);   //“血泵流速更新”信号
    connect( ParamMgr::getInstance(), &ParamMgr::flowRateOfACDPumpChanged, this, &UiAdaptor::flowRateOfACDPumpChanged);     //“抗凝剂泵流速更新”信号
    connect( ParamMgr::getInstance(), &ParamMgr::flowRateOfPresvPumpChanged, this, &UiAdaptor::flowRateOfPresvPumpChanged);   //“保养液泵流速更新”信号
    connect( ParamMgr::getInstance(), &ParamMgr::speedOfCentrifugeChanged, this, &UiAdaptor::speedOfCentrifugeChanged);     //“离心机转速更新”信号
    connect( ParamMgr::getInstance(), &ParamMgr::lineDetectorChanged, this, &UiAdaptor::lineDetectorChanged);          //“管路探测器更新”信号

    connect( ParamMgr::getInstance(), &ParamMgr::bloodChanged, this, &UiAdaptor::bloodChanged);
    connect( ParamMgr::getInstance(), &ParamMgr::drawspeedChanged, this, &UiAdaptor::drawspeedChanged);
    connect( ParamMgr::getInstance(), &ParamMgr::collectspeedChanged, this, &UiAdaptor::collectspeedChanged);
    connect( ParamMgr::getInstance(), &ParamMgr::linecoffChanged, this, &UiAdaptor::linecoffChanged);
    connect( ParamMgr::getInstance(), &ParamMgr::bpaprateChanged, this, &UiAdaptor::bpaprateChanged);
    connect( ParamMgr::getInstance(), &ParamMgr::prsspeedChanged, this, &UiAdaptor::prsspeedChanged);

    connect( ParamMgr::getInstance(), &ParamMgr::bPrealChanged, this, &UiAdaptor::bPrealChanged);
    connect( ParamMgr::getInstance(), &ParamMgr::aPrealChanged, this, &UiAdaptor::aPrealChanged);
    connect( ParamMgr::getInstance(), &ParamMgr::nPrealChanged, this, &UiAdaptor::nPrealChanged);


    connect( ParamMgr::getInstance(), &ParamMgr::targetRateOfDrawChanged, this, &UiAdaptor::targetRateOfDrawChanged);
    connect( ParamMgr::getInstance(), &ParamMgr::targetRateOfCollectChanged, this, &UiAdaptor::targetRateOfCollectChanged);
//    connect( ParamMgr::getInstance(), &ParamMgr::targetRateOfDrawChanged, this, &UiAdaptor::targetRateOfDrawChanged);


    connect( ParamMgr::getInstance(), &ParamMgr::volumeOfNaClChanged,  this, &UiAdaptor::volumeOfNaClChanged);          //“盐水量更新”信号
    connect( ParamMgr::getInstance(), &ParamMgr::volumeOfBloodChanged, this, &UiAdaptor::volumeOfBloodChanged);         //“全血采集量量更新”信号
    connect( ParamMgr::getInstance(), &ParamMgr::volumeOfBloodPgbarChanged, this, &UiAdaptor::volumeOfBloodPgbarChanged);
    connect( ParamMgr::getInstance(), &ParamMgr::volumeOfPresvChanged, this, &UiAdaptor::volumeOfPresvChanged);         //“保养液量更新”信号
    connect( ParamMgr::getInstance(), &ParamMgr::volumeOfSRBCChanged,  this, &UiAdaptor::volumeOfSRBCChanged);          //“悬红量更新”信号
    connect( ParamMgr::getInstance(), &ParamMgr::volumeOfSRBCPgbarChanged,  this, &UiAdaptor::volumeOfSRBCPgbarChanged);          //“悬红量pgbar更新”信号
   // connect( ParamMgr::getInstance(), &ParamMgr::volumeOfSRBCVolChanged,  this, &UiAdaptor::volumeOfSRBCVolChanged);
    connect( ParamMgr::getInstance(), &ParamMgr:: timeLenChanged,      this, &UiAdaptor::timeLenChanged);  //采集时间

    connect( BtThread::getInst(), &BtThread::stopButtonPressed,   this,&UiAdaptor::stopButtonPressed);

    connect( NetOnline::getInst(), &NetOnline::netconnect,   this,&UiAdaptor::netconnect);
    connect( NetOnline::getInst(), &NetOnline::netconnectfaild,   this,&UiAdaptor::netconnectfaild);



    connect(&AlarmMgr::getInstance(), &AlarmMgr::triggerAlarm, this, &UiAdaptor::onAlarmStart);
    connect(&AlarmMgr::getInstance(), &AlarmMgr::cancelAlarm, this, &UiAdaptor::onCancelAlarm);

    connect( &StatusMgr::getInstance(), &StatusMgr::controlSystemStatusChanged, this, &UiAdaptor::onCtrlSysStatusChanged);
    connect( this, &UiAdaptor::UICmd, &SerialApp::getInstance(), &SerialApp::onUICmd);    
}

void UiAdaptor::onUILoadCompleted()
{
    qDebug()<<"UI loaded!!";

    //    SerialApp::getInstance().send(CMD_start_selftest);
    emit UICmd(CMD_start_selftest, 0, 0);
}

void UiAdaptor::bootSelfTest(void)
{
    emit UICmd(CMD_boot_selftest, 0, 0);
}

void UiAdaptor::bootChkFailed(void)
{
    emit UICmd(CMD_boot_chkfailed, 0, 0);
}

void UiAdaptor::bootQuit(void)
{
    emit UICmd(CMD_boot_quit, 0, 0);

}

void UiAdaptor::startSelfTest(void)
{
  //  emit UICmd(CMD_start_selftest, 0, 0);
    emit UICmd(CMD_boot_selftest, 0, 0);
}

void UiAdaptor::fillfailed(void)
{
    emit UICmd(CMD_Fill_failed, 0, 0);
}

void UiAdaptor::startDrawProc()
{
    //    SerialApp::getInstance().send(CMD_start_install);
    emit UICmd(CMD_start_install, 0, 0);
}

void UiAdaptor::startDrawing(void)
{
    emit UICmd(CMD_start_collect, 0, 0);
}

void UiAdaptor::confirmLine(void)
{
    emit UICmd(CMD_confirm_install, 0, 0);
}
//启动调试
void UiAdaptor::starDebug(void)
{
    emit UICmd(CMD_start_debug, 0, 0);
    qDebug("startDebug");
}

void UiAdaptor::exitDebug(void)
{
    emit UICmd(CMD_quit_debug, 0, 0);
    qDebug("exitDebug");
}

//// 调试状态时的设置命令
//CMD_DB_set_bldPumpRate,    //设置血泵速度
//CMD_DB_set_acdFactor,      //设置抗凝比
//CMD_DB_set_cfStatus,       //设置离心机启停
//CMD_DB_set_bldPump_Dir,    //设置血泵方向   0：顺时针；1：逆时针

void UiAdaptor::confirmACDRdy(void)
{
    emit UICmd(CMD_prime, 0, 0);
}

void UiAdaptor::dbSetBool(int index, short val)
{
    switch (index) {
    case 0:
        emit UICmd(CMD_DB_set_cfStatus, (const short *)&val, 1);
        break;
    case 1:
        emit UICmd(CMD_DB_set_bldValve, (const short *)&val, 1);
        break;
    case 2:
        emit UICmd(CMD_DB_set_RBCValve, (const short *)&val, 1);
        break;
    case 3:
        emit UICmd(CMD_DB_set_plmValve, (const short *)&val, 1);
        break;
    case 4:
        emit UICmd(CMD_DB_set_WasteValve, (const short *)&val, 1);
        break;
    case 5:
        emit UICmd(CMD_DB_set_PresvValve, (const short *)&val, 1);
        break;
    case 6:
        emit UICmd(CMD_DB_set_naclValve, (const short *)&val, 1);
        break;
    default:
        break;
    }
}

void UiAdaptor::dbSetBldPSpeed(short bldS)  //血泵
{
    emit UICmd(CMD_DB_set_bldPumpRate,  (const short *)&bldS, 1);
}

void UiAdaptor::dbSetAcdPSpeed(short acdS)   //保养液--AC
{
    emit UICmd(CMD_DB_set_acdFactor,    (const short *)&acdS, 1);  // 调整状态的比例认为是直接的速度设置值
}

void UiAdaptor::dbSetPresvPSpeed(short nS)    //抗凝剂泵--N
{
    emit UICmd(CMD_DB_set_PrsvPumpRate, (const short *)&nS, 1);
}
//电子秤部分
void UiAdaptor::scaledOkOne(short num)
{
    emit UICmd(CMD_Scaled_Ok_One,(const short *)&num,1);
}

void UiAdaptor::scaledOkTwo(short num1)
{
    emit UICmd(CMD_Scaled_Ok_Two, (const short *)&num1, 1);
}

void UiAdaptor::bldScaOkThree(short num2)
{
    emit UICmd(CMD_BldSca_Ok_Three, (const short *)&num2, 1);
}

void UiAdaptor::bldScaOkFour(short num3)
{
    emit UICmd(CMD_BldSca_Ok_four, (const short *)&num3, 1);
}

//void UiAdaptor::bldScaOkfive(/*short num4*/)
//{
//    //emit UICmd(CMD_BldSca_Ok_five, (const short *)&num4, 1);
//}

void UiAdaptor::paramOK(short num1,short num2,short num3,short num4,short num5,short num6)
{
        emit UICmd(CMD_Collect_Blood, (const short *)&num1, 1);
        emit UICmd(CMD_Draw_Speed, (const short *)&num2, 1);
        emit UICmd(CMD_Collect_Speed, (const short *)&num3, 1);
        emit UICmd(CMD_Anti, (const short *)&num4, 1);
        emit UICmd(CMD_LineCoeff, (const short *)&num5, 1);
        emit UICmd(CMD_Presvvlm_Speed, (const short *)&num6, 1);
}

//退出采集自检
void UiAdaptor::quitselftest(void)
{
    emit UICmd(CMD_self_quit, 0, 0);
}

void UiAdaptor::colNPadd(void)
{
    emit UICmd(CMD_Col_NPadd, 0, 0);
}

void UiAdaptor::colNPred(void)
{
    emit UICmd(CMD_Col_NPred, 0, 0);
}
void UiAdaptor::colNPsta(void)
{
    emit UICmd(CMD_Col_Npsta, 0, 0);
}

void UiAdaptor::colNPstop(void)
{
    emit UICmd(CMD_Col_Npstop, 0, 0);
}

void UiAdaptor::endCollect(void)
{
    emit UICmd(CMD_end_collect, 0, 0);
}




void UiAdaptor::colNext(void)
{
    emit UICmd(CMD_Col_next, 0, 0);
}



void UiAdaptor::paramsave(int num1,int num2,int num3,int num4,int num5,int num6)
{
    ParamRec par;
    par.cblood = num1;
    par.cbloodsp = num2;
    par.prespeed = num6;
    par.collsp = num3;
    par.anti = num4;
    par.line = num5;

    DataStorage::getInstance().saveParam( par );

}

void UiAdaptor::resultp(int num1,int num2)
{
    RecRst rst;
    rst.prsvVlm = num1;
    rst.acdVlm = num2;

    DataStorage::getInstance().saveUploadedRst( rst );
}



/*******************************************/
/*******************stop按钮*****************/
void UiAdaptor::stoppress(void)
{
    emit UICmd(CMD_stop,0, 0);
}

//报警部分
void UiAdaptor::popupalarmblood(void)
{
    emit UICmd(CMD_ala_collectblood,0,0);
}

void UiAdaptor::popupalarmpreparation(void)
{
    emit UICmd(CMD_ala_preparation,0,0);
}

void UiAdaptor::popupalarmexit(void)
{
    emit UICmd(CMD_ala_exit,0,0);
}
//
//血液阀操作
void UiAdaptor::bldSpeedAdd(void)
{
    emit UICmd(CMD_Col_bldadd,0,0);
}

void UiAdaptor::bldSpeedReduce(void)
{
    emit UICmd(CMD_Col_bldred,0,0);
}

void UiAdaptor::bldSpeedStart(void)
{
    emit UICmd(CMD_Col_bldsta,0,0);
}

void UiAdaptor::bldSpeedStop(void)
{
    emit UICmd(CMD_Col_bldstop,0,0);
}
//

void UiAdaptor::dbSetBldPDir(short val)
{
    emit UICmd(CMD_DB_set_bldPump_Dir, (const short *)&val, 1);
}

void UiAdaptor::scaledstart(void)
{
    emit UICmd(CMD_Sca_start,0,0);
    qDebug("scaledstart");
}

void UiAdaptor::scaledexit(void)
{
    emit UICmd(CMD_Sca_exit,0,0);
    qDebug("scaledexit");
}


void UiAdaptor::onCtrlSysStatusChanged(qint16 newStatus)
{
    QString errStr = "";
    switch ((ControlSystemStatus)newStatus)
    {
    case CSS_standby:
    //    if ( CSS_unknown != StatusMgr::getInstance().getPreControlSystemStatus()){
            emit setCSS2StandBy();
        wiringPiSetup();
        pinMode(3,OUTPUT);
        pinMode(7,OUTPUT);

        digitalWrite(3,LOW);
        digitalWrite(7,HIGH);
            qDebug("lllllllll");
     //   }
        break;
    case CSS_open_waiting:
        emit setCSS2WaitCoverOpen();
        emit showSfChkMsg(QString("请打开离心机盖"));
        break;
    case CSS_close_waiting:
        emit setCSS2WaitCoverClose();
        emit showSfChkMsg(QString("请关闭离心机盖"));
        break;
    case CSS_AirDs_checking:/*空探正在检查*/
        emit showSelftTestAirDs();
        break;
    case CSS_Vlvs_checking:
        emit showSelftTestVlvs();
        break;
    case CSS_Pumps_checking:
        emit showSelftTestPumps();
        break;
    case CSS_line_checking:
        emit showSelftTestline();
        break;
    case CSS_CF_checking:
        emit showSelftTestCF();
        break;
    case CSS_DPM_checking:
        emit showSelftTestDPM();
        break;

    case CSS_Scales_checking:
        emit showSelftTestScales();
        break;
    case CSS_leak_checking:
        emit showSelftTestleak();
        break;
    case CSS_selftest_failed:
        errStr= StatusMgr::getInstance().getErrStr();
        emit setCSS2SelfTestFailed(errStr);
        //TODO   显示失败项

        break;
    case CSS_selftest_over:

        emit setCSS2Succeed();
        break;

//            case CSS_collect_begin:/*开始启动*/
//                emit setCSS2Safe();
//                break;
    case CSS_Sf_AirDs_checking:/*空探正在检查*/
        emit showSfChkMsg(QString("空探自检"));
        emit setCSS2SafeChk();
        break;
    case CSS_Sf_Vlvs_checking:
        emit showSfChkMsg(QString("阀门自检"));
        emit setCSS2SafeChk();
        break;
    case CSS_Sf_Chk_failed:
        errStr = StatusMgr::getInstance().getErrStr();
        emit setCSS2SafeChkFailed(errStr);
        break;
    case CSS_cup_waiting:                  //等待离心杯安装
        emit setCSS2WaitCup();
        emit showSfChkMsg(QString("请安装离心杯"));
        break;
    case CSS_line_ready:                   //等待管路安装确认
        emit setCSS2WaitLine();
        emit showSfChkMsg(QString("确认耗材已安装成功"));
        break;
    case CSS_acd_waiting:                  //等待抗凝剂穿刺
        emit setCSS2WaitACD();
        emit showSfChkMsg(QString("接入样品袋，并确认"));
        break;
    case CSS_filling:                   //采集准备
        emit showSfChkMsg(QString("正在预充"));
        emit setCSS2Prime();
        break;
    case CSS_filling_failed:               //充液失败
        emit cssFillFailed();
        break;
//    case CSS_install_finished:             //安装完成
//        break;
    case CSS_ready_draw:                   //采集准备
        emit showSfChkMsg(QString("预充完成，请点击按钮开始采集"));
        emit setCSS2ReadyDraw();
        break;
    case CSS_drawing:                     //正在采血
        emit setCSS2Draw();
        break;
    case CSS_washing:                     //正在洗涤
        emit setCSS2Washing();
        break;
    case CSS_collect:                     //正在制备
        emit setCSS2Collect();
        break;
    case CSS_collect_paused:              //采集暂停
        emit setCSS2Halt();
        break;
    case CSS_collect_over:                //采集结束
        emit setCSS2CollectEnd();
        wiringPiSetup();
        pinMode(3,OUTPUT);
        pinMode(7,OUTPUT);
        pinMode(0,OUTPUT);

        digitalWrite(7,LOW);
        digitalWrite(0,LOW);
        digitalWrite(3,HIGH);
        break;
    case CSS_drawing_power:
        emit setCSSdrawpower();
        break;
    case CSS_collect_power:
        emit setCSScollectpower();
        break;
    case CSS_continueOrover:
        emit setCSScontinueOrover();
        break;


    default:
        break;
    }
}

QVariantList UiAdaptor::getParamSet()
{
    QVariantList rt;
    rt <<(300);
    rt <<(100);
    rt <<(150);

    return rt;
}

bool UiAdaptor::saveParam(QVariantList params)
{
    if (params.count() < 3)
        return false;
    ParamSetting set;
    set.bloodVlm  = params[0].toInt();
    set.cSpeed    = params[1].toInt();
    set.cRBCSpeed = params[2].toInt();

    return ParamMgr::getInstance()->setParamSetting(set);
}

void UiAdaptor::onAlarmStart(AlarmInfo alarm)
{
    QString str = AlarmString::getInstance().getStr(alarm.type);
    QString details = AlarmString::getInstance().getDetail(alarm.type);
    emit raiseAlarm(alarm.latch, str ,details);
}

void UiAdaptor::onCancelAlarm(AlarmInfo alarm)
{
    Q_UNUSED(alarm);

    emit cancelAlarm();
}

void UiAdaptor::saveConsequence(QVariantList consequence)
{
//    if(consequence.count() < 12)
//        return false;
    RecRst rst;
    rst.bgtime  = QDateTime::currentDateTime();
    rst.edtime_m= QDateTime::currentDateTime();
    rst.edtime_e= QDateTime::currentDateTime();
    rst.donorId = "123";//consequence[0].toString();
    rst.machineId = 1;
    rst.oprtrId = "123";//consequence[4].toString();
    rst.oprtrName = 1;
    rst.collectionvlm  = consequence[0].toString();
    rst.enrivlm = consequence[1].toString();
    rst.timelen  = consequence[2].toInt();
//    rst.naclVlm   = 1;
//    rst.SRBCVlm = consequence[9].toInt();
//    rst.prsvVlm = consequence[5].toInt();
//    rst.timeLen_m = 1;
//    rst.timeLen_e = consequence[6].toInt();
//    rst.dposlId = consequence[1].toString();
//    rst.naclId    = 1;
//    rst.acId    = consequence[2].toString();
//    rst.prsvId  = consequence[3].toString();
//    rst.status  = consequence[11].toString();

    DataStorage::getInstance().saveUploadedRst(rst);

}

void UiAdaptor::execCmd(QString cmd)
{
#ifndef Q_WS_WIN32
    if (m_pExecProc){
        m_pExecProc->start(cmd);
    }
#else
    qDebug()<<cmd;
#endif
}
