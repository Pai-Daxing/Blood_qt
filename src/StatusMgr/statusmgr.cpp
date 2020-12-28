#include "statusmgr.h"
#include "../DataMgr/datamgr.h"
#include "../ParamMgr/parammgr.h"
#include "../SerialApp/serialapp.h"

StatusMgr::StatusMgr(QObject *parent):
    QObject(parent),
    m_curStatus(CSS_unknown),
    m_preStatus(CSS_unknown),
    m_workingStatus( WS_BUSY ),
    mSTErrNo(0),
    mbIsQuitDraw(false)
{

}

void StatusMgr::init(QObject *sender)
{
    connect(sender, SIGNAL(setCtrlSysStatus(qint16)),\
            this, SLOT(onSetControlSystemStatus(qint16)));
    connect(sender, SIGNAL(setErrNo(qint16)),\
            this, SLOT(updateErrNo(qint16)));
    connect(this, SIGNAL(controlSystemStatusChanged(qint16)),\
            this, SLOT(onControlSystemStatusChanged(qint16)));
}

StatusMgr& StatusMgr::getInstance()
{
    static StatusMgr instance;
    return instance;
}

void StatusMgr::updateErrNo(qint16 no)
{
    if (no > EC_MAX || no < 0)
        no = 0;

    mSTErrNo = no;
}

QString StatusMgr::getErrStr()
{
    static TestErrMsg s[]={
        {EC_NONE, tr("")},
        {EC_ST_AirD1_F, tr("血液空探自检失败")},
        {EC_ST_AirD2_F, tr("保养液空探自检失败")},
        {EC_ST_AirD3_F, tr("抗凝剂空探自检失败")},
        {EC_ST_VlvT1_F, tr("阀1自检失败")},
        {EC_ST_VlvT2_F, tr("阀2自检失败")},
        {EC_ST_VlvT3_F, tr("阀3自检失败")},
        {EC_ST_VlvT4_F, tr("阀4自检失败")},
        {EC_ST_VlvT5_F, tr("阀5自检失败")},
        {EC_ST_VlvT6_F, tr("阀6自检失败")},
        {EC_ST_Pump1_F, tr("血泵自检失败")},
        {EC_ST_Pump2_F, tr("抗凝剂泵自检失败")},
        {EC_ST_Pump3_F, tr("保养液泵自检失败")},
        {EC_ST_Line_F,  tr("红细胞探测器自检失败")},
        {EC_ST_CF_F,    tr("离心机自检失败")},
        {EC_ST_DPM_F,   tr("压力监测器安装故障")},
        {EC_ST_DPM_F1,   tr("压力监测器压力值故障")},
        {EC_ST_Scale1_F, tr("血浆秤自检失败")},
        {EC_ST_Scale2_F, tr("支杆秤自检失败")},
        {EC_ST_Leak_F,  tr("漏液检查失败")},
        {EC_ST_Cover_F,  tr("盖开关异常打开")},

        {EC_SF_AirD1_F, tr("血液空探自检失败")},
        {EC_SF_AirD2_F, tr("保养液空探自检失败")},
        {EC_SF_AirD3_F, tr("抗凝剂空探自检失败")},
        {EC_SF_VlvT1_F, tr("阀1自检失败")},
        {EC_SF_VlvT2_F, tr("阀2自检失败")},
        {EC_SF_VlvT3_F, tr("阀3自检失败")},
        {EC_SF_VlvT4_F, tr("阀4自检失败")},
        {EC_SF_VlvT5_F, tr("阀5自检失败")},
        {EC_SF_VlvT6_F, tr("阀6自检失败")}
    };

    QString str = "";
    for (int i = 0; i < EC_MAX; i++){
        if (s[i].code == mSTErrNo)
            str = s[i].str;
    }
    return str;
}

void StatusMgr::onSetControlSystemStatus(qint16 newStatus)
{
    qint16 curStatus = (qint16)m_curStatus;
    if (newStatus != curStatus)
    {
        m_preStatus = m_curStatus;

        switch (newStatus)
        {
        case CSS_selftest_over:
            m_workingStatus = WS_FREE;
            if (mSTErrNo == 0){
                SerialApp::getInstance().send( CMD_quit_selftest );
            }
            break;
        case CSS_drawing:
//        case CSS_returning:
//        case CSS_draw_preparing:
//        case CSS_return_preparing:
        case CSS_collect_paused:
//            if (curStatus != CSS_drawing && curStatus != CSS_returning
//                    && curStatus != CSS_draw_preparing && curStatus != CSS_return_preparing
//                    && curStatus != CSS_collect_paused && curStatus != CSS_collect_stopping
//                    && curStatus != CSS_collect_over)
            {
                emit colctBegin();
            }
            break;
        case CSS_collect_over:
            emit colctEnd();
            break;
        case CSS_alarm_paused:
            emit enterAlarmPause();
            break;
        case CSS_debug:
            emit enterDebug();
            break;
        default:
            break;
        }
        switch(curStatus)
        {
        case CSS_alarm_paused:
            emit leaveAlarmPause();
            break;
        case CSS_debug:
            emit leaveDebug();
            break;
        case CSS_unknown:
            if (CSS_standby == newStatus){
                SerialApp::getInstance().send( CMD_start_selftest );
            }

            emit controlSystemConnected(newStatus);
            break;
        default:
            break;
        }

        if (newStatus == CSS_collect_paused && curStatus == CSS_alarm_paused)
        {
            emit colctPauseRecover();
        }

        m_curStatus = (ControlSystemStatus)newStatus;
        emit controlSystemStatusChanged(newStatus);
    }
}

void StatusMgr::onControlSystemStatusChanged(qint16 newStatus)
{
    ControlSystemStatus status = (ControlSystemStatus)newStatus;
//        switch (status)
//        {
//        case CSS_selftest_begin:
//            m_count_ST = 0;
//            break;
//        case CSS_acdAD_checking:
//            m_count_ST++;
//            break;
//        case CSS_AD1_checking:
//            m_count_ST++;
//            break;
//        case CSS_AD2_checking:
//            m_count_ST++;
//            break;
//        case CSS_bloodV_checking:
//            m_count_ST++;
//            break;
//        case CSS_plasmaV_checking:
//            m_count_ST++;
//            break;
//        case CSS_naclV_checking:
//            m_count_ST++;
//            break;
//        case CSS_acdP_checking:
//            m_count_ST++;
//            break;
//        case CSS_bloodP_checking:
//            m_count_ST++;
//            break;
//        case CSS_line_checking:
//            m_count_ST++;
//            break;
//        case CSS_CF_checking:
//            m_count_ST++;
//            break;
//        case CSS_PD_checking:
//            m_count_ST++;
//            break;
//        case CSS_Scale_checking:
//            m_count_ST++;
//            break;
//        case CSS_leak_checking:
//            m_count_ST++;
//            break;
//        case CSS_close_waiting:
//            m_count_ST++;
//            break;
//        case  CSS_selftest_over:
//            m_count_ST++;
//            break;
//        case CSS_collect_begin:
//            m_count_CLT = 0;
//            break;
//        case CSS_CLT_bloodAD_passed:
//            m_count_CLT++;
//            break;
//        case CSS_CLT_acdAD_passed:
//            m_count_CLT++;
//            break;
//        case CSS_CLT_AD1_passed:
//            m_count_CLT++;
//            break;
//        case CSS_CLT_AD2_passed:
//            m_count_CLT++;
//            break;
//        case CSS_CLT_bloodV_passed:
//            m_count_CLT++;
//            break;
//        case CSS_CLT_plasmaV_passed:
//            m_count_CLT++;
//            break;
//        case CSS_CLT_naclV_passed:
//            m_count_CLT++;
//            break;
//        default:
//            break;
//        }
}
