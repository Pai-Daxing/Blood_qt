#ifndef CFG_H
#define CFG_H

#include <QObject>
#include <QSettings>

#define PLASMA_SET_FILE  ("./Datas/cfg.ini")

enum CFG_BOOL
{
    CFG_NO,
    CFG_YES
};

enum CFG_SW_CUN
{
    SW_Plasma,
    SW_PlasmaRep
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

enum CFGSETTING
{
     CFG_stepCycleNumber             //循环数累计值
    ,CFG_stepVolumeOfPlasma          //置换量累计
    ,CFG_stepVolumeOfACD             //抗凝剂量累计
    ,CFG_stepVolumeOfNaCl            //盐水量累计
    ,CFG_stepCycleVolumeInReturn     //回输处理量累计
    ,CFG_stepCycleVolumeInDraw       //采集处理量累计

    ,CFG_perbagVol                    //血浆置换转移量，即每袋置换多少血浆
    ,CFG_tmpPerbagVol                 //血浆置临时换转移量

    ,NW_wlan             //是否设置为无线连接
    ,NW_hostIp           //主机的ip
    ,NW_gatewayAdress    //网关
    ,NW_netmask          //子网掩码
    ,NW_key              //密钥
    ,NW_ServerAdress     //服务器地址

    ,ST_80Tip            //采样提示状态
    ,CFG_targetVlm       //采集速度
    ,CFG_collectSpeed    //制备速度
    ,CFG_collectRBCSpeed //袖带压力
    //,CFG_ACFactor        //抗凝剂比例因子
    ,CFG_lineDSens       //管探灵敏度
    ,CFG_volume          //音量
    ,CFG_langID          //语言
    ,CFG_prsUnit         //压力单位
    ,CFG_weightUnit      //体重单位
    ,CFG_weightTarget    //重量校准目标值
    ,CFG_dateFormat      //日期显示
    ,CFG_timeFormat      //小时制
    ,CFG_dataMgrSys      //数据管理系统
    ,CFG_powerOffRecover //掉电恢复
    ,CFG_usrPsw          //用户密码
    ,CFG_softFun         //软件功能配置项
    ,CFG_dspslIdSet      //耗材ID录入设置值
    ,CFG_acdIdSet        //抗凝剂ID录入设置值
    ,CFG_salineIdSet     //盐水ID录入设置值
    ,CFG_donorIdSet      //供浆员ID录入设置值
    ,CFG_oprtrIdset      //操作者ID录入设置值
    ,CFG_authorized      //是否已授权
    ,CFG_hostIp          //主机的ip
    ,CFG_beginTime       //采集开始时间
    ,CFG_timeLen         //采集时长
    ,CFG_sampleTip       //血液留样提醒
    ,CFG_comDebug        //串口调试功能
    ,CFG_resendTimeLimit //采浆记录重新上传时间限

    ,CFG_devID           //机器号
    ,CFG_sn              //产品序列号

    ,CFG_COM_WIN32
    ,CFG_COM_LINUX
};

enum SrvName
{
     LANGCHENG            //朗程信息系统
};

class Cfg : public QObject
{
    Q_OBJECT
    public:

    static Cfg& getInst();
    //获取指定字符型配置项的用户设置值（如果指定的配置项不存在，返回空）
    QString  getUsrCfgStr(CFGSETTING id);

    //获取指定整型配置项的用户设置值（如果指定的配置项不存在，返回空）
    qint32  getUsrCfgInt(CFGSETTING id);

    //设置指定字符型配置项的用户设置值（如果指定的配置项不存在，返回false）
    void setUsrCfgStr(CFGSETTING id, QString value);

    void setServerName( SrvName index );
    SrvName  getServerName( );
private:
    Cfg( QObject *parent = 0 );

signals:
    
public slots:

private:
    QSettings *m_pCfgSetting;
    QHash< int, QString > m_Hash;
};

#endif // CFG_H
