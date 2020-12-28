#include "soundthread.h"
#include <QDebug>
#include <QTimer>

SoundThread::SoundThread(QObject *parent) :
    QThread(parent),
    m_bPlayAlarm(false),
    m_name("")
{
    m_pPlayProc = new QProcess();
    m_pPlayProc->moveToThread( this );
}

SoundThread::~SoundThread()
{
}

void SoundThread::playSnd(QString name)
{
    m_bPlayAlarm = true;
    m_name = name;
}

void SoundThread::onPlay(QString name)
{
    m_bPlayAlarm = true;
    m_name = name;
}

void SoundThread::run()
{
    while(1)
    {
        if ( m_bPlayAlarm )
        {
            m_pPlayProc->start( "omxplayer " + m_name );
            m_bPlayAlarm = false;


            //            if ( m_pPlayProc->waitForFinished( MAX_SOUND_TIME ) )
            //            {
            //                qDebug() << "play sound not finish and start again!";
            //            }
        }
        else if ( m_pPlayProc->waitForFinished( MAX_SOUND_TIME ) )
        {
            qDebug() << "play sound not finish and start again!";
        }

        msleep(200);
    }
}
