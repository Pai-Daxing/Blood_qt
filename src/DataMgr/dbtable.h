#ifndef DBTABLE_H
#define DBTABLE_H

#include <QObject>
#include <QDateTime>
#include <QtSql>

class DBTable:public QObject
{
     Q_OBJECT

public:
    DBTable(QString strName);
    virtual ~DBTable();

    QString getTableName();
    virtual bool delAllRec();

    virtual bool create() = 0;
    virtual bool delRec( QDateTime dt1, QDateTime dt2 ) = 0;

private:
    QString m_tblName;
};

#endif // DBTABLE_H
