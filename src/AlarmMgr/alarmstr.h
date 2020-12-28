#ifndef ALARMSTR_H
#define ALARMSTR_H

#include "../AlarmMgr/alarmmgr.h"

struct ALARMSTRING
{
    AlarmType type;
    QString str;
    QString details;
};

class AlarmString : public QObject
{
    Q_OBJECT

public:
    static AlarmString& getInstance()
    {
        static AlarmString as;
        return as;
    }

    QString getStr( AlarmType type )
    {
        if ( type < AlmType_MAX  )
            return m_str[type].str;
        else
            return "Error";
    }

    QString getDetail( AlarmType type )
    {
        if ( type < AlmType_MAX  )
            return m_str[type].details;
        else
            return "Error";
    }


private:
    explicit AlarmString(QObject *parent = 0);
    
    void resetStr();
protected:
//    void changeEvent(QEvent *e);
    
private:    
//    Ui::AlarmString ui;
    ALARMSTRING m_str[AlmType_MAX];
};

#endif // ALARMSTR_H
