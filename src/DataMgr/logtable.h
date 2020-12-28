#ifndef LOGTABLE_H
#define LOGTABLE_H

#include "dbtable.h"
#include <QLinkedList>
#include <QDateTime>

struct LogRec
{
    QDateTime time;
    QString   mid;
    QString   str;
};

class   LogTable : public DBTable
{
    Q_OBJECT
public:
    explicit LogTable( QString strName );
    
    bool create();
    bool addRec( const LogRec& rec );
    bool delRec( const LogRec& rec );
    bool delRec( QDateTime dt1, QDateTime dt2 );
    QLinkedList< LogRec > * queryRec( QString id );
    QLinkedList< LogRec > * queryRec( QDateTime dt1, QDateTime dt2 );
};

#endif // LOGTABLE_H
