/***********************************************************************
* logtable.cpp
* Copyright all resever(2015)
*
* 日志记录数据库表类
*
* Author              Date               Action
* lilice              2015/11/17           create
*
***********************************************************************/
#include "../global.h"
#include "logtable.h"

LogTable::LogTable( QString strName ) :
    DBTable(  strName )
{
}

bool LogTable::create()
{
    QSqlQuery query;
    query.exec("select * from "  + getTableName());
    if ( query.lastError().isValid() && QSqlError::StatementError == query.lastError().type() )
    {
        query.exec("create table " +getTableName()+"( time  QDateTime, "
                   "mID varchar, logStr varchar)");
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

bool LogTable::addRec( const LogRec& rec )
{
    QSqlQuery query;
    query.prepare("INSERT INTO " +getTableName()+"(time, mID, logStr) "
                  "VALUES (:time, :mID, :logStr)");

    query.bindValue(0, rec.time.toString("yyyy-MM-dd hh:mm"));
    query.bindValue(1, rec.mid);
    query.bindValue(2, rec.str);

    query.exec();

    return !(query.lastError().isValid());
}

bool LogTable::delRec( const LogRec& rec )
{
    QSqlQuery query;

    query.prepare( QString("DELETE from "+ getTableName() +" where time = '%1' and logStr = '%2' ").arg( rec.time.toString("yyyy-MM-dd hh:mm") ).arg(rec.str) );
    query.exec();

    return !(query.lastError().isValid());
}

bool LogTable::delRec( QDateTime dt1, QDateTime dt2 )
{
    QSqlQuery query;

    query.prepare( QString("DELETE from "+ getTableName() +" where time between '%1' and '%2' ")
                           .arg(dt1.toString("yyyy-MM-dd hh:mm")).arg(dt2.toString("yyyy-MM-dd hh:mm")) );
    query.exec();

    return !(query.lastError().isValid());
}

QLinkedList< LogRec > * LogTable::queryRec( QString id )
{
    QLinkedList< LogRec > *ret = new QLinkedList< LogRec >;
    QSqlQuery query;

    query.exec( QString(" SELECT * from " + getTableName() + " where mID = '%1' ").arg(id) );

    while (query.next())
    {
        LogRec log;
        log.time   = QDateTime::fromString(query.value(0).toString(), "yyyy-MM-dd hh:mm");
        log.mid = query.value(1).toString();
        log.str = query.value(2).toString();

        *ret << log;
    }

    return ret;
}

QLinkedList< LogRec > * LogTable::queryRec( QDateTime dt1, QDateTime dt2 )
{
    QLinkedList< LogRec > *ret = new QLinkedList< LogRec >;
    QSqlQuery query;

    query.exec( QString(" SELECT * from " + getTableName() + " where time between '%1' and '%2' ")
                .arg(dt1.toString("yyyy-MM-dd hh:mm")).arg(dt2.toString("yyyy-MM-dd hh:mm")) );

    while (query.next())
    {
        LogRec log;
        log.time   = QDateTime::fromString(query.value(0).toString(), "yyyy-MM-dd hh:mm");
        log.mid = query.value(1).toString();
        log.str = query.value(2).toString();

        *ret << log;
    }

    return ret;
}
