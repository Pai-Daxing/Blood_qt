/***********************************************************************
* dbtable.cpp
* Copyright all resever(2015)
*
* 数据库表类虚类
*
* Author              Date               Action
* lilice              2015/11/17           create
*
***********************************************************************/
#include "dbtable.h"

DBTable::DBTable(QString strName)
    :m_tblName( strName )
{

}

DBTable::~DBTable()
{

}

QString DBTable::getTableName()
{
    return m_tblName;
}

bool DBTable::delAllRec()
{
    QSqlQuery query;

    query.prepare( QString("DELETE from "+ getTableName() ));
    query.exec();

    return !(query.lastError().isValid());
}
