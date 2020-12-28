#ifndef DATAMGR_H
#define DATAMGR_H

#include "cfg.h"
class Logger;
class QObject;
class QFile;

class DataMgr
{
public:
    enum ERR_MASK
    {
        ERR_RST = 0x1,
        ERR_ALM = 0x2,
        ERR_OPT = 0x4,
        ERR_CFG = 0x8
    };

public:
    static DataMgr& getInst();
    qint32      init();

    //获取指定整型配置项的厂家缺省值（如果指定的配置项不存在，返回-1）
    qint32  getFacCfgInt(CFGSETTING id);

    //获取指定整型配置项的用户设置值（如果指定的配置项不存在，返回-1）
    qint32  getUsrCfgInt(CFGSETTING id);

    //设置指定整型配置项的用户设置值（如果指定的配置项不存在，返回false）
    bool setUsrCfgInt(CFGSETTING id, qint32 value);

    //设置指定字符型配置项的用户设置值（如果指定的配置项不存在，返回false）
    bool setUsrCfgStr(CFGSETTING id, QString value);

    //获取指定字符型配置项的用户设置值（如果指定的配置项不存在，返回空字串）
    QString getUsrCfgStr(CFGSETTING id);

    bool resetUsrCfg();

    QString getDateFormat()const;
    QString getTimeFormat()const;
    QString getDateTimeFormat()const;
    QString getTimeDateFormat()const;

private:
    explicit DataMgr();

};

#endif // DATAMGR_H
