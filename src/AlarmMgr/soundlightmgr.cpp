#include "soundlightmgr.h"
#include "../StatusMgr/statusmgr.h"
#include <QTimerEvent>
#ifndef Q_WS_WIN32
#include "../Dev/Sound/soundthread.h"
#include<sys/fcntl.h>
#include<linux/input.h>
#include </home/slrom/qtworks/led/wiringPi/wiringPi.h>
#endif

SoundLightMgr::SoundLightMgr(QObject *parent) :
    QObject(parent),
    m_bStart(false),
    m_nTimerId(0),
    m_fdLt(-1),   //fd描述符
    m_nLtItvl(0),
    m_nLtNo(0),
    m_hSnd(0),
    m_bSilence(false),
    m_nSndItvl(0)
{
    m_sndRes["startup"] = QString("./Datas/Snd/start.mp3");
    m_sndRes["alarm_high"] = QString("./Datas/Snd/alarm_high.wav");
    m_sndRes["alarm_low"] = QString("./Datas/Snd/alarm_low.wav");
}

SoundLightMgr::~SoundLightMgr()
{
    if (m_nTimerId)
    {
        killTimer(m_nTimerId);
        m_nTimerId = 0;
    }
    if (m_hSnd)
    {
        delete m_hSnd;
        m_hSnd = 0;
    }
}

SoundLightMgr& SoundLightMgr::getInst()
{
    static SoundLightMgr inst;
    return inst;
}

bool SoundLightMgr::init()
{
    Q_ASSERT_X(!m_hSnd, "SoundLightMgr::init", "SoundLightMgr duplicate init");  //断言

    bool ret = true;

    m_nTimerId = startTimer(250);

#ifndef Q_WS_WIN32
    //light

    //sound
    m_hSnd = new SoundThread();
    if (m_hSnd)
    {
        m_hSnd->start();
    }
    else
    {
        Q_ASSERT_X(0, "SoundLightMgr::init", "init  SoundThread error");  //断言
        ret = false;
    }

    //connect(this, SIGNAL(play(QString)), m_hSnd, SLOT(onPlay(QString)), Qt::QueuedConnection);
#endif
    qRegisterMetaType<AlarmInfo>( );
    connect(&AlarmMgr::getInstance(), SIGNAL(triggerAlarm(AlarmInfo)), this, SLOT(onAlarmStart(AlarmInfo)), Qt::QueuedConnection);
    connect(&StatusMgr::getInstance(), SIGNAL(leaveAlarmPause()), this, SLOT(onAlarmEnd()), Qt::QueuedConnection);
    connect(&StatusMgr::getInstance(), SIGNAL(colctEnd()), this, SLOT(onCollectOver()), Qt::QueuedConnection);

    playSnd(m_sndRes.value("startup"));

    return ret;
}

void SoundLightMgr::onCollectOver()
{
    lightOff(m_nLtNo);
    onStop();

    m_nLtNo    = LT_GREEN;
    m_nLtItvl  = 0;
    m_nSndItvl = 0;
    m_strSnd   = ":/Snd/end.wav";

    if (!m_bStart)
    {
        m_bStart = true;
    }
    else
    {
        Q_ASSERT_X(0, "SoundLightMgr::onCollectOver", "Sound and Light start error");
    }
}

void SoundLightMgr::onAlarmStart(const AlarmInfo& info)
{
    m_bSilence = false;
    lightOff(m_nLtNo);
    digitalWrite(7,LOW);
    onStop();

    pinMode(0,OUTPUT);
    pinMode(3,OUTPUT);
    pinMode(7,OUTPUT);

    switch (info.latch)
    {
    case ALARM_AUTOB:
        m_nLtNo    = LT_Blue;
        m_nLtItvl  = 1;
        m_nSndItvl = 56;
        m_strSnd   = m_sndRes.value("alarm_low");
        break;
    case ALARM_LATCH:
        m_nLtNo    = LT_RED;
        m_nLtItvl  = 1;
        m_nSndItvl = 68;
        m_strSnd   = m_sndRes.value("alarm_high");
        break;
    case ALARM_BUTTON:
        m_nLtNo    = LT_RED;
        m_nLtItvl  = 0;
        break;
    default:
        //        Q_ASSERT_X(0, "SoundLightMgr::onAlarmStart", "wrong alarm level");
        break;
    }

    if (!m_bStart)
    {
        m_bStart = true;
    }
    else
    {
        Q_ASSERT_X(0, "SoundLightMgr::onAlarmStart", "Sound and Light start error");
    }
}

void SoundLightMgr::onAlarmEnd()
{
    //  在采集结束时，不需要处理报警结束而关闭声音和灯光
    if ( CSS_collect_over == StatusMgr::getInstance().getControlSystemStatus() )
        return;

    onStop();
}

static int  count     = 0;
static bool bLtOn     = false;
static bool bPlayed   = false;
void SoundLightMgr::onStop()
{
    //停止报警灯
    if (m_bStart)
    {
        m_bStart = false;
        lightOff(m_nLtNo);

        count = 0;
        bLtOn = false;
        bPlayed = false;
    }
    else
    {
        //Q_ASSERT_X(0, "SoundLightMgr::stop", "Sound and Light stop error");
    }
    //报警音
    m_bSilence = false;

    qDebug("llllalallaalall");
}

void  SoundLightMgr::OnPlayTip( bool bPlay )
{
    if ( bPlay )
    {
        if ( !m_bStart )
        {
            m_bStart = true;
            m_nLtNo     = LT_GREEN;
            m_nLtItvl    = 0;
            m_nSndItvl  = 20;
            m_strSnd     = ":/Snd/tip.wav";
        }
    }
    else
    {
        onStop();
    }
}

void SoundLightMgr::timerEvent(QTimerEvent */*event*/)
{
    if (!m_bStart)
    {
        count = 0;
        bLtOn = false;
        bPlayed = false;
        return;
    }

    if (m_nLtItvl > 0)
    {
        if (0 == count%m_nLtItvl)
        {
            if (bLtOn)
            {
                bLtOn = false;
                lightOff(m_nLtNo);
            }
            else
            {
                bLtOn = true;
                lightOn(m_nLtNo);
            }
        }
    }
    else
    {
        if (!bLtOn)
        {
            bLtOn = true;
            lightOn(m_nLtNo);
        }
    }

    if (m_nSndItvl > 0)
    {
        if ((0 == count%m_nSndItvl) && !m_bSilence)
        {
            playSnd(m_strSnd);
        }
    }
    else
    {
        if (!bPlayed)
        {
            bPlayed = true;
            playSnd(m_strSnd);
        }
    }

    count++;
}

void SoundLightMgr::lightOn(int no)
{
#ifndef Q_WS_WIN32
//    digitalWrite(7,LOW);
    digitalWrite(no,HIGH);
#else
    qDebug("light on");
#endif
}

void SoundLightMgr::lightOff(int no)
{
#ifndef Q_WS_WIN32
//    digitalWrite(7,HIGH);
    digitalWrite(no,LOW);
#else
    qDebug("light off");
#endif
}

void SoundLightMgr::playSnd(QString name)
{
#ifndef Q_WS_WIN32
    if (m_hSnd)
    {
        m_hSnd->playSnd(name);
    }
#endif
    qDebug("play sound");

}
