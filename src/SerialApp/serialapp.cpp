#include "serialapp.h"
//#include "../Protocol/ProtocolAPI.h"
#include "../Protocol/types.h"
#include <QtSerialPort/QSerialPort>
#include <QDebug>
#include <QTimerEvent>

#ifdef VIRTUALCOM
#include <QFile>
#endif

static quint8 CharToAsciiHigh(quint8 c)
{
    quint8 r = (0xF0 & c) >> 4;
    if (r<10)
        return '0' + r;
    else
        return 'A' + r - 10;
}

static quint8 CharToAsciiLow(quint8 c)
{
    quint8 r = (0x0F & c);
    if (r<10)
        return '0' + r;
    else
        return 'A' + r - 10;
}

static quint8 AsciiToChar_Num(quint8 ch)
{

    if ((ch>='0')&&(ch<='9'))
    {
        return ch - '0';
    }
    else
    {
        return ch;
    }

}

static quint8 AsciiToChar(quint8 ch)
{
    if (((ch<'0') || (ch>'9')) &&
            ((ch<'A') || (ch>'Z')))
    {
        return ch;
    }
    if ((ch>='0')&&(ch<='9'))
    {
        return ch - '0';
    }
    else
    {
        return ch - 'A' + 10;
    }
}

static u16 CRC16Default( quint8 in, u16 CrcReg )
{
    quint8 j;
    u16 CurVal;

    CurVal = in << 8;

    for (j = 0; j < 8; j++)
    {
        if ((short)(CrcReg ^ CurVal) < 0)
            CrcReg = (CrcReg << 1) ^ 0x8005;
        else
            CrcReg <<= 1;
        CurVal <<= 1;
    }

    return CrcReg;
}
SerialApp::SerialApp(QObject *parent):
    QObject(parent)
{
    m_pSerial = new QSerialPort(this);
    m_pComProtocol = new COMProtocol();

    connect(m_pSerial, &QSerialPort::readyRead, this, &SerialApp::onReadyRead);  //this是指信号接收者就是信号发送者本身
    connect(m_pComProtocol, &COMProtocol::COMdata, this, &SerialApp::parseData);
    connect(m_pComProtocol, &COMProtocol::sendFromProtocol, this, &SerialApp::hwSend);
    //bool QObject::connect ( const QObject * sender, const char * signal,
    //                        const QObject * receiver, const char * member ) [static]
    //将信号发送者sender对象中的信号signal与接受者receiver中的member槽函数联系起来。
    //当指定信号signal时必须使用宏SIGNAL（），当指定槽函数时必须使用宏SLOT()，
    //如果发送者与连接者属于同一个对象时，那么在connect调用中接受者参数可以忽略。

#ifdef VIRTUALCOM
    m_DebugTiemrId = startTimer(1000);
#endif
    m_cmdTimerId = startTimer(100);
}

SerialApp::~SerialApp()
{
    closeCOM();
    delete m_pSerial;
    m_pSerial = 0;
}

//long ReadSerialPort(long /*handle*/, unsigned char *lpInBuffer, unsigned long /*dwBytesRead*/)
//{
//    memcpy( lpInBuffer, sCOMBuf.buf, sCOMBuf.curLen );
//    return sCOMBuf.curLen;
//}

//#ifdef __cplusplus
//}
//#endif

//串口的初始化及打开
bool SerialApp::init(const QString name, qint32 baudRate)
{
    qDebug()<<name +"  SerialApp::init" + QString::number(baudRate);
    //    Protocol_Register(1, ReadSerialPort, WriteSerialPort);
    //    start();
    return openCOM(name, baudRate);
}

bool SerialApp::openCOM(const QString name, qint32 baudRate)
{
    m_pSerial->setPortName(name);
    m_pSerial->setBaudRate(baudRate);
    m_pSerial->setDataBits(QSerialPort::Data8);
    m_pSerial->setParity(QSerialPort::NoParity);
    m_pSerial->setStopBits(QSerialPort::OneStop);
    m_pSerial->setFlowControl(QSerialPort::NoFlowControl);

    if (m_pSerial->open(QIODevice::ReadWrite)){
        m_pSerial->clearError();
        m_pSerial->clear();

        return true;
    }
    return false;
}

void SerialApp::closeCOM()
{
    if (m_pSerial->isOpen())
        m_pSerial->close();
}

bool SerialApp::hwSend(const quint8* buf, quint32 len)    //???
{
    if ( m_pSerial &&m_pSerial->write((const char*)buf, len) )
        return true;

    return false;
}

bool SerialApp::send(CommandID cmd, const CmdParam *params, quint32 num)
{
    int nCmdLen  = sizeof(cmd);
    int nParaLen = num * sizeof(CmdParam);
    int nDataLen = nCmdLen + nParaLen;
    char* data = new char[nDataLen];
    if (0 == data)
    {
        qDebug("new when send failed");
        return false;
    }
    *((CommandID*)data) = cmd;
    if (num > 0)
    {
        memcpy(data + nCmdLen, (const char*)params, nParaLen);
    }

    m_pComProtocol->Protocol_Send_Secure((quint8*)data, nDataLen, 100);   //???
}

void SerialApp::onUICmd(quint16 cmd, const short *params, quint32 num)   //???
{
    send((CommandID)cmd, (const CmdParam *)params, num);
}

void SerialApp::onReadyRead()
{
    QByteArray br = m_pSerial->readAll();
 //   qDebug()<<br.data();
    m_pComProtocol->parseCOMData( (quint8*)br.data(), br.length() );
}

void SerialApp::parseData(const quint8* data, int len)
{

    Q_UNUSED(len);  //避免编译器警告


    qint16* ptr = (qint16*)data;
    int index = 0;

    // 将这个提前，避免找不到错误代码
    qint16 errNo = ptr[2];
    emit setErrNo(errNo);

    qint16 status = ptr[index++];
    emit setCtrlSysStatus(status);

    qint16 alarmType = ptr[index++];
    emit setAlarmType(alarmType);

    index++;

    qint16 nBloodVlm = ptr[index++];//全血量
    emit setBloodVlm(nBloodVlm);
    qint16 nPlasmaVlm = ptr[index++];//血浆采集量
    emit setPlasmaVlm(nPlasmaVlm);
    qint16 nACDVlm = ptr[index++]; //抗凝剂量
    emit setACDVlm(nACDVlm);
    qint16 nPresvVlm = ptr[index++];//保养液量
    emit setPresvVlm(nPresvVlm);
    qint16 nRBCVlm = ptr[index++]; //悬红量
    emit setRBCVlm(nRBCVlm);
    qint16 nNaClVlm = ptr[index++]; //洗涤盐水量
    emit setNaClVlm(nNaClVlm);  
    qint16 nDpm = ptr[index++];      //压力监测值
    emit setDpm(nDpm);
    qint16 nBPSpeed = ptr[index++]; //血泵速
    emit setBPSpeed(nBPSpeed);
    qint16 nAPSpeed = ptr[index++]; //抗凝剂泵速
    emit setAPSpeed(nAPSpeed);
    qint16 nPresvPSpeed = ptr[index++]; //抗凝剂泵速
    emit setPresvPSpeed(nPresvPSpeed);
    qint16 nCFSpeed = ptr[index++]; //离心机速
    emit setCFSpeed(nCFSpeed);
    qint16 nLineDetector = ptr[index++];//管路探测器
    emit setLineDetector(nLineDetector);
    qint16 tmp = ptr[index++];
    qint32 nBool = (tmp<<16 & 0xffff0000)|ptr[index++]; //开关量

    emit setBoolParam(nBool);

    qint16 nVersion = ptr[index++]; //版本号
    emit setVersion(nVersion);

    qint16 nCollecttime = ptr[index++]; //采集总时长
    emit setCollecttime(nCollecttime);
//设置界面数据
    qint16 nBlood = ptr[index++];  //采血量
    emit setBlood(nBlood);

    qint16 nDraw_speed = ptr[index++]; //采集速度
    emit setDraw_speed(nDraw_speed);

    qint16 nCollect_speed = ptr[index++]; //制备速度
    emit setCollect_speed(nCollect_speed);

    qint16 nLinecoff = ptr[index++]; //管探系数
    emit setLinecoff(nLinecoff);

    qint16 nBpap_rate = ptr[index++]; // 抗凝比
    emit setBpap_rate(nBpap_rate);

    qint16 nPrs_speed = ptr[index++]; //保养液
    emit setPrs_speed(nPrs_speed);

    qint16 nBPreal = ptr[index++]; //血泵实际速度
    emit setBPreal(nBPreal);

    qint16 nAPreal = ptr[index++]; //抗凝剂实际速度
    emit setAPreal(nAPreal);

    qint16 nNPreal = ptr[index++]; //保养液实际速度
    emit setNPreal(nNPreal);

    QString strtmp = "";
    static int cnt = 0;
    for (int i = 0; i < index; i++)
    {
        strtmp =strtmp + QString("%1 ").arg(ptr[i]);
    }

    cnt++;
//    if ( 50 < cnt )    /// 每10s记录一次数据到log.txt
    {
        cnt = 0;
        qDebug() << strtmp;
    }

    emit COMStr(strtmp);     //串口数据查看
}


void SerialApp::timerEvent(QTimerEvent *event)  //定时器事件
{
    if ( event->timerId() == m_cmdTimerId ){
        if (!m_cmdList.isEmpty()){
            stCmd *cmd = m_cmdList.constLast();
            //            innerSend(cmd->cmd, cmd->params, cmd->num);
            send((CommandID)cmd->cmd, (const CmdParam *)cmd->params, cmd->num);

            m_cmdList.pop_back();
        }
    }

#ifdef VIRTUALCOM
    if ( event->timerId() == m_DebugTiemrId ){
        QFile file("data.txt");
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return;

        QByteArray br;
        QTextStream in(&file);

        while ( !in.atEnd() )
        {
            QString line = in.readLine();
            QStringList strList = line.split(" ", QString::SkipEmptyParts);

            foreach(QString s, strList)
            {
                br.append(s.toInt(0, 16));
            }
        }

        file.close();

        qDebug()<<br;
        m_pComProtocol->parseCOMData( (quint8*)br.data(), br.length() );
    }
#endif
}

COMProtocol::COMProtocol():
    QObject(0),
    m_smRxState(_sWaitBegin),
    m_usRxWord(0),
    m_usChkSum(0xFFFF),
    m_AckRslt(cmdAck_NULL)
{
    m_sbUnicodeData = false;

    startTimer(50);
}

qint32 COMProtocol::SendSecuredFrameAck(quint8 loop, quint8 ack)
{
    quint8 tx_buf[2 + 2 * sizeof(TDataLinkFrame)];

    int i = 0;
    quint8 crc;

    tx_buf[i++]=0x02;
    tx_buf[i++]=CharToAsciiHigh(FRAME_TYPE_SECURED_ACK);
    tx_buf[i++]=CharToAsciiLow(FRAME_TYPE_SECURED_ACK);
    crc = FRAME_TYPE_SECURED_ACK;

    tx_buf[i++]=CharToAsciiHigh(loop);
    tx_buf[i++]=CharToAsciiLow(loop);
    crc += loop;

    tx_buf[i++]=CharToAsciiHigh(1);
    tx_buf[i++]=CharToAsciiLow(1);
    crc += 1;

    tx_buf[i++]=CharToAsciiHigh(ack);
    tx_buf[i++]=CharToAsciiLow(ack);
    crc += ack;

    crc = ~crc;
    tx_buf[i++]=CharToAsciiHigh(crc);
    tx_buf[i++]=CharToAsciiLow(crc);
    tx_buf[i++]=0x03;

    emit sendFromProtocol(tx_buf, i);
    //    HostProtocol.hal.ptr_tx_hal(HostProtocol.hal.dev_handle, tx_buf, i);

    return 0;
}

qint32 COMProtocol::parseCOMData(quint8 *chbuf, int len)
{
    static u32 bHiByte     = TRUE;

    quint16 iCmdCnt = 0;
    quint8  ch;
    qint32  i = 0,j = 0;

    while(i < len)
    {
        ch = chbuf[i];
        i++;

        if (_sWaitBegin == m_smRxState)
        {
            /* If sync mode then wait for flag byte first */
            if ( 0x02 == ch )
            {
                m_smRxState = _sWaitType;
                m_usChkSum = 0xFFFF;
                m_usRxWord = 0;
            }
            continue;
        }
        if (_sWaitEnd == m_smRxState)
        {
            if ( 0x03 == ch )
            {
                switch(m_buf.type)
                {
                case FRAME_TYPE_SECURED_ACK:
                    m_bufRecv.append(&m_buf);
                    //                    RingFifoIn(ptr_protocol->ptr_secured_frame_ack_fifo, (quint8*)&m_buf);
                    break;
                case FRAME_TYPE_SECURED:
                    /* Correct command received */
                {
                    quint8 id = *(m_buf.payload);
                    cmdAckType ack = cmdAck_OK;
                    //                    CMD_CB_INFO info = cmdCbInfo[id];
                    //                    if ((info.id == id) && info.pf)
                    //                    {
                    //                        ack = info.pf(m_buf.payload, sizeof(m_buf.payload));
                    //                    }
                    SendSecuredFrameAck(m_buf.loop, ack);
                }
                    break;
                case FRAME_TYPE_NONE_SECURED:
                    emit COMdata(m_buf.payload, m_buf.len);
                    //                    if ( RingFifoIn(ptr_protocol->ptr_received_frame_fifo , (quint8*)&m_buf) )
                    //                    {
                    //                        iCmdCnt++;
                    //                    }
                    //                    else
                    //                    {
                    //                        //OUTPUT_TEXT("buffer full");
                    //                    }
                    break;
                default:
                    break;
                }
                m_smRxState = _sWaitBegin;
            }
            continue;
        }

        if (bHiByte)
        {
            ch = AsciiToChar(ch);
            if (ch > 0x0F)
            {
                if (FRAME_TYPE_SECURED == m_buf.type &&
                        (_sWaitLength == m_smRxState ||
                         _sWaitData == m_smRxState ||
                         _sWaitCheck == m_smRxState))
                {
                    SendSecuredFrameAck(m_buf.loop, cmdAck_UnexpectedEnd);
                }
                m_smRxState = _sWaitBegin;
                continue;
            }
            m_usRxWord = ch << 4;
            bHiByte = FALSE;
        }
        else
        {
            ch = AsciiToChar(ch);
            if (ch > 0x0F)
            {
                if (FRAME_TYPE_SECURED == m_buf.type &&
                        (_sWaitLength == m_smRxState ||
                         _sWaitData == m_smRxState ||
                         _sWaitCheck == m_smRxState))
                {
                    SendSecuredFrameAck(m_buf.loop, cmdAck_UnexpectedEnd);
                }
                m_smRxState = _sWaitBegin;
                continue;
            }
            m_usRxWord += ch;
            bHiByte = TRUE;

            switch (m_smRxState)
            {
            case _sWaitType:
                if (m_usRxWord != FRAME_TYPE_SECURED &&
                        m_usRxWord != FRAME_TYPE_SECURED_ACK &&
                        m_usRxWord != FRAME_TYPE_NONE_SECURED)
                {
                    //OUTPUT_TEXT("invalid frame type");
                    m_smRxState = _sWaitBegin;
                }
                else
                {
                    m_buf.type = m_usRxWord;
                    m_usChkSum = m_usRxWord;
                    m_smRxState = _sWaitLoop;
                }
                break;

            case _sWaitLoop:
                m_buf.loop = m_usRxWord;
                m_usChkSum += m_usRxWord;
                m_smRxState = _sWaitLength;
                break;

            case _sWaitLength:
                if (m_usRxWord > DATA_LINK_FRAME_LEN)
                {
                    if (FRAME_TYPE_SECURED == m_buf.type)
                    {
                        SendSecuredFrameAck(m_buf.loop, cmdAck_InvalidLen);
                    }
                    //OUTPUT_TEXT("invalid param length");
                    m_smRxState = _sWaitBegin;
                }
                else
                {
                    m_buf.len = m_usRxWord;
                    m_usChkSum += m_usRxWord;
                    m_usDataCnt = 0;
                    if(m_buf.len != 0)
                        m_smRxState = _sWaitData;
                    else
                        m_smRxState = _sWaitCheck;
                }

                break;

            case _sWaitData:
                m_buf.payload[m_usDataCnt++] = m_usRxWord;
                m_usChkSum += m_usRxWord;
                if (m_usDataCnt == m_buf.len)
                {
                    m_smRxState = _sWaitCheck;
                }

                break;

            case _sWaitCheck:
                m_buf.crc = m_usRxWord;
                m_usChkSum += m_usRxWord;
                if (m_usChkSum != 0xFF)
                {
                    //						OUTPUT_TEXT("invalid checksum");
                    if (FRAME_TYPE_SECURED == m_buf.type)
                    {
                        SendSecuredFrameAck(m_buf.loop, cmdAck_IncorrectCRC);
                    }
                    m_smRxState = _sWaitBegin;
                }
                else
                {
                    m_smRxState = _sWaitEnd;
                }
                break;
            default:
                break;
            }  /* switch(RxState) */
        }  /* Word received */
    }
    return iCmdCnt;
} /* RxInt */

qint32 COMProtocol::Protocol_Send(const quint8 * buf, quint8 len)
{
    quint8 tx_buf[2 + 2 * sizeof(TDataLinkFrame)];

    int i,j;
    quint8 crc;
    i=0;

    tx_buf[i++]=0x02;
    tx_buf[i++]=CharToAsciiHigh(FRAME_TYPE_NONE_SECURED);
    tx_buf[i++]=CharToAsciiLow(FRAME_TYPE_NONE_SECURED);
    crc = FRAME_TYPE_NONE_SECURED;

    tx_buf[i++]=CharToAsciiHigh(0);
    tx_buf[i++]=CharToAsciiLow(0);
    crc += 0;

    tx_buf[i++]=CharToAsciiHigh(len);
    tx_buf[i++]=CharToAsciiLow(len);
    crc += len;
    for(j=0;j<len;j++)
    {
        tx_buf[i++]=CharToAsciiHigh(buf[j]);
        tx_buf[i++]=CharToAsciiLow(buf[j]);
        crc += buf[j];
    }
    crc = ~crc;
    tx_buf[i++]=CharToAsciiHigh(crc);
    tx_buf[i++]=CharToAsciiLow(crc);
    tx_buf[i++]=0x03;

    //    HostProtocol.hal.ptr_tx_hal(HostProtocol.hal.dev_handle, tx_buf, i);
    emit sendFromProtocol(tx_buf, i);
    return 0;
}

qint32 COMProtocol::Protocol_Send_Secure(const quint8 * buf, quint8 len, qint32 timeout)
{
    static quint8 loop = 0;
    quint8 tx_buf[2 + 2 * sizeof(TDataLinkFrame)];

    int i = 0, j;
    quint8 crc;
    loop++;

    tx_buf[i++]=0x02;
    tx_buf[i++]=CharToAsciiHigh(FRAME_TYPE_SECURED);
    tx_buf[i++]=CharToAsciiLow(FRAME_TYPE_SECURED);
    crc = FRAME_TYPE_SECURED;

    tx_buf[i++]=CharToAsciiHigh(loop);
    tx_buf[i++]=CharToAsciiLow(loop);
    crc += loop;

    tx_buf[i++]=CharToAsciiHigh(len);
    tx_buf[i++]=CharToAsciiLow(len);
    crc += len;
    for(j=0;j<len;j++)
    {
        tx_buf[i++]=CharToAsciiHigh(buf[j]);
        tx_buf[i++]=CharToAsciiLow(buf[j]);
        crc += buf[j];
    }
    crc = ~crc;
    tx_buf[i++]=CharToAsciiHigh(crc);
    tx_buf[i++]=CharToAsciiLow(crc);
    tx_buf[i++]=0x03;

    //    FrameNode node;
    //    node.bvalid = true;
    //    node.loop   = loop;
    //    node.time   = timeout;
    //    m_bufTx.append(&node);

    //    HostProtocol.hal.ptr_tx_hal(HostProtocol.hal.dev_handle, tx_buf, i);
    emit sendFromProtocol(tx_buf, i);

    //    while(timeout > 0)
    //    {
    //        TDataLinkFrame* ack;
    //        if (RingFifoGetFull(HostProtocol.ptr_secured_frame_ack_fifo, (quint8**)&ack))
    //        {
    //            if ((*ack).loop == loop)
    //            {
    //                RingFifoCommitOut(HostProtocol.ptr_secured_frame_ack_fifo);
    //                return (*ack).payload[0];
    //            }
    //            RingFifoCommitOut(HostProtocol.ptr_secured_frame_ack_fifo);
    //        }
    //        msleep(50);
    //        timeout -= 50;
    //    }

    return 0;
}

bool COMProtocol::isCmdFinished(quint8* ack)
{
    if (m_AckRslt != cmdAck_NULL){
        *ack = m_AckRslt;
        m_AckRslt = cmdAck_NULL;
        return true;
    }

    return false;
}

void COMProtocol::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event );

    foreach (TDataLinkFrame *node, m_bufRecv) {

        foreach (FrameNode *p, m_bufTx) {
            if (node->loop == p->loop){
                m_AckRslt = node->payload[0];
                m_bufTx.removeOne(p);
            }
        }

        m_bufRecv.removeOne(node);
    }

    foreach (FrameNode *node, m_bufTx) {
        node->time -= 50;
        if (node->time <= 0){
            m_AckRslt = cmdAck_TimeOut;
            m_bufTx.removeOne(node);
        }
    }
}

