#ifndef URLLANG_H
#define URLLANG_H

#include  "../myurl.h"
class UrlLang : public MyUrl
{
public:
    UrlLang(QObject *parent = 0);

    QString getUrl( ID_NET id );

private:
    QMap<ID_NET, QString> httpIdList;
};

#endif // URLLANG_H
