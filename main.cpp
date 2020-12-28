#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QTimer>
#include "src/Protocol/commands.h"
#include "src/SerialApp/serialapp.h"
#include "src/AlarmMgr/alarmmgr.h"
#include "src/ParamMgr/parammgr.h"
#include "src/DataMgr/datamgr.h"
#include "src/DataMgr/netdatamgr.h"
#include "src/AlarmMgr/soundlightmgr.h"
#include "src/Dev/button/btthread.h"
#include "src/Network/network.h"
#include "src/StatusMgr/statusmgr.h"
#include "src/UI/uiadaptor.h"
#include "src/wiringPi/wiringPi.h"
#include "src/DataMgr/sqlquerymodel.h"
#include "src/Dev/Time/time.h"
#include "src/IDserial/serialtest.h"
#include <QQmlContext>

// 生成日志文件
//#define DUBUG_LOG_FILE
#ifdef DUBUG_LOG_FILE
#include "./DataMgr/debuglog.h"
#endif

bool modelInitilize();
bool bUpgrade = false;
QString gCOM_Name;

int main(int argc, char *argv[])
{
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    qmlRegisterType<UiAdaptor>("UiAdaptor", 1,0, "UiAdaptor");//第一个参数* uri指的是QML中import后的内容，相当于头文件名，
    //第二个第三个参数分别是主次版本号，第四个指的是QML中类的名字。
//    qmlRegisterType<SqlQueryModel>("SqlQueryModel", 1,0, "SqlQueryModel");
    qmlRegisterType<BtThread>("BtThread", 1,0, "BtThread");
    qmlRegisterType<SerialTest>("SerialTest", 1,0, "SerialTest");
    qmlRegisterType<Network>("Network", 1,0, "Network");

    modelInitilize();

    QQmlApplicationEngine engine;
    engine.load(QUrl(QString("qrc:/src/qmls/%2").arg(MAIN_QML)));
    engine.rootContext()->setContextProperty("sqlquery", new SqlQueryModel(&engine));

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}

bool modelInitilize()
{
    bool ret = false;
    SoundLightMgr::getInst().init();

    DataStorage::getInstance().init(); //需要放在DataMgr初始化前
    DataMgr::getInst().init();             //一定要在ParamMgr:init前进行
    Network::getInstance().init();

#ifdef Q_WS_WIN32
    gCOM_Name = Cfg::getInst().getUsrCfgStr(CFG_COM_WIN32);
    if (gCOM_Name == "") gCOM_Name = "COM22";
#else
    gCOM_Name = Cfg::getInst().getUsrCfgStr(CFG_COM_LINUX);
    if (gCOM_Name == "") gCOM_Name = "/dev/ttyAMA0";
#endif

    ret = SerialApp::getInstance().init(gCOM_Name);
    if (ret)
    {
        QObject* sender = &SerialApp::getInstance();
        StatusMgr::getInstance().init(sender);
        AlarmMgr::getInstance().init(sender);
        ParamMgr::getInstance()->init(sender);
        qDebug("chenggong");

    }
    else
    {
        qDebug("shibai");

    }

#ifndef  Q_WS_WIN32
    wiringPiSetup();
    pinMode(7,OUTPUT);
    pinMode(0,OUTPUT);
    pinMode(3,OUTPUT);
    digitalWrite(0,HIGH);
    delay(1000);
    digitalWrite(0,LOW);

    delay(1000);
    digitalWrite(3,HIGH);
    delay(1000);
    digitalWrite(3,LOW);

    delay(1000);
    digitalWrite(7,HIGH);
    delay(1000);
    digitalWrite(7,LOW);

    delay(1000);
    digitalWrite(7,HIGH);
#endif

    return ret;
}
