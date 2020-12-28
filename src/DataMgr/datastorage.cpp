#include "datastorage.h"
#include <QtGui>
#include <QtSql>
//#include <QMessageBox>
#include "../AlarmMgr/alarmstr.h"
DataStorage::DataStorage(QObject *parent) :
    QObject(parent)
{
}

/***********************************************************************
* 初始化数据存储模块，建立数据库 PlasmaDb，建立表格resultTb、alarmTb、logTb
*
*
* Author              Date               Action
* lilice               2013/1/28          create
*  lilice              2015/11/17        modified
***********************************************************************/
bool DataStorage::init()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName( "./Datas/PlasmaDb" );

    if (!db.open())
    {
        qDebug()<<"DataStorage::init";
//        QMessageBox::critical(0, "Cannot open database",
//                              "Unable to establish a database connection", QMessageBox::Cancel);
        return false;
    }

    return initDbTable();
}

// 分别创建采集结果、报警记录和日志记录三张表格
bool DataStorage::initDbTable()
{
    bool rtval = false;
    m_pUploadedRstTb = new ResultTable( "UploadedRstTb" );
    m_pNotUploadRstTb = new ResultTable( "NotUploadRstTb" );
    m_pUploadFailRstTb = new ResultTable( "UploadFailRstTb" );
    m_pLogTb               = new LogTable( "LogTb" );
    m_pUsrLogTb           = new LogTable( "UsrLogTb" );
    m_pAlarmTb            = new AlarmTable( "AlarmTb" );
    m_pParamTb            = new ParamTable("ParamTb");

    if ( 0 == m_pUploadedRstTb||
         0 == m_pNotUploadRstTb||
         0 == m_pUploadFailRstTb||
         0 == m_pLogTb||
         0 == m_pAlarmTb||
         0 == m_pParamTb||
         0 == m_pUsrLogTb)
    {
        return false;
    }

    rtval = m_pUploadedRstTb->create();
    rtval = rtval && m_pNotUploadRstTb->create();
    rtval = rtval && m_pUploadFailRstTb->create();
    rtval = rtval &&  m_pLogTb->create();
    rtval = rtval && m_pAlarmTb->create();
    rtval = rtval && m_pUsrLogTb->create();
    rtval = rtval && m_pParamTb->create();

    return rtval;
}

QString DataStorage::getTableName( TABLETYPE type )
{
    DBTable *pTb = NULL;
    QString str = "";

    switch( type )
    {
    case UPLOADEDRST_TB:
        pTb = (DBTable *)m_pUploadedRstTb;
        break;
    case UPLOADFAILRST_TB:
        pTb = (DBTable *)m_pUploadFailRstTb;
        break;
    case NOTUPLOADRST_TB:
        pTb = (DBTable *)m_pNotUploadRstTb;
        break;
    case ALM_TB:
        pTb = (DBTable *)m_pAlarmTb;
        break;
    case LOG_TB:
        pTb = (DBTable *)m_pLogTb;
        break;
    case USR_LOG_TB:
        pTb = (DBTable *)m_pUsrLogTb;
        break;
    case PAR_TB:
        pTb = (DBTable *)m_pParamTb;
        break;
    default:
        Q_ASSERT(0);
        break;
    }

    if ( NULL != pTb )
    {
        str = pTb->getTableName();
    }

    return str;
}

//// 保存到数据库对应表格的接口
void DataStorage::saveUploadedRst( const RecRst & rst)
{
    Q_ASSERT( m_pUploadedRstTb );

    if ( !m_pUploadedRstTb->addRec( rst ) )
    {

    }
}

void DataStorage::saveUploadFailRst( const RecRst & rst)
{
    Q_ASSERT( m_pUploadFailRstTb );

    if ( !m_pUploadFailRstTb->addRec( rst ) )
    {

    }
}

void DataStorage::saveNotUploadRst( const RecRst & rst)
{
    Q_ASSERT( m_pNotUploadRstTb );

    if ( !m_pNotUploadRstTb->addRec( rst ) )
    {

    }
}

void DataStorage::saveUsrLog( QString str )
{
    LogRec log;
    log.time = QDateTime::currentDateTime();
    log.str = str;

    saveUsrLog(log);
}

void DataStorage::saveUsrLog( const LogRec &log )
{
    Q_ASSERT( m_pUsrLogTb );

    if ( !m_pUsrLogTb->addRec( log ) )
    {

    }
}

void DataStorage::saveData(const AlarmRec &alm)
{
    Q_ASSERT( m_pAlarmTb );

    if ( !m_pAlarmTb->addRec( alm ) )
    {

    }
}

void DataStorage::saveParam(const ParamRec &par)
{
    Q_ASSERT( m_pParamTb );

    if ( !m_pParamTb->addRec( par ) )
    {

    }
}

void DataStorage::saveLog( QString str )
{
    LogRec log;
    log.time = QDateTime::currentDateTime();
    log.str = str;

    saveLog(log);
}

void DataStorage::saveLog(const LogRec &log)
{
    Q_ASSERT( m_pLogTb );

    if ( !m_pLogTb->addRec( log ) )
    {

    }
}

//// 删除对应数据库表格记录的接口

void DataStorage::delAllDatas()
{
    m_pUploadedRstTb->delAllRec();
    m_pNotUploadRstTb->delAllRec();
    m_pUploadFailRstTb->delAllRec();
    m_pAlarmTb->delAllRec();
    m_pLogTb->delAllRec();
    m_pUsrLogTb->delAllRec();
    m_pParamTb->delAllRec();
}

void DataStorage::delUploadedRst( const RecRst & rst)
{
    Q_ASSERT( m_pUploadedRstTb );

    if ( !m_pUploadedRstTb->delRec( rst ) )
    {

    }
}

void DataStorage::delUploadFailRst( const RecRst & rst)
{
    Q_ASSERT( m_pUploadFailRstTb );

    if ( !m_pUploadFailRstTb->delRec( rst ) )
    {

    }
}

void DataStorage::delNotUploadRst( const RecRst & rst)
{
    Q_ASSERT( m_pNotUploadRstTb );

    if ( !m_pNotUploadRstTb->delRec( rst ) )
    {

    }
}

void DataStorage::delData( const AlarmRec &alm )
{
    Q_ASSERT( m_pAlarmTb );

    if ( !m_pAlarmTb->delRec( alm ) )
    {

    }
}

void DataStorage::delParam( const ParamRec &par )
{
    Q_ASSERT( m_pParamTb );

    if ( !m_pParamTb->delRec( par ) )
    {

    }
}

void DataStorage::delUsrLog(const LogRec &log)
{
    Q_ASSERT( m_pUsrLogTb );

    if ( !m_pUsrLogTb->delRec( log ) )
    {

    }
}

void DataStorage::delLog(const LogRec &log)
{
    Q_ASSERT( m_pLogTb );

    if ( !m_pLogTb->delRec( log ) )
    {

    }
}

//// 查询对应数据库表格记录的接口
QLinkedList< RecRst > *DataStorage::getUploadedRst( QDateTime dt1, QDateTime dt2 )
{
    Q_ASSERT( m_pUploadedRstTb );

    return m_pUploadedRstTb->queryRec( dt1, dt2 );
}

QLinkedList< RecRst > *DataStorage::getUploadingRst( QDateTime dt1, QDateTime dt2 )
{
    Q_ASSERT( m_pUploadFailRstTb );

    return m_pUploadFailRstTb->queryRec( dt1, dt2 );
}

QLinkedList< RecRst > *DataStorage::getNotUploadRst( QDateTime dt1, QDateTime dt2 )
{
    Q_ASSERT( m_pNotUploadRstTb );

    return m_pNotUploadRstTb->queryRec( dt1, dt2 );
}

QLinkedList< AlarmRec > *DataStorage::getAlarmData( QDateTime dt1, QDateTime dt2 )
{
    Q_ASSERT( m_pAlarmTb );

    return m_pAlarmTb->queryRec( dt1, dt2 );
}

QLinkedList< ParamRec > *DataStorage::getParam( QDateTime dt1, QDateTime dt2 )
{
    Q_ASSERT( m_pParamTb );

    return m_pParamTb->queryRec( dt1, dt2 );
}

QLinkedList< LogRec > *DataStorage::getLogData( QDateTime dt1, QDateTime dt2 )
{
    Q_ASSERT( m_pLogTb );

    return m_pLogTb->queryRec( dt1, dt2 );
}

QLinkedList< LogRec > *DataStorage::getUsrLogData( QDateTime dt1, QDateTime dt2 )
{
    Q_ASSERT( m_pUsrLogTb );

    return m_pUsrLogTb->queryRec( dt1, dt2 );
}
