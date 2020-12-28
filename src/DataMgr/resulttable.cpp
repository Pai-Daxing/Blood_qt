/***********************************************************************
* resulttable.cpp
* Copyright all resever(2015)
*
* 采集结果记录数据库表类
*
* Author              Date               Action
* lilice              2015/11/17           create
*
***********************************************************************/
#include "resulttable.h"
#include "../global.h"

ResultTable::ResultTable( QString strName  ):
    DBTable( strName )
{

}

bool ResultTable::create()
{
    QSqlQuery query;

    query.exec("select * from " + getTableName());

    if ( query.lastError().isValid() && QSqlError::StatementError == query.lastError().type() )
    {
        query.exec("create table " +getTableName()+"( bgtime  QDateTime, edtime_m  QDateTime, edtime_e  QDateTime, "
                   "dID varchar, mID varchar, nID varchar, nName varchar, "
                   "collectionvlm varchar, enrivlm varchar, timelen varchar) ");
                  // "timeLen_m int, timeLen_e int, dposlId varchar, naclId varchar, acId varchar, prsvId varchar, status varchar )");
    }
    else
    {
        // 每次开机清理一遍6个月前的记录
        QDateTime curDt = QDateTime::currentDateTime();
        query.exec( QString("DELETE from "+ getTableName() +" where edtime < '%1' ")
                               .arg(curDt.addMonths( -LOG_MONTH ).toString("yyyy-MM-dd hh:mm")) );
    }

     return !( query.lastError().isValid() );
}

bool ResultTable::addRec( const  RecRst& rst )
{
    QSqlQuery query;
    query.prepare("INSERT INTO " +getTableName()+"( bgtime, edtime_m, edtime_e, dID, mID, nID,  nName, collectionvlm, enrivlm, timelen )"
                  "VALUES (:bgtime, :edtime_m, :edtime_e, :dID, :mID, :nID, :nName, :collectionvlm, :enrivlm, :timelen )");

//    query.bindValue(":bgtime",    rst.bgtime.toString("yyyy-MM-dd hh:mm") );
//    query.bindValue(":edtime_m",  rst.edtime_m.toString("yyyy-MM-dd hh:mm") );
//    query.bindValue(":edtime_e",  rst.edtime_e.toString("yyyy-MM-dd hh:mm") );
//    query.bindValue(":dID",       rst.donorId);
//    query.bindValue(":mID",       rst.machineId);
//    query.bindValue(":nID",       rst.oprtrId);
//    query.bindValue(":nName",     rst.oprtrName);
//    query.bindValue(":bldVlm",    rst.bldVlm);
//    query.bindValue(":plsmVlm",   rst.plsmVlm);
//    query.bindValue(":acVlm",     rst.acdVlm);
//    query.bindValue(":naclVlm",   rst.naclVlm);
//    query.bindValue(":SRBCVlm",   rst.SRBCVlm);
//    query.bindValue(":prsvVlm",   rst.prsvVlm);
//    query.bindValue(":timeLen_m", rst.timeLen_m);
//    query.bindValue(":timeLen_e", rst.timeLen_e);
//    query.bindValue(":dposlId",   rst.dposlId);
//    query.bindValue(":naclId",    rst.naclId);
//    query.bindValue(":acId",      rst.acId);
//    query.bindValue(":prsvId",    rst.prsvId);
//    query.bindValue(":status",    rst.status);

    query.bindValue(0,    rst.bgtime.toString("yyyy-MM-dd hh:mm") );
    query.bindValue(1,  rst.edtime_m.toString("yyyy-MM-dd hh:mm") );
    query.bindValue(2,  rst.edtime_e.toString("yyyy-MM-dd hh:mm") );
    query.bindValue(3,       rst.donorId);
    query.bindValue(4,       rst.machineId);
    query.bindValue(5,       rst.oprtrId);
    query.bindValue(6,     rst.oprtrName);
    query.bindValue(7,    rst.collectionvlm);
    query.bindValue(8,   rst.enrivlm);
    query.bindValue(9,     rst.timelen);/*
    query.bindValue(10,   rst.naclVlm);
    query.bindValue(11,   rst.SRBCVlm);
    query.bindValue(12,   rst.prsvVlm);
    query.bindValue(13, rst.timeLen_m);
    query.bindValue(14, rst.timeLen_e);
    query.bindValue(15,   rst.dposlId);
    query.bindValue(16,    rst.naclId);
    query.bindValue(17,      rst.acId);
    query.bindValue(18,    rst.prsvId);
    query.bindValue(19,    rst.status);*/

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

bool ResultTable::delRec( const  RecRst& rst )
{
    QSqlQuery query;

    QString strCmd = QString("DELETE from "+ getTableName() +" where dID='%1' and edtime_e='%2' ")
            .arg( rst.donorId).arg( rst.edtime_e.toString("yyyy-MM-dd hh:mm") );
    query.prepare( strCmd );
    query.exec();

    qDebug() << query.lastError();
    return !(query.lastError().isValid());
}

bool ResultTable::delRec( QDateTime dt1, QDateTime dt2 )
{
    QSqlQuery query;

    query.prepare( QString("DELETE from "+ getTableName() +" where edtime between '%1' and '%2' ")
                           .arg(dt1.toString("yyyy-MM-dd hh:mm")).arg(dt2.toString("yyyy-MM-dd hh:mm")) );
    query.exec();

    return !(query.lastError().isValid());
}

QLinkedList< RecRst > * ResultTable::queryRec( QString id )
{
    QLinkedList< RecRst > *ret = new QLinkedList< RecRst >;
    QSqlQuery query;

    query.exec( QString("SELECT * from " + getTableName() + " where dID='%1'")
                .arg( id ) );

    int cnt = 0;

    while (query.next())
    {
        RecRst rst;
        rst.bgtime     = QDateTime::fromString(query.value(cnt++).toString(), "yyyy-MM-dd hh:mm");
        rst.edtime_m     = QDateTime::fromString(query.value(cnt++).toString(), "yyyy-MM-dd hh:mm");
        rst.edtime_e     = QDateTime::fromString(query.value(cnt++).toString(), "yyyy-MM-dd hh:mm");
        rst.donorId         = query.value(cnt++).toString();
        rst.machineId     = query.value(cnt++).toString();
        rst.oprtrId          = query.value(cnt++).toString();
        rst.oprtrName     = query.value(cnt++).toString();
        rst.collectionvlm        = query.value(cnt++).toString();
        rst.enrivlm       = query.value(cnt++).toString();
        rst.timelen         = query.value(cnt++).toInt();
//        rst.naclVlm         = query.value(cnt++).toInt();
//        rst.SRBCVlm         = query.value(cnt++).toInt();
//        rst.prsvVlm         = query.value(cnt++).toInt();

//        rst.timeLen_m       = query.value(cnt++).toInt();
//        rst.timeLen_e       = query.value(cnt++).toInt();
//        rst.dposlId        = query.value(cnt++).toString();
//        rst.naclId          = query.value(cnt++).toString();
//        rst.acId            = query.value(cnt++).toString();
//        rst.prsvId          = query.value(cnt++).toString();
//        rst.status          = query.value(cnt++).toString();

        *ret << rst;
        qDebug() << "suiprise!!! u got data from Database now";
    }

    return ret;
}

QLinkedList< RecRst > * ResultTable::queryRec( QDateTime dt1, QDateTime dt2 )
{
    QLinkedList< RecRst > *ret = new QLinkedList< RecRst >;
    QSqlQuery query;

    query.exec( QString("SELECT * from " + getTableName() + " where edtime between '%1' and '%2' ")
                .arg(dt1.toString("yyyy-MM-dd hh:mm")).arg(dt2.toString("yyyy-MM-dd hh:mm")) );

    qDebug() << QString("no data between %1 and %2 ?").arg( dt1.toString("yyyy-MM-dd hh:mm") )
                .arg(dt2.toString("yyyy-MM-dd hh:mm"));

    int cnt = 0;
    while (query.next())
    {
        RecRst rst;
        rst.bgtime     = QDateTime::fromString(query.value(cnt++).toString(), "yyyy-MM-dd hh:mm");
        rst.edtime_m     = QDateTime::fromString(query.value(cnt++).toString(), "yyyy-MM-dd hh:mm");
        rst.edtime_e     = QDateTime::fromString(query.value(cnt++).toString(), "yyyy-MM-dd hh:mm");
        rst.donorId         = query.value(cnt++).toString();
        rst.machineId     = query.value(cnt++).toString();
        rst.oprtrId          = query.value(cnt++).toString();
        rst.oprtrName     = query.value(cnt++).toString();
        rst.collectionvlm        = query.value(cnt++).toString();
        rst.enrivlm       = query.value(cnt++).toString();
        rst.timelen         = query.value(cnt++).toInt();
//        rst.naclVlm         = query.value(cnt++).toInt();
//        rst.SRBCVlm         = query.value(cnt++).toInt();
//        rst.prsvVlm         = query.value(cnt++).toInt();

//        rst.timeLen_m       = query.value(cnt++).toInt();
//        rst.timeLen_e       = query.value(cnt++).toInt();
//        rst.dposlId        = query.value(cnt++).toString();
//        rst.naclId          = query.value(cnt++).toString();
//        rst.acId            = query.value(cnt++).toString();
//        rst.prsvId          = query.value(cnt++).toInt();
//        rst.status          = query.value(cnt++).toString();

        *ret << rst;
        qDebug() << "suiprise!!! u got data from Database now";
    }

    return ret;
}
