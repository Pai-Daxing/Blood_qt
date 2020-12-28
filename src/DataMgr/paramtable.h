#ifndef PARAMTABLE_H
#define PARAMTABLE_H

#include <QLinkedList>
#include"dbtable.h"
#include <QDateTime>

struct ParamRec
{
    QDateTime time;
    quint16   cblood;
    quint16   cbloodsp;
    quint16   prespeed;
    quint16   collsp;
    quint16   anti;
    quint16   line;
};

class ParamTable : public DBTable
{
    Q_OBJECT

public:
   explicit ParamTable( QString strName );

    bool create();
    bool addRec( const ParamRec& rec );
    bool delRec( const ParamRec &par );
    bool delRec( QDateTime dt1, QDateTime dt2 );
    QLinkedList< ParamRec > * queryRec( QString id );
    QLinkedList< ParamRec > * queryRec( QDateTime dt1, QDateTime dt2 );
};
#endif // PARAMTABLE_H
