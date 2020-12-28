#ifndef SERIALAPP_H
#define SERIALAPP_H

#include <QObject>
#include "../Protocol/commands.h"

//#define VIRTUALCOM

class QSerialPort;
class COMProtocol;

typedef enum
{
    cmdAck_OK = 0,
    cmdAck_InvalidLen,
    cmdAck_IncorrectCRC,
    cmdAck_UnexpectedEnd,
    cmdAck_ReceiveBufferFull,
    cmdAck_TimeOut,
    cmdAck_Reject,
    cmdAck_NULL = 0xFF
}cmdAckType;

#define FRAME_TYPE_SECURED         (1)
#define FRAME_TYPE_SECURED_ACK     (2)
#define FRAME_TYPE_NONE_SECURED    (3)

struct stCmd{
    quint16 cmd;
    short   params[128];
    quint32 num;
};

#define BUF_LEN  (128)

#define DATA_LINK_FRAME_LEN  (128)

typedef struct
{
    quint8 type;
    quint8 loop;
    quint8 len;
    quint8 payload[DATA_LINK_FRAME_LEN];
    quint8 crc;
}TDataLinkFrame;

class SerialApp: public QObject
{
    Q_OBJECT

    friend class ExamProtocol;
public:
    virtual ~SerialApp();
    static SerialApp& getInstance(){static SerialApp a(0); return a;}

    bool init(const QString name, qint32 baudRate=115200);
    bool openCOM(const QString name, qint32 baudRate=115200);
    void closeCOM();


    bool send(CommandID cmd, const CmdParam *params=0, quint32 num=0);

    quint8 getVersion(int index);

//protected:
//    void run();

//    QThread workerThread;
//    quint8 getVersion(int index);



protected:
    void timerEvent(QTimerEvent *event);

public slots:
    void onUICmd(quint16 cmd, const short *params=0, quint32 num=0);
    bool hwSend(const quint8* buf, quint32 len);
private slots:
    void onReadyRead();
    void parseData(const quint8* data, int len);
signals:
    void setAlarmType(qint16 newType);
    void setCtrlSysStatus(qint16 newStatus);
    void setErrNo(qint16 errNo);
    //    void setParamRTData(qint32);
    void setDpm(qint16 newValue);                   //“压力监测值更新”信号
    void setPlasmaVlm(qint16 newValue);             //“血浆量更新”信号
    void setACDVlm(qint16 newValue);                //“抗凝剂量更新”信号
    void setNaClVlm(qint16 newValue);               //“盐水量更新”信号
    void setPresvVlm(qint16 newValue);              //“保养液量更新”信号
    void setBloodVlm(qint16 newValue);              //“全血量更新”信号
    void setRBCVlm(qint16 newValue);                //“悬红量更新”信号
    void setBPSpeed(qint16 newValue);               //“血泵流速更新”信号
    void setAPSpeed(qint16 newValue);               //“抗凝剂泵流速更新”信号
    void setPresvPSpeed(qint16 newValue);           //“保养液泵流速更新”信号
    void setCFSpeed(qint16 newValue);               //“离心机转速更新”信号
    void setLineDetector(qint16 newValue);          //“管路探测器更新”信号
    void setVersion(qint16 newValue);
    void setCollecttime(qint16 newValue);

    void setBlood(qint16 newValue);
    void setDraw_speed(qint16 newValue);
    void setCollect_speed(qint16 newValue);
    void setLinecoff(qint16 newValue);
    void setBpap_rate(qint16 newValue);
    void setPrs_speed(qint16 newValue);

    void setBPreal(qint16 newValue);
    void setNPreal(qint16 newValue);
    void setAPreal(qint16 newValue);

    void setBoolParam(qint32 newValue);             //开关量更新信号

    void COMdata(const quint8* , int);
    void COMStr(QString);
private:
    explicit SerialApp( QObject *parent );

    QSerialPort *m_pSerial;
    COMProtocol *m_pComProtocol;
    int m_DebugTiemrId;
    int m_cmdTimerId;

    QList<stCmd*> m_cmdList;
};

class COMProtocol:public QObject
{
    Q_OBJECT

    typedef enum _RX_STATE{
        _sWaitBegin,
        _sWaitType,
        _sWaitLoop,
        _sWaitLength,
        _sWaitData,
        _sWaitCheck,
        _sWaitEnd
    } RX_STATE;

    typedef struct{
        quint8 loop;
        quint32 time;
        bool bvalid;
    } FrameNode;

public:
    COMProtocol();
    qint32 parseCOMData(quint8 *chbuf, int len);

    bool isCmdFinished( quint8* ack);
    qint32 Protocol_Send(const quint8 * buf, quint8 len);
    qint32 Protocol_Send_Secure(const quint8 * buf, quint8 len, qint32 timeout);
protected:
    qint32 SendSecuredFrameAck(quint8 loop, quint8 ack);
    void timerEvent(QTimerEvent *event);
signals:
    void COMdata(const quint8* , int);
    void sendFromProtocol(const quint8* , quint8);
private:
    RX_STATE m_smRxState;
    quint8   m_usDataCnt;
    quint8   m_usRxWord;
    quint8   m_usChkSum;
    bool m_sbUnicodeData;
    TDataLinkFrame m_buf;
    QList<FrameNode*> m_bufTx;
    QList<TDataLinkFrame*> m_bufRecv;

    quint8   m_AckRslt;
};

#endif // SERIALAPP_H
