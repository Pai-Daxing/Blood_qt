QT += qml quick \
                network\
                sql\
                widgets\
                serialport

CONFIG += c++11


SOURCES += main.cpp \
    src/AlarmMgr/alarmmgr.cpp \
    src/AlarmMgr/alarmstr.cpp \
    src/AlarmMgr/soundlightmgr.cpp \
    src/DataMgr/alarmtable.cpp \
    src/DataMgr/cfg.cpp \
    src/DataMgr/datamgr.cpp \
    src/DataMgr/datastorage.cpp \
    src/DataMgr/dbtable.cpp \
    src/DataMgr/debuglog.cpp \
    src/DataMgr/logtable.cpp \
    src/DataMgr/netdatamgr.cpp \
    src/DataMgr/resulttable.cpp \
    src/Network/langcheng/protocollang.cpp \
    src/Network/langcheng/urllang.cpp \
    src/Network/myurl.cpp \
    src/Network/netobj.cpp \
    src/Network/netreply.cpp \
    src/Network/network.cpp \
    src/Network/networkinterface.cpp \
    src/Network/protocolhelper.cpp \
    src/ParamMgr/parammgr.cpp \
#    src/Protocol/Src/Protocol.cpp \
#    src/Protocol/Src/ProtocolAPI.cpp \
#    src/Protocol/Src/RingFifo.cpp \
    src/SerialApp/serialapp.cpp \
    src/StatusMgr/statusmgr.cpp \
    src/UI/uiadaptor.cpp \
    src/DataMgr/sqlquerymodel.cpp \
    src/Wifi/wifi.cpp \
    src/DataMgr/paramtable.cpp \
    src/IDserial/serialtest.cpp \
    src/Dev/NetOnline/netonline.cpp

RESOURCES += \
    Blood.qrc

CONFIG +=resources_big

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

disable-xcb {
    message("The disable-xcb option has been deprecated. Please use disable-desktop instead.")
    CONFIG += disable-desktop
}

disable-desktop|android-embedded|!isEmpty(CROSS_COMPILE)|qnx {
    DEFINES += MAIN_QML=\\\"Main-b2qt.qml\\\"
} else {
    DEFINES += MAIN_QML=\\\"Main.qml\\\"
}

unix:{

             SOURCES += src/Dev/button/btthread.cpp \
                        src/Dev/Sound/soundthread.cpp \
                        src/Dev/Time/time.cpp
             HEADERS += src/Dev/button/btthread.h \
                        src/Dev/Sound/soundthread.h \
                        src/Dev/Time/time.h
             LIBS += -L/home/slrom/qtworks/led/wiringPi -lwiringPi -lcrypt
             target.path=/home/pi
}
else:{
    DEFINES += Q_WS_WIN32
}

HEADERS += \
    src/AlarmMgr/alarmmgr.h \
    src/AlarmMgr/alarmstr.h \
    src/AlarmMgr/soundlightmgr.h \
    src/DataMgr/alarmtable.h \
    src/DataMgr/cfg.h \
    src/DataMgr/datamgr.h \
    src/DataMgr/datastorage.h \
    src/DataMgr/dbtable.h \
    src/DataMgr/debuglog.h \
    src/DataMgr/logtable.h \
    src/DataMgr/netcfg.h \
    src/DataMgr/netdatamgr.h \
    src/DataMgr/resulttable.h \
    src/Network/network.h \
    src/Network/langcheng/protocollang.h \
    src/Network/langcheng/urllang.h \
    src/Network/myurl.h \
    src/Network/netobj.h \
    src/Network/netreply.h \
    src/Network/networkinterface.h \
    src/Network/protocolhelper.h \
    src/ParamMgr/parammgr.h \
#    src/Protocol/Src/Protocol.h \
#    src/Protocol/Src/RingFifo.h \
    src/Protocol/alarms.h \
    src/Protocol/commands.h \
#    src/Protocol/ProtocolAPI.h \
    src/Protocol/status.h \
    src/Protocol/types.h \
    src/SerialApp/serialapp.h \
    src/StatusMgr/statusmgr.h \
    src/UI/uiadaptor.h \
    src/DataMgr/sqlquerymodel.h \
    src/Protocol/ProtocolAPI.h \
    src/Wifi/wifi.h \
    src/DataMgr/paramtable.h \
    src/IDserial/serialtest.h \
    src/Dev/NetOnline/netonline.h

DISTFILES +=

FORMS +=


