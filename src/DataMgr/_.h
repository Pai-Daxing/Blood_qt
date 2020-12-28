#ifndef CFGMGR_H
#define CFGMGR_H
#include "../Protocol/types.h"
#include <qfile.h>

enum CfgID
{   //只能追加！不能更改已定义的ID值
    //CFG_version,
    CFG_drawRate,     //采集速度
    CFG_returnRate,   //回输速度
    CFG_cuffPrs,      //袖带压力
    CFG_ACFactor,     //抗凝剂比例因子
    CFG_NaClVol,      //盐水目标量
    CFG_NaClCycVol,   //盐水循环量
    CFG_plsmVol,      //采集目标量
    CFG_plsmCycVol,   //采集循环量
    CFG_lineDSens,    //管探灵敏度
    CFG_volume,       //音量
    //CFG_devID,        //设备号
    CFG_langID,       //语言
    CFG_prsUnit,      //压力单位
    CFG_weightUnit,   //体重单位
    CFG_weightTarget, //重量校准目标值
    CFG_dateFormat,   //日期显示
    CFG_timeFormat,   //小时制
    CFG_Scaner,       //扫码器
    CFG_battery,      //电池
    CFG_dataMgrSys,   //数据管理系统
    CFG_powerOffRecover,//掉电恢复
    CFG_usrPsw,       //用户密码
    CFG_softFun,      //软件功能配置项
    CFG_dspslIdSet,  //耗材ID录入设置值
    CFG_acdIdSet,    //抗凝剂ID录入设置值
    CFG_salineIdSet, //盐水ID录入设置值
    CFG_donorIdSet,  //供浆员ID录入设置值
    CFG_oprtrIdset,  //操作者ID录入设置值
    CFG_tscalib,      //执行了触摸屏校准
    CFG_wlan,         //是否设置为无线连接
    CFG_authorized,   //是否已授权
    CFG_hostIp,         //主机的ip
    CFG_beginTime,    //采集开始时间
    CFG_timeLen,       //采集时长
    CFG_sampleTip,    //血液留样提醒
    CFG_comDebug,    //串口调试功能
    CFG_resendTimeLimit, //采浆记录重新上传时间限
    CFG_gatewayAdress,   //网关地址
    CFG_netmask,            //子网掩码
    CFG_MAX
};

enum CfgStrID
{
    CFG_STR_devID,    //机器号
    CFG_STR_sn,       //产品序列号
    CFG_STR_dspslIdSet,   //耗材ID录入设置值
    CFG_STR_acdIdSet,     //抗凝剂ID录入设置值
    CFG_STR_salineIdSet,  //盐水ID录入设置值
    CFG_STR_donorIdSet,  //供浆员ID录入设置值
    CFG_STR_oprtrIdset,   //操作者ID录入设置值
    CFG_STR_key,            //网络传输使用的密钥
    CFG_STR_ServerAdress,   //服务器地址
    CFG_STR_MAX
};

enum
{
    CFG_SIZE = 4,  //每个整型配置项的长度（字节数）
    CFG_STR_SIZE = 200, //每个str型配置项的长度（字节数）
};

// 抗凝剂全血比
//enum enumACFactor
//{
//    AC1_BLOOD8,     //1:8
//    AC1_BLOOD9,     //1:9
//    AC1_BLOOD10,    //1:10
//    AC1_BLOOD11,    //1:11
//    AC1_BLOOD12,    //1:12
//    AC1_BLOOD13,    //1:13
//    AC1_BLOOD14,    //1:14
//    AC1_BLOOD15,    //1:15
//    AC1_BLOOD16     //1:16
//};

// 语言配置项
enum enumLang
{
    ZH_CN,          //中文
    ENGLISH,        //英文
    GERMAN,         //德语
    ITALIAN,        //意大利语
    PORTUGUESE,     //葡萄牙语
    RUSSIAN,        //俄语
    FRENCH,         //法语
    SPAINISH,       //西班牙语
    LANG_MAX
};
// 选配外设配置项
enum enumDevExist
{
    CFG_FALSE,        //有外设
    CFG_TRUE        //无外设
};

// 日期显示配置
enum DateDisplay
{
    YYMMDD,         //YYYY/MM/DD
    MMDDYY,         //MM/DD/YYYY
    YY_MM_DD,       //YYYY-MM-DD
    MM_DD_YY        //MM-DD-YYYY
};
// 时钟显示配置
enum TimeDisplay
{
    H24_FORMAT,     //24小时
    H12_FORMAT,     //12小时
};

// 压力单位配置
enum Prs_Unit
{
    kPa,
    mmHg
};

// 体重单位配置
enum Weight_Unit
{
    ml,
    g
};

// 选配软件功能配置项
enum enumSoftwareFun
{
    SW_Default,            //默认软件
    SW_PlasmaRep,       //血浆置换
    SW_RongSheng,       //蓉生定制
    SW_RongShengTest,  //蓉生验证
};

class CfgMgr
{
public:
    CfgMgr();
    ~CfgMgr();

    bool  init();

    //获取指定整型配置项的厂家缺省值（如果指定的配置项不存在，返回-1）
    s32  getFacCfgInt(CfgID id);

    //获取指定整型配置项的用户设置值（如果指定的配置项不存在，返回-1）
    s32  getUsrCfgInt(CfgID id);

    //设置指定整型配置项的用户设置值（如果指定的配置项不存在，返回false）
    bool setUsrCfgInt(CfgID id, s32 value);

    //获取指定字符型配置项的用户设置值（如果指定的配置项不存在，返回空）
    QString  getUsrCfgStr(CfgStrID id);

    //设置指定字符型配置项的用户设置值（如果指定的配置项不存在，返回false）
    bool setUsrCfgStr(CfgStrID id, QString value);


    bool resetUsrCfg();

    //重置所有整型配置项的用户设置值
    bool resetUsrCfgInt();

    //重置所有字符型配置项的用户设置值
    bool resetUsrCfgStr();

    QFile   m_usrFile;
    s32     m_usrValue[CFG_MAX];
    QFile   m_strFile;
};

#endif // CFGMGR_H
