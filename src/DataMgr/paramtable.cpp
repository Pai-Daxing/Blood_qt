/***********************************************************************
* alarmtable.cpp
* Copyright all resever(2015)
*
* 参数设置记录数据库表类
*
* Author              Date               Action
* tangzhengqi         2019/5/12          create
*
***********************************************************************/
#include "src/global.h"
#include "paramtable.h"

ParamTable::ParamTable( QString strName ):
    DBTable( strName )
{

}

bool ParamTable::create()
{
    QSqlQuery query;

    query.exec("select * from " + getTableName());
    if ( query.lastError().isValid() && QSqlError::StatementError == query.lastError().type() )
    {
        query.exec("create table " +getTableName()+"( time  QDateTime, "
                   "cblood int, cbloodsp int, prespeed int, collsp int, anti int, line int)");
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

bool ParamTable::addRec( const ParamRec& rec )
{
    QSqlQuery query;

    query.prepare("INSERT INTO  "+ getTableName() +"(time, cblood, cbloodsp, prespeed, collsp, anti, line) "
                  "VALUES (:time, :cblood, :cbloodsp, :prespeed, :collsp, :anti, :line)");

    query.bindValue(0, rec.time.toString("yyyy-MM-dd hh:mm") );
    query.bindValue(1, rec.cblood);
    query.bindValue(2, rec.cbloodsp);
    query.bindValue(3, rec.prespeed);
    query.bindValue(4, rec.collsp);
    query.bindValue(5, rec.anti);
    query.bindValue(6, rec.line);

    query.exec();

    return !(query.lastError().isValid());
}

bool ParamTable::delRec( const ParamRec &par )
{
    QSqlQuery query;

    query.prepare( QString("DELETE from "+ getTableName() +
                           " where time = '%1' and cblood = '%2' ").arg( par.time.toString("yyyy-MM-dd hh:mm") ).arg(par.cblood) );
    query.exec();

    return !(query.lastError().isValid());
}

bool ParamTable::delRec( QDateTime dt1, QDateTime dt2 )
{
    QSqlQuery query;

    query.prepare( QString("DELETE from "+ getTableName() +" where time between '%1' and '%2' ")
                           .arg(dt1.toString("yyyy-MM-dd hh:mm")).arg(dt2.toString("yyyy-MM-dd hh:mm")) );
    query.exec();

    return !(query.lastError().isValid());
}

QLinkedList< ParamRec > * ParamTable::queryRec( QString id )
{
    QLinkedList< ParamRec > *ret = new QLinkedList< ParamRec >;
    QSqlQuery query;

    query.exec( QString(" SELECT * from " + getTableName() + " where mID = '%1' ").arg(id) );

    while (query.next())
    {
        ParamRec par;
        par.time = QDateTime::fromString(query.value(0).toString(), "yyyy-MM-dd hh:mm");
        par.cblood = query.value(1).toInt();
        par.cbloodsp = query.value(2).toInt();
        par.prespeed = query.value(3).toInt();
        par.collsp = query.value(4).toInt();
        par.anti = query.value(5).toInt();
        par.line = query.value(6).toInt();

        *ret << par;
    }

    return ret;
}

QLinkedList< ParamRec > * ParamTable::queryRec( QDateTime dt1, QDateTime dt2 )
{
    QLinkedList< ParamRec > *ret = new QLinkedList< ParamRec >;
    QSqlQuery query;

    query.exec( QString(" SELECT * from " + getTableName() + " where time between '%1' and '%2' ")
                .arg(dt1.toString("yyyy-MM-dd hh:mm")).arg(dt2.toString("yyyy-MM-dd hh:mm")) );

    while (query.next())
    {
        ParamRec par;
        par.time = QDateTime::fromString(query.value(0).toString(), "yyyy-MM-dd hh:mm");
        par.cblood = query.value(1).toInt();
        par.cbloodsp = query.value(2).toInt();
        par.prespeed = query.value(3).toInt();
        par.collsp = query.value(4).toInt();
        par.anti = query.value(5).toInt();
        par.line = query.value(6).toInt();

        *ret << par;
    }

    return ret;
}
