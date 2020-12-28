#ifndef SoundLightMgr_H
#define SoundLightMgr_H

#include <QObject>
#include <QHash>
#include "alarmmgr.h"

class SoundThread;

#ifdef Q_WS_QWS
#define QWS_ARM     //ARM平台编译宏。x86平台请注释掉
#endif

class SoundLightMgr : public QObject
{
    Q_OBJECT
public:
    enum
    {
        LT_RED   = 0,
        LT_Blue      = 3,
        LT_GREEN  =7,
    };

    static SoundLightMgr& getInst();
    virtual ~SoundLightMgr();
    bool  init();
    void  setSilence(bool bSilence) {m_bSilence = bSilence;};
    bool  getSilence()const {return m_bSilence;};
    explicit SoundLightMgr(QObject *parent = 0);
    Q_INVOKABLE void onStop();


    void  selftest();
//    void inittime();
//    void time();

signals:
    void play(QString name);

public slots:


    void  onAlarmStart(const AlarmInfo& info);
    void  onAlarmEnd();
//    void  onStop();
    void  onCollectOver();
    void  OnPlayTip( bool bPlay );   // 播放提示信息     李立策  20150508

protected:
    void  timerEvent( QTimerEvent *event );
private:
//    explicit SoundLightMgr(QObject *parent = 0);

    void  lightOn(int no);
    void  lightOff(int no);
    void  playSnd(QString name);


private:
    bool   m_bStart;
    qint16 m_nTimerId;

    int    m_fdLt;
    int    m_nLtItvl;
    int    m_nLtNo;

    SoundThread* m_hSnd;
    bool         m_bSilence;
    int          m_nSndItvl;
    QString      m_strSnd;

    QHash<QString, QString> m_sndRes;
};

#endif // SoundLightMgr_H
