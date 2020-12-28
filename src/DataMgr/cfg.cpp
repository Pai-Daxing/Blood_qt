#include "cfg.h"
#include <QDebug>

Cfg::Cfg(QObject *parent) :
    QObject(parent)
{
    m_pCfgSetting = new QSettings( PLASMA_SET_FILE, QSettings::NativeFormat );

    m_Hash.insert( NW_wlan,                "Network/isWlan"  );
    m_Hash.insert( NW_hostIp,              "Network/IPAdress"  );
    m_Hash.insert( NW_gatewayAdress,       "Network/gatewayAdress"  );
    m_Hash.insert( NW_netmask,             "Network/netmask"  );
    m_Hash.insert( NW_key,                 "Network/secrectkey"  );
    m_Hash.insert( NW_ServerAdress,        "Network/serverAdress"  );

    m_Hash.insert( ST_80Tip,               "Status/sampleTip"  );

    m_Hash.insert( CFG_targetVlm,          "Param/TargetVolume"  );
    m_Hash.insert( CFG_collectSpeed,       "Param/DrawRate"  );
    m_Hash.insert( CFG_collectRBCSpeed,    "Param/CollectRate"  );
    m_Hash.insert( CFG_lineDSens,          "Param/LineD"  );
    m_Hash.insert( CFG_volume,             "Param/SoundVol"  );
    m_Hash.insert( CFG_langID,             "Param/Language"  );
    m_Hash.insert( CFG_prsUnit,            "Param/PrsUnit"  );
    m_Hash.insert( CFG_weightUnit,         "Param/PlasmaUnit"  );
    m_Hash.insert( CFG_weightTarget,       "Param/CalibTarget"  );
    m_Hash.insert( CFG_dateFormat,         "Param/DateFormat"  );
    m_Hash.insert( CFG_timeFormat,         "Param/TimeFormat"  );
    m_Hash.insert( CFG_dataMgrSys,         "Param/DMS"  );
    m_Hash.insert( CFG_powerOffRecover,    "Param/PowerOffRecover"  );
    m_Hash.insert( CFG_usrPsw,             "Param/Passwd"  );
    m_Hash.insert( CFG_softFun,            "Param/SoftFun"  );
    m_Hash.insert( CFG_dspslIdSet,         "Param/DispslId"  );
    m_Hash.insert( CFG_acdIdSet,           "Param/AcdId"  );
    m_Hash.insert( CFG_salineIdSet,        "Param/SalineId"  );
    m_Hash.insert( CFG_donorIdSet,         "Param/DonorId"  );
    m_Hash.insert( CFG_oprtrIdset,         "Param/OprtrId"  );
    m_Hash.insert( CFG_authorized,         "Param/A%*d"  );
    m_Hash.insert( CFG_beginTime,          "Param/BeginTime"  );
    m_Hash.insert( CFG_timeLen,            "Param/TimeLen"  );
    m_Hash.insert( CFG_sampleTip,          "Param/SampleTip_En"  );
    m_Hash.insert( CFG_comDebug,           "Param/COMDebug"  );
    m_Hash.insert( CFG_resendTimeLimit,    "Param/ResendTimeLimit"  );
    m_Hash.insert( CFG_devID,              "Param/DevID"  );
    m_Hash.insert( CFG_sn,                 "Param/SN"  );

    m_Hash.insert( CFG_COM_WIN32,          "COM_Win32"  );
    m_Hash.insert( CFG_COM_LINUX,          "COM_Linux"  );
}

Cfg& Cfg::getInst()
{
    static Cfg obj;
    return obj;
}

qint32  Cfg::getUsrCfgInt( CFGSETTING id )
{
    QString strID = m_Hash.value( id );
    return m_pCfgSetting->value( strID, QVariant(QString("")) ).toInt();
}

QString  Cfg::getUsrCfgStr( CFGSETTING id )
{
    QString strID = m_Hash.value( id );
    return m_pCfgSetting->value( strID, QVariant(QString("")) ).toString();
}

void Cfg::setUsrCfgStr( CFGSETTING id, QString value )
{
    QString strID = m_Hash.value( id );
    m_pCfgSetting->setValue( strID, QVariant( value ) );
}

void Cfg::setServerName( SrvName index )
{
    QString name;
    switch ( index )
    {
    default:
    case LANGCHENG:
        name = "LangCheng";
        break;
    }

    m_pCfgSetting->setValue( "Network/serverName", QVariant( name ) );
}

SrvName  Cfg::getServerName( )
{
    SrvName ret = LANGCHENG;

    QString str = m_pCfgSetting->value( "Network/serverName", QVariant(QString("")) ).toString();

    if  ( "LangCheng" == str )
    {
        ret = LANGCHENG;
    }

    return ret;
}
