/***********************************************************************
* dlgpswsetting.cpp
* Copyright all resever(2013)
*
* 因为报警字符串不能即时翻译成多语言，所以用UI类来建，通过QEvent::LanguageChange来
* 刷新多语言字符
*
* Author              Date               Action
* lilice              2013/7/10           create
*
***********************************************************************/
#include "alarmstr.h"

AlarmString::AlarmString(QObject *parent) :
    QObject(parent)
{
    //    ui.setupUi(this);

    resetStr();
}

void AlarmString::resetStr()
{
    ALARMSTRING str[AlmType_MAX] =
    {
        { ALM_none,                 "", "" },

        {
            ALM_ComError,
            tr("控制系统通信异常"),
            tr("系统遇到了无法恢复的报警情况.\n"
            "请立即断开电源,联系用服.\n"
            "使用重力回输法进行回输.")
        },

        {
            ALM_centrHigh,
            tr("离心机速度过高"),
            tr("Details")
        },
        { ALM_centrLow,             tr("离心机速度过低"), tr("Details")},
        { ALM_bldPump_Error,        tr("血泵方向错误"), tr("血泵在采血过程中应为顺时针转动.\n")},
        { ALM_bldPump_High,         tr("血泵速度过高"), tr("Details")},
        { ALM_bldPump_Low,          tr("血泵速度过低"), tr("Details")},
        { ALM_acdPump_Low,          tr("抗凝剂泵速度过低"), tr("Details")},
        { ALM_acdPump_High,         tr("抗凝剂泵速度过高"), tr("Details")},
        { ALM_acdPump_Error,        tr("抗凝剂泵方向错误"), tr("抗凝剂泵在采血过程中应为顺时针转动.\n")},
        { ALM_prsvPump_Low,         tr("保养液泵速度过低"), tr("Details")},
        { ALM_prsvPump_High,        tr("保养液泵速度过高"), tr("Details")},
        { ALM_prsvPump_Error,       tr("保养液泵方向错误"), tr("Details")},
        { ALM_cupLink,              tr("离心杯漏液"), tr("Details")},
        { ALM_coverOpen,            tr("离心机盖未关闭"), tr("检查离心机盖是否有任何阻塞.\n")},
        { ALM_Vlv1_OpenError,        tr("血液阀打开失败"), tr("Details")},
        { ALM_Vlv1_CloseError,       tr("血液阀关闭失败"), tr("Details")},
        { ALM_Vlv2_OpenError,        tr("悬红阀打开失败"), tr("Details")},
        { ALM_Vlv2_CloseError,       tr("悬红阀关闭失败"), tr("Details")},
        { ALM_Vlv3_OpenError,        tr("血浆阀打开失败"), tr("Details")},
        { ALM_Vlv3_CloseError,       tr("血浆阀关闭失败"), tr("Details")},
        { ALM_Vlv4_CloseError,       tr("废液阀关闭失败"), tr("Details")},
        { ALM_Vlv4_OpenError,        tr("废液阀打开失败"), tr("Details")},
        { ALM_Vlv5_CloseError,       tr("保养液阀关闭失败"), tr("Details")},
        { ALM_Vlv5_OpenError,        tr("保养液阀打开失败"), tr("Details")},
        { ALM_Vlv6_CloseError,       tr("盐水阀关闭失败"), tr("Details")},
        { ALM_Vlv6_OpenError,        tr("盐水阀打开失败"), tr("Details")},
        { ALM_plsmweigh_Error,       tr("血浆重量不正常"), tr("Details")},
        { ALM_acdweigh_Error,        tr("抗凝剂重量不正常"), tr("Details")},
        { ALM_tooLong_Draw,          tr("采血过程太长"), tr("点击制备按钮以进行制备.\n")},
        { ALM_tooLong_RBC,           tr("红细胞制备时间太长"), tr("管路在血液管路空气探测器中安放正确.\n"
                                                               "管路无扭曲或阻塞.")},
        { ALM_acdLineAir,            tr("抗凝剂管路发现空气"), tr("抗凝剂袋连接正确.\n"
                                                               "抗凝剂管路正确安装到抗凝剂泵和抗凝剂管路空气探测器中.")},
        { ALM_donorLineAir,          tr("血员管路发现空气"), tr("供血浆者有足够血流.\n"
                                                             "管路在血液管路空气探测器中安放正确.")},
        { ALM_presvLineAir,          tr("保养液管路发现空气"), tr("保养液袋不是空的.\n"
                                                               "管路在保养液管路空气探测器中安放正确.")},

        { ALM_DPMopen,              tr("管路压力监测器打开"), tr("压力检测器接头（DPM）安装正确.")},
        { ALM_pressLow,             tr("采血压力过低"), tr("针头畅通，无渗血或阻塞.\n"
                                                         "管路没有扭曲或阻塞")},
        { ALM_pressHigh,            tr("采血压力过高"), tr("血泵速度是否合适.")},
        { ALM_buttonpress,          tr("按键被按下"), tr("啦啦啦啦啦啦")}

    };

    for ( int i = 0; i < AlmType_MAX; i++  )
    {
        m_str[i].type = str[i].type;
        m_str[i].str   = str[i].str;
        m_str[i].details = str[i].details;
    }
}

//void AlarmString::changeEvent(QEvent *e)
//{
//    QWidget::changeEvent(e);
//    switch (e->type()) {
//    case QEvent::LanguageChange:
//        ui.retranslateUi(this);

//        resetStr();
//        break;
//    default:
//        break;
//    }
//}
