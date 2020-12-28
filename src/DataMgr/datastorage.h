#ifndef DATASTORAGE_H
#define DATASTORAGE_H

#include <QObject>
#include <QThread>
#include <QDateTime>
#include "logtable.h"
#include "alarmtable.h"
#include "resulttable.h"
#include "paramtable.h"


enum TABLETYPE
{
    UPLOADEDRST_TB,
    UPLOADFAILRST_TB,
    NOTUPLOADRST_TB,
    ALM_TB,
    LOG_TB,
    USR_LOG_TB,
    PAR_TB,
    MAX_TB
};

class DataStorage :public QObject
{
    Q_OBJECT

public:
    static DataStorage& getInstance(){static DataStorage ds; return ds;}
    bool init();

    //// 保存到数据库对应表格的接口
    void saveUploadedRst( const RecRst & rst);
    void saveUploadFailRst( const RecRst & rst);
    void saveNotUploadRst( const RecRst & rst);
    void saveUsrLog( QString str );
    void saveUsrLog( const LogRec &log );
    void saveData(const AlarmRec &alm);
    void saveParam(const ParamRec &par);
    void saveLog( QString str );
    void saveLog(const LogRec &log);

    //// 删除对应数据库表格记录的接口
    void delUploadedRst( const RecRst & rst);
    void delUploadFailRst( const RecRst & rst);
    void delNotUploadRst( const RecRst & rst);
    void delData( const AlarmRec &alm );
    void delParam( const ParamRec &par );
    void delLog( const LogRec &log );
    void delUsrLog( const LogRec &log );

    void delAllDatas();

    //// 查询对应数据库表格记录的接口
    QLinkedList< RecRst > *getUploadedRst( QDateTime dt1, QDateTime dt2 );
    QLinkedList< RecRst > *getUploadingRst( QDateTime dt1, QDateTime dt2 );
    QLinkedList< RecRst > *getNotUploadRst( QDateTime dt1, QDateTime dt2 );
    QLinkedList< AlarmRec > *getAlarmData( QDateTime dt1, QDateTime dt2 );
    QLinkedList< ParamRec > *getParam( QDateTime dt1, QDateTime dt2 );
    QLinkedList< LogRec > *getLogData( QDateTime dt1, QDateTime dt2 );
    QLinkedList< LogRec > *getUsrLogData( QDateTime dt1, QDateTime dt2 );

    QString getTableName( TABLETYPE type );
signals:
    
public slots:

private:
    explicit DataStorage(QObject *parent = 0);
    bool initDbTable();   //初始化数据库表格

private:
   ResultTable *m_pUploadedRstTb;
   ResultTable *m_pNotUploadRstTb;
   ResultTable *m_pUploadFailRstTb;
   AlarmTable  *m_pAlarmTb;
   LogTable     *m_pLogTb;
   LogTable     *m_pUsrLogTb;
   ParamTable   *m_pParamTb;
};

#endif // DATASTORAGE_H
