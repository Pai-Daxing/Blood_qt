#include "cfgmgr.h"
#include "datastorage.h"
#include<QDebug>

const static s32 s_facValue[CFG_MAX] =
{ //厂家缺省值
  //0x0001,       //软件版本 不考虑配置兼容
  60,           //采集速度
  60,           //回输速度
  60,           //袖带压力
  16,           //抗凝剂比例因子
  200,          //盐水目标量
  50,           //盐水循环量
  600,          //采集目标量
  200,          //采集循环量
  85,           //管探灵敏度
  30,           //音量
  //1234,         //设备号
  ZH_CN,        //语言
  kPa,          //压力单位
  g,           //体重单位
  600,          //重量校准目标值
  YYMMDD,       //日期显示
  H24_FORMAT,   //小时制
  CFG_FALSE,    //扫码器
  CFG_FALSE,    //电池
  CFG_FALSE,    //数据管理系统
  CFG_FALSE,    //掉电恢复
  0x08080808,   //用户密码
  CFG_FALSE,    //血浆置换
  1,            //耗材ID录入设置值
  1,            //抗凝剂ID录入设置值
  1,            //盐水ID录入设置值
  1,            //浆员ID录入设置值
  1,            //操作者ID录入设置值
  0,            //执行了触摸屏校准
  0,            //是否选择无线网络连接
  0,            //是否已授权
  0xc0a80004,   //数据管理主机IP
  0,                 //采集开始时间
  0,                 //采集时长
  CFG_FALSE,    //血液留样提醒
  CFG_FALSE,    //串口调试功能
  40,               //采浆记录重新上传时间限
  0xc0a80001,   //网关地址
  0xffffff00,   //子网掩码
};

const static char s_facStr[CFG_STR_MAX][CFG_STR_SIZE] =
{
    {"0"},
    {""},
    {""},
    {""},
    {""},
    {""},
    {""},
    {"LBJKKPOLKFKLKCOKRMPJJRVW"},
    {"http://125.71.208.40:7777/bip"},
};

CfgMgr::CfgMgr()
{
    memcpy(&m_usrValue, &s_facValue, CFG_SIZE * CFG_MAX);
    m_usrFile.setFileName("./Datas/CFG/UsrCfgFile");
    m_strFile.setFileName("./Datas/CFG/StrCfgFile");
}

CfgMgr::~CfgMgr()
{
    m_usrFile.close();
    m_strFile.close();
}

bool CfgMgr::init()
{
    if (!m_strFile.open(QIODevice::ReadOnly))
    {
        resetUsrCfgStr();
    }
    m_strFile.close();

    QString logStr;
    s64 nLen  = CFG_SIZE * CFG_MAX;
    bool bRet = false;
    if (m_usrFile.open(QIODevice::ReadOnly))
    {
        if (m_usrFile.seek(0))
        {
            s64 nReadLen = m_usrFile.read((char*)(&m_usrValue), nLen);
            if (nLen == nReadLen)
            {
                bRet = true;
                //qDebug()<<"CfgData loading success!";
            }
            else
            {
                logStr = QString("CfgData read read failed!%1").arg(nReadLen);
                DataStorage::getInstance().saveUsrLog(logStr);
                qDebug()<< logStr;
            }
        }
        else
        {
            logStr = "CfgData read seek failed!";
            DataStorage::getInstance().saveUsrLog( logStr );
            qDebug()<< logStr;
        }
        m_usrFile.close();
    }
    else
    {
        logStr = "CfgData read open failed.--Ignore if it's the first time after upgrade";
        DataStorage::getInstance().saveUsrLog( logStr );
        qDebug()<< logStr;
    }

    if (!bRet)
    {
        bRet = resetUsrCfgInt();
    }

    return bRet;
}

bool CfgMgr::resetUsrCfg()
 {
     return resetUsrCfgInt() && resetUsrCfgStr();
 }

bool CfgMgr::resetUsrCfgInt()
{
    bool bRet = false;
    s64 nLen  = CFG_SIZE * CFG_MAX;

    QString logStr;

    memcpy(&m_usrValue, &s_facValue, CFG_SIZE * CFG_MAX);
    if (m_usrFile.open(QIODevice::ReadWrite))
    {
        if (m_usrFile.seek(0))
        {
            if (nLen == m_usrFile.write((char*)(&s_facValue), nLen))
            {
                if (m_usrFile.flush())
                {
                    bRet = true;
                    //qDebug()<<"CfgData rewrite success!";
                }
                else
                {
                    logStr = "CfgData rewrite flush failed!";
                    DataStorage::getInstance().saveUsrLog( logStr );
                }
            }
            else
            {
                logStr = "CfgData rewrite write failed!";
                DataStorage::getInstance().saveUsrLog( logStr );
            }
        }
        else
        {
            logStr = "CfgData rewrite seek failed!";
            DataStorage::getInstance().saveUsrLog(logStr);
            qDebug()<< logStr;
        }
        m_usrFile.close();
    }
    else
    {
        logStr = "CfgData rewrite open failed!";
        DataStorage::getInstance().saveUsrLog( logStr );
        qDebug()<< logStr;
    }

    return bRet;
}

bool CfgMgr::resetUsrCfgStr()
{
    bool bRet = false;
    QString logStr;

    if (m_strFile.open(QIODevice::ReadWrite))
    {
        s64 wLen = CFG_STR_MAX * CFG_STR_SIZE;
        if (wLen != m_strFile.write((char*)s_facStr, wLen))
        {
            logStr = "CfgStr init write write failed!";
            DataStorage::getInstance().saveUsrLog( logStr );
            qDebug()<< logStr;
        }
        else
        {
            m_strFile.flush();
            bRet = true;
        }

        m_strFile.close();
    }
    else
    {
        logStr = "CfgStr init write open failed";
        DataStorage::getInstance().saveUsrLog( logStr );
        qDebug()<< logStr;
    }

    return bRet;
}

s32 CfgMgr::getFacCfgInt(CfgID id)
{
    s32 value = -1;
    if (id < CFG_MAX)
    {
        value = s_facValue[id];
    }
    else
    {
        Q_ASSERT_X(0, "CfgMgr::getFacCfgInt", "get FacCfgInt failed: id > CFG_MAX");
    }
    return value;
}

s32 CfgMgr::getUsrCfgInt(CfgID id)
{
    s32 value = -1;
    if (id < CFG_MAX)
    {
        value = m_usrValue[id];
    }
    else
    {
        Q_ASSERT_X(0, "CfgMgr::getUsrCfgInt", "get UsrCfgInt failed: id > CFG_MAX");
    }
    return value;
}

bool CfgMgr::setUsrCfgInt(CfgID id, s32 value)
{
    bool ret = false;
    if (id >= CFG_MAX)
        return false;

    if (value == m_usrValue[id])
        return true;

    QString logStr;

    if (m_usrFile.open(QIODevice::ReadWrite))
    {
        if (m_usrFile.seek(id * CFG_SIZE))
        {
            if (CFG_SIZE == m_usrFile.write((char*)(&value), CFG_SIZE))
            {
                ret = m_usrFile.flush();
                if (!ret)
                {
                    logStr = QString("CfgData set %1 flush failed!").arg(id);
                    DataStorage::getInstance().saveUsrLog( logStr );
                    qDebug()<< logStr;
                }

            }
            else
            {
                logStr = QString("CfgData set %1 write failed!").arg(id);
                DataStorage::getInstance().saveUsrLog(logStr);
                qDebug()<< logStr;
            }
        }
        else
        {
            logStr = QString("CfgData set %1 seek failed!").arg(id);
            DataStorage::getInstance().saveUsrLog(logStr);
            qDebug()<< logStr;
        }
        m_usrFile.close();
    }
    else
    {
        logStr = QString("CfgData set %1 open failed!").arg(id);
        DataStorage::getInstance().saveUsrLog(logStr);
        qDebug()<< logStr;
    }

    if ( ret )
    {
        m_usrValue[id] = value;

        logStr = QString("CfgData set %1 success!").arg(id);
        //qDebug() << logStr;
    }
    return ret;
}

bool CfgMgr::setUsrCfgStr(CfgStrID id, QString value)
{
    bool ret = false;
    if (id >= CFG_STR_MAX)
        return false;

    QString logStr;

    if (m_strFile.open(QIODevice::ReadWrite))
    {
        if (m_strFile.seek(id * CFG_STR_SIZE))
        {
            if (CFG_STR_SIZE == m_strFile.write(value.toAscii(), CFG_STR_SIZE))
            {
                ret = m_strFile.flush();
                if (!ret)
                {
                    logStr = QString("CfgStr set %1 flush failed!").arg(id);
                    DataStorage::getInstance().saveUsrLog(logStr);
                    qDebug()<< logStr;
                }
            }
            else
            {
                logStr = QString("CfgStr set %1 write failed!").arg(id);
                DataStorage::getInstance().saveUsrLog(logStr);
                qDebug()<< logStr;
            }
        }
        else
        {
            logStr = QString("CfgStr set %1 seek failed!").arg(id);
            DataStorage::getInstance().saveUsrLog(logStr);
            qDebug()<< logStr;
        }
        m_strFile.close();
    }
    else
    {
        logStr = QString("CfgStr set %1 open failed!").arg(id);
        DataStorage::getInstance().saveUsrLog(logStr);
        qDebug()<< logStr;
    }

    if ( ret )
    {
        logStr = QString("CfgStr set %1 success!").arg(id);
        //qDebug() << logStr;
    }
    return ret;
}

QString CfgMgr::getUsrCfgStr(CfgStrID id)
{
    QString ret = "";
    if (id >= CFG_STR_MAX)
        return ret;

    QString logStr;

    if (m_strFile.open(QIODevice::ReadOnly))
    {
        if (m_strFile.seek(id * CFG_STR_SIZE))
        {
            char tmp[CFG_STR_SIZE] = {0};
            if (CFG_STR_SIZE == m_strFile.read(tmp, CFG_STR_SIZE))
            {
                ret = QString(tmp);
                logStr = QString("CfgStr get %1 read success!").arg(id);
                //qDebug()<< logStr;

            }
            else
            {
                logStr = QString("CfgStr get %1 read failed!").arg(id);
                DataStorage::getInstance().saveUsrLog(logStr);
                qDebug()<< logStr;
            }
        }
        else
        {
            logStr = QString("CfgStr get %1 seek failed!").arg(id);
            DataStorage::getInstance().saveUsrLog(logStr);
            qDebug()<< logStr;
        }
        m_strFile.close();
    }
    else
    {
        logStr = QString("CfgStr get %1 open failed!").arg(id);
        DataStorage::getInstance().saveUsrLog(logStr);
        qDebug()<< logStr;
    }

    return ret;
}
