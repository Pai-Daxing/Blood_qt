#ifndef ALARMS_H
#define ALARMS_H

typedef enum _AlarmType
{
    ALM_none = 0x00,          //无报警
    ALM_ComError,             //串口通信异常

    ALM_centrHigh,            //离心机速度过高
    ALM_centrLow,             //离心机速度过低
    ALM_bldPump_Error,        //血泵方向错误
    ALM_bldPump_High,         //血泵速度过高
    ALM_bldPump_Low,          //血泵速度过低
    ALM_acdPump_Low,          //抗凝剂泵速度过低
    ALM_acdPump_High,         //抗凝剂泵速度过高
    ALM_acdPump_Error,        //抗凝剂泵方向错误
    ALM_prsvPump_Low,         //保养液泵速度过低
    ALM_prsvPump_High,        //保养液泵速度过高
    ALM_prsvPump_Error,       //保养液泵方向错误
    ALM_cupLink,              //离心杯漏液
    ALM_coverOpen,            //离心机盖未关闭
    ALM_Vlv1_OpenError,        //盐水阀打开失败
    ALM_Vlv1_CloseError,       //盐水阀关闭失败
    ALM_Vlv2_OpenError,        //血液阀打开失败
    ALM_Vlv2_CloseError,       //血液阀关闭失败
    ALM_Vlv3_OpenError,        //血浆阀打开失败
    ALM_Vlv3_CloseError,       //血浆阀关闭失败
    ALM_Vlv4_CloseError,       //血浆阀关闭失败
    ALM_Vlv4_OpenError,        //血浆阀打开失败
    ALM_Vlv5_CloseError,       //血浆阀关闭失败
    ALM_Vlv5_OpenError,        //血浆阀打开失败
    ALM_Vlv6_CloseError,       //血浆阀关闭失败
    ALM_Vlv6_OpenError,        //血浆阀打开失败
    ALM_plsmweigh_Error,       //血浆重量不正常
    ALM_acdweigh_Error,        //抗凝剂重量不正常
    ALM_tooLong_Draw,          //采血过程太长
    ALM_tooLong_RBC,           //红细胞制备时间太长
    ALM_acdLineAir,            //抗凝剂管路发现空气
    ALM_donorLineAir,          //血员管路发现空气
    ALM_presvLineAir,          //保养液管路发现空气

    ALM_DPMopen,              //管路压力监测器打开
    ALM_pressLow,             //采血压力过低
    ALM_pressHigh,            //采血压力过高
    ALM_buttonpress,          //按键

    AlmType_MAX,
} AlarmType;


//错误代码
typedef enum _ErrorCode
{
     EC_NONE = 0
    ,EC_ST_AirD1_F = 1
    ,EC_ST_AirD2_F
    ,EC_ST_AirD3_F
    ,EC_ST_VlvT1_F
    ,EC_ST_VlvT2_F
    ,EC_ST_VlvT3_F
    ,EC_ST_VlvT4_F
    ,EC_ST_VlvT5_F
    ,EC_ST_VlvT6_F
    ,EC_ST_Pump1_F
    ,EC_ST_Pump2_F
    ,EC_ST_Pump3_F
    ,EC_ST_Line_F
    ,EC_ST_CF_F
    ,EC_ST_DPM_F
    ,EC_ST_DPM_F1
    ,EC_ST_Scale1_F
    ,EC_ST_Scale2_F
    ,EC_ST_Leak_F
    ,EC_ST_Cover_F

    ,EC_SF_AirD1_F
    ,EC_SF_AirD2_F
    ,EC_SF_AirD3_F
    ,EC_SF_VlvT1_F
    ,EC_SF_VlvT2_F
    ,EC_SF_VlvT3_F
    ,EC_SF_VlvT4_F
    ,EC_SF_VlvT5_F
    ,EC_SF_VlvT6_F

    ,EC_MAX
} ErrorCode;

#endif // ALARMS_H
