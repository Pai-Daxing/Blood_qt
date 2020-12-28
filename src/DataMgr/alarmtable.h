#ifndef ALARMTABLE_H
#define ALARMTABLE_H

#include <QLinkedList>
#include"dbtable.h"
#include <QDateTime>

struct AlarmRec
{
    QDateTime time;
    QString   mid;
    QString   str;
    quint16   action;
};

class AlarmTable : public DBTable
{
    Q_OBJECT

public:
   explicit AlarmTable( QString strName );

    bool create();
    bool addRec( const AlarmRec& rec );
    bool delRec( const AlarmRec &alm );
    bool delRec( QDateTime dt1, QDateTime dt2 );
    QLinkedList< AlarmRec > * queryRec( QString id );
    QLinkedList< AlarmRec > * queryRec( QDateTime dt1, QDateTime dt2 );
};

#endif // ALARMTABLE_H
