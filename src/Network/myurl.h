#ifndef MYURL_H
#define MYURL_H

#include <QObject>
#include "networkinterface.h"

class MyUrl : public QObject
{
    Q_OBJECT
public:
    explicit MyUrl(QObject *parent = 0);
    virtual QString getUrl( ID_NET id ) = 0;
signals:
    
public slots:
    
};

#endif // MYURL_H
