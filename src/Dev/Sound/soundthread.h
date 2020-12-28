#ifndef SOUNDTHREAD_H
#define SOUNDTHREAD_H

#include <QProcess>
#include <QThread>

// 播放声音的最长时间定为8s
#define  MAX_SOUND_TIME  8000

class SoundThread : public QThread
{
    Q_OBJECT
public:
    explicit SoundThread(QObject *parent = 0);
    virtual  ~SoundThread();

    void playSnd(QString name);

signals:

public slots:
    void onPlay(QString str);
protected:
    virtual void run();
private:
    bool        m_bPlayAlarm;
    QString     m_name;
    QProcess   *m_pPlayProc;
};

#endif // SOUNDTHREAD_H
