#include "debuglog.h"

/*************************************************************************
 * Function     : outPutDebugLogFile
 * Description  : 信息输出到日志文件
 * Calls        : 无
 * Input        : type 输出的信息类型，0~3 (debug,warning,critical,fatal)
 *                msg  输出的信息内容
 * Output       : 无
 * Return       : void
 * Others       : 无
 ************************************************************************/
#if (QT_VERSION < 0X50000)
void outPutDebugLogFile(QtMsgType type, const char *msg)
#else
void outPutDebugLogFile(QtMsgType type, const QMessageLogContext &context, const QString &msg)
#endif
{
    static QMutex mutex;

    QString level;
    switch(type)
    {
    case QtDebugMsg:
    {
        level = QString("Debug   :");
        break;
    }

    case QtWarningMsg:
    {
        level = QString("Warning :");
        break;
    }

    case QtCriticalMsg:
    {
        level = QString("Critical:");
        break;
    }

    case QtFatalMsg:
    {
        level = QString("Fatal   :");
        break;
    }

    default:
    {
        level = QString();
        break;
    }
    }

    QString current_time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz");

#if (QT_VERSION < 0X50000)
    QString message = QString("[%1] %2 %3").arg(current_time).arg(level).arg(msg);
#else
    QString message = QString("[%1] %2 %3 %4")
            .arg(current_time)
            .arg(level)
            .arg(QString("[FILE: %1; LINE: %2]").arg(context.file).arg(context.line))
            .arg(msg);
#endif

    mutex.lock();

    QFile file(LOG_FILE);
    file.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream out(&file);
    out << message << "\r\n";
    file.flush();
    file.close();

    mutex.unlock();
}
