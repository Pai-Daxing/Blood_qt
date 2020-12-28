#include "datamgr.h"
#include <QDebug>

DataMgr::DataMgr()
{
}

DataMgr& DataMgr::getInst()
{
    static DataMgr inst;
    return inst;
}

qint32 DataMgr::init()
{
    qint32 ret = 1;
//    qDebug() << "doing DataMgr initialize ";

    Cfg::getInst();

    return ret;
}

qint32 DataMgr::getFacCfgInt(CFGSETTING id)
{
    return Cfg::getInst().getUsrCfgInt(id);
}

qint32 DataMgr::getUsrCfgInt(CFGSETTING id)
{
    return Cfg::getInst().getUsrCfgInt(id);
}

bool DataMgr::setUsrCfgInt(CFGSETTING id, qint32 value)
{
    Cfg::getInst().setUsrCfgStr(id, QString::number(value));
    return true;
}

bool DataMgr::setUsrCfgStr(CFGSETTING id, QString value)
{
    Cfg::getInst().setUsrCfgStr(id, value);
    return true;
}

QString DataMgr::getUsrCfgStr(CFGSETTING id)
{
    return Cfg::getInst().getUsrCfgStr(id);
}

QString DataMgr::getTimeFormat()const
{
    QString timeFormat = "hh:mm";
    if ( H12_FORMAT == DataMgr::getInst().getUsrCfgInt(CFG_timeFormat))
    {
        timeFormat = "hh:mm AP";
    }

    return timeFormat;
}

bool DataMgr::resetUsrCfg()
{
    return true;
}

QString DataMgr::getDateFormat()const
{
    // "dd/MM/yyyy"  "yyyy/MM/dd"  "MM/dd/yyyy" "yyyy.MM.dd" "MM.dd.yyyy"

    return DataMgr::getInst().getUsrCfgStr(CFG_dateFormat);
}

QString DataMgr::getDateTimeFormat()const
{
    return getDateFormat() + QString(" ") + getTimeFormat();
}

QString DataMgr::getTimeDateFormat()const
{
    return getTimeFormat() + QString("\n") + getDateFormat();
}
