/***********************************************************************
* alarmtable.cpp
* Copyright all resever(2015)
*
* 报警记录数据库表类
*
* Author              Date               Action
* lilice              2015/11/17           create
*
***********************************************************************/
#include "src/global.h"
#include "alarmtable.h"

AlarmTable::AlarmTable( QString strName ):
    DBTable( strName )
{

}

bool AlarmTable::create()
{
    QSqlQuery query;

    query.exec("select * from " + getTableName());
    if ( query.lastError().isValid() && QSqlError::StatementError == query.lastError().type() )
    {
        query.exec("create table " +getTableName()+"( time  QDateTime, "
                   "mID varchar, alarmStr varchar, action varchar)");
    }
    else
    {
        // 每次开机清理一遍6个月前的记录
        QDateTime curDt = QDateTime::currentDateTime();
        query.exec( QString("DELETE from "+ getTableName() +" where time < '%1' ")
                               .arg( curDt.addMonths( -LOG_MONTH ).toString("yyyy-MM-dd hh:mm") ) );
    }
    return !( query.lastError().isValid() );
}

bool AlarmTable::addRec( const AlarmRec& rec )
{
    QSqlQuery query;

    query.prepare("INSERT INTO  "+ getTableName() +"(time, mID, alarmStr, action) "
                  "VALUES (:time, :mID, :alarmStr, :action)");

    query.bindValue(0, rec.time.toString("yyyy-MM-dd hh:mm") );
    query.bindValue(1, rec.mid);
    query.bindValue(2, rec.str);
    query.bindValue(3, rec.action);

    query.exec();

    if ( query.lastError().isValid() )
    {
        qDebug()<< "write Db failed";
        qDebug() << query.lastError();
    }
    else
    {
        qDebug()<< "write Db done";
    }

    return !(query.lastError().isValid());
}

bool AlarmTable::delRec( const AlarmRec &alm )
{
    QSqlQuery query;

    query.prepare( QString("DELETE from "+ getTableName() +
                           " where time = '%1' and alarmStr = '%2' ").arg( alm.time.toString("yyyy-MM-dd hh:mm") ).arg(alm.str) );
    query.exec();

    return !(query.lastError().isValid());
}

bool AlarmTable::delRec( QDateTime dt1, QDateTime dt2 )
{
    QSqlQuery query;

    query.prepare( QString("DELETE from "+ getTableName() +" where time between '%1' and '%2' ")
                           .arg(dt1.toString("yyyy-MM-dd hh:mm")).arg(dt2.toString("yyyy-MM-dd hh:mm")) );
    query.exec();

    return !(query.lastError().isValid());
}

QLinkedList< AlarmRec > * AlarmTable::queryRec( QString id )
{
    QLinkedList< AlarmRec > *ret = new QLinkedList< AlarmRec >;
    QSqlQuery query;

    query.exec( QString(" SELECT * from " + getTableName() + " where mID = '%1' ").arg(id) );

    while (query.next())
    {
        AlarmRec alm;
        alm.time = QDateTime::fromString(query.value(0).toString(), "yyyy-MM-dd hh:mm");
        alm.mid = query.value(1).toString();
        alm.str  = query.value(2).toString();
        alm.action = query.value(3).toInt();

        *ret << alm;
    }

    return ret;
}

QLinkedList< AlarmRec > * AlarmTable::queryRec( QDateTime dt1, QDateTime dt2 )
{
    QLinkedList< AlarmRec > *ret = new QLinkedList< AlarmRec >;
    QSqlQuery query;

    query.exec( QString(" SELECT * from " + getTableName() + " where time between '%1' and '%2' ")
                .arg(dt1.toString("yyyy-MM-dd hh:mm")).arg(dt2.toString("yyyy-MM-dd hh:mm")) );

    while (query.next())
    {
        AlarmRec alm;
        alm.time = QDateTime::fromString(query.value(0).toString(), "yyyy-MM-dd hh:mm");
        alm.mid = query.value(1).toString();
        alm.str  = query.value(2).toString();
        alm.action = query.value(3).toInt();

        *ret << alm;
    }

    return ret;
}
