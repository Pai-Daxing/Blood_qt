#ifndef DEBUGLOG_H__
#define DEBUGLOG_H__

#include <QDebug>
#include <QDateTime>
#include <QMutex>
#include <QFile>
#include <QTextStream>
#include <stdio.h>
#include <stdlib.h>


#define LOG_FILE ("./log.txt")

#if (QT_VERSION < 0X50000)
void outPutDebugLogFile(QtMsgType type, const char *msg);
#else
void outPutDebugLogFile(QtMsgType type, const QMessageLogContext &context, const QString &msg);
#endif




#endif /*DEBUGLOG_H__*/
