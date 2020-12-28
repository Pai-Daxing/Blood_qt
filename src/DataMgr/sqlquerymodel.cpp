#include <QSqlError>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QUuid>
#include <QDebug>
#include "sqlquerymodel.h"
#include "cfg.h"
#include "datastorage.h"
#include <QSqlRecord>
#include <QSqlField>
#include <QTimer>

SqlQueryModel::SqlQueryModel(QObject *parent)
    : QSqlQueryModel(parent)
{

}

SqlQueryModel::~SqlQueryModel()
{
}

QHash<int, QByteArray> SqlQueryModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    QSqlRecord record = this->record();
    for (int i = 0; i < record.count(); ++i)
    {
        roles.insert(Qt::UserRole + 1 + i, record.fieldName(i).toUtf8());
    }

    return roles;
}

QVariant SqlQueryModel::data(const QModelIndex &index, int role) const
{
    QVariant value = QSqlQueryModel::data(index, role);

    if(role < Qt::UserRole)
    {
        value = QSqlQueryModel::data(index, role);
    }
    else
    {
        int column = role - Qt::UserRole - 1;
        QModelIndex modelIndex = this->index(index.row(), column);
        value = QSqlQueryModel::data(modelIndex, Qt::DisplayRole);
    }

    return value;
}

void SqlQueryModel::refresh()
{
    this->query().clear();
//    QString sqlSelect = QString("SELECT * FROM %1").arg(m_userTable);
    this->setQuery("SELECT * FROM " + DataStorage::getInstance().getTableName( UPLOADEDRST_TB ));
    qDebug()<<">>>>>>>>>>>>>>>>>>>>>>";
}


//#include "sqlquerymodel.h"
//#include "cfg.h"
//#include "datastorage.h"
//#include <QSqlRecord>
//#include <QSqlField>
//#include <QDebug>

//SqlQueryModel::SqlQueryModel(QObject *parent) :
//    QSqlQueryModel(parent)
//{
//    setQuery( "SELECT * FROM "+
//                           DataStorage::getInstance().getTableName( UPLOADEDRST_TB ));

//}

//void SqlQueryModel::setQuery(const QString &query, const QSqlDatabase &db)
//{
//    QSqlQueryModel::setQuery(query, db);
//    generateRoleNames();
//}

//void SqlQueryModel::setQuery(const QSqlQuery & query)
//{
//    QSqlQueryModel::setQuery(query);
//    generateRoleNames();
//}

//void SqlQueryModel::generateRoleNames()
//{
//    m_roleNames.clear();
//    for( int i = 0; i < record().count(); i ++) {
//        m_roleNames.insert(Qt::UserRole + i + 1, record().fieldName(i).toUtf8());
//    }
//}


//void SqlQueryModel::refresh()
//{
//    setQuery( "SELECT * FROM  "+ DataStorage::getInstance().getTableName( UPLOADEDRST_TB ));
//    qDebug("==============================");
//}

//QVariant SqlQueryModel::data(const QModelIndex &index, int role) const
//{
//    QVariant value;

//    if(role < Qt::UserRole) {
//        value = QSqlQueryModel::data(index, role);
//    }
//    else {
//        int columnIdx = role - Qt::UserRole - 1;
//        QModelIndex modelIndex = this->index(index.row(), columnIdx);
//        value = QSqlQueryModel::data(modelIndex, Qt::DisplayRole);
//    }
//    return value;
//}

