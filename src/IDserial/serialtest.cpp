#include "serialtest.h"
#include <QDebug>
#include <QTime>
#include <QCoreApplication>

SerialTest::Settings currentsetting;//定义设定值结构体的结构体变量
QSerialPort serialtest;

qint64 c_sendnumber,c_receivenumber;

SerialTest::SerialTest(QSerialPort *parent):QSerialPort (parent),m_receivedata("Receive Label"),m_receivenumber("0"),m_sendnumber("0")
{
    QObject::connect(&serialtest, SIGNAL(readyRead()),this, SLOT(receivefrom()));//将端口收到数据产生的信号绑定receivefrom()函数;

}
//打开端口并设置:函数的参数（……Index由qml中combobox的currentIndex决定），由按钮触发
void SerialTest::openAndSetPort(int PortNameIndex,
                                int BaudRateIndex,
                                int DatabitsIndex,
                                int ParityIndex,
                                int StopbitsIndex,
                                int FlowcontrolIndex)
{
    ////////////////////1.得到当前选择的各项设置//////////////////////////////
    //得到当前端口名
    QString allname[7]={"ttyACM0","ttyACM1"};//列举所有的端口名
    currentsetting.name=allname[PortNameIndex];//由qml里表示name的combobox的currentIndex来确定当前的name
    qDebug()<<" ok setPortName to ";//通过输出来验证设定成功

    //得到当前波特率
    qint32 allbauRate[4]={9600,19200,38400,115200};
    currentsetting.baudRate=allbauRate[BaudRateIndex];

    //得到当前发送位数
    QSerialPort::DataBits allDatabits[4]={QSerialPort::Data5,
                                          QSerialPort::Data6,
                                          QSerialPort::Data7,
                                          QSerialPort::Data8};
    currentsetting.dataBits=allDatabits[DatabitsIndex];

    //得到当前Parity
    QSerialPort::Parity allparity[5]={QSerialPort::NoParity,
                                      QSerialPort::EvenParity,
                                      QSerialPort::OddParity,
                                      QSerialPort::MarkParity,
                                      QSerialPort::SpaceParity};
    currentsetting.parity=allparity[ParityIndex];

    //得到当前停止位
    QSerialPort::StopBits allstopBits[3]={QSerialPort::OneStop,
                                          QSerialPort::OneAndHalfStop,
                                          QSerialPort::TwoStop};
    currentsetting.stopBits=allstopBits[StopbitsIndex];

    //得到当前FlowControl
    QSerialPort::FlowControl allflowControl[3]={QSerialPort::NoFlowControl,
                                                QSerialPort::HardwareControl,
                                                QSerialPort::SoftwareControl};
    currentsetting.flowControl=allflowControl[FlowcontrolIndex];


////////////////////2.设定当前端口名//////////////////////////////
    serialtest.setPortName(currentsetting.name);

////////////////////3.打开这一端口并按照当前设置信息进行设置//////////////////////////////
    if (serialtest.open(QIODevice::ReadWrite))//打开这一端口
    {
        qDebug()<<"open port sucess";

        if(serialtest.setBaudRate(currentsetting.baudRate)//设置各项信息
                && serialtest.setDataBits(currentsetting.dataBits)
                && serialtest.setParity(currentsetting.parity)
                && serialtest.setStopBits(currentsetting.stopBits)
                && serialtest.setFlowControl(currentsetting.flowControl))
        {
            qDebug()<<"set sucess";
        }
    }
}


////////////////////4.发送数据//////////////////////////////
void SerialTest::sendto()//此函数由qml里的send按钮触发，sendmessage来源于qml文本框的当前文本，
{
    QString dataStr = "16 54 0d";//将QString转为QByteArray，并加上'\r'（回车符）,因为芯片要求在回车符之后再返回数据

    if (dataStr.length() % 2){
        dataStr.insert(dataStr.length()-1, '0');
    }

    QByteArray sendData;
    StringToHex(dataStr, sendData);

    serialtest.write(sendData);
}

void SerialTest::setsendnumber(QString sendnumber)//更新发送的数据字节总数，触发sendnumberChanged()的消息响应函数sendnumber()来更新显示
{
//    m_sendnumber=sendnumber;
//    emit sendnumberChanged();
}

QString SerialTest::sendnumber()//响应sendnumberChanged()消息
{
//    return m_sendnumber;
}

void SerialTest::StringToHex(QString str, QByteArray &senddata)
{
    int hexdata,lowhexdata;
    int hexdatalen = 0;
    int len = str.length();
    senddata.resize(len / 2);
    char lstr,hstr;
    for (int i = 0; i < len; ) {
        hstr = str[i].toLatin1();
        if (hstr == ' ') {
            ++i;
            continue;
        }
        ++i;
        if (i  >= len) break;
        lstr = str[i].toLatin1();
        hexdata = ConvertHexChar(hstr);
        lowhexdata = ConvertHexChar(lstr);
        if ((hexdata == 16) || (lowhexdata == 16))
            break;
        else
            hexdata = hexdata*16 + lowhexdata;
        ++i;
        senddata[hexdatalen] = (char)hexdata;
        ++hexdatalen;
    }
    senddata.resize(hexdatalen);
}

char SerialTest::ConvertHexChar(char ch)
{
    if ((ch >= '0') && (ch <= '9'))
        return ch - 0x30;
    else if ((ch >= 'A') && (ch <= 'F'))
        return ch - 'A' + 10;
    else if ((ch >= 'a') && (ch <= 'f'))
        return ch - 'a' + 10;
    else return ch -  ch;
}

void SerialTest::Delay(unsigned int msec)
{
    QTime _Timer = QTime::currentTime().addMSecs(msec);

    while( QTime::currentTime() < _Timer )

    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

}

////////////////////4.接收数据//////////////////////////////
void SerialTest::receivefrom()//由readyRead()消息出发（在前边进行绑定），当串口收到数据此消息被激活（对于串口，每发送出去一个字节，都会将此字节返回，触发readyread消息，当芯片有特殊指令时，收到的信息更多，比如对sim900，发送0000，芯片就会受到0000，但是发送AT，会受到 AT OK）
{
    QByteArray blood = serialtest.readAll();//读取所有收到的数据

    QString receivedata=blood.data();//将QByteArray转为QString来显示
    emit receivedataChanged(receivedata);//发送消息触发receivedata()，更新当前收到的数据显示receivedata

    Delay(1000);

    sendto();
    qDebug()<<"=====>"<<receivedata;
}


void SerialTest::setreceivenumber(QString receivenumber)//更新接收的数据字节总数
{
//    m_receivenumber=receivenumber;
//    emit receivenumberChanged();;
}

QString SerialTest::receivenumber()//响应receivenumberChanged()消息
{
//    return m_receivenumber;
}


QString SerialTest::receivedata()//qml读取receivedata值的时候就会触发此函数,或者emit receivedataChanged()更新当前收到的数据显示时触发
{
//    return m_receivedata;
}
void SerialTest::setreceivedata(QString receivedata)//其任务已被receive from函数完成，但是在清空数据时用到这个函数
{
//    m_receivedata=receivedata;
//    emit receivedataChanged();
}

////////////////////5.关闭端口//////////////////////////////
void SerialTest::closePort()//由按钮出发
{
    QString dataStr = "16 54 0e";

    if (dataStr.length() % 2){
        dataStr.insert(dataStr.length()-1, '0');
    }

    QByteArray sendData;
    StringToHex(dataStr, sendData);

    serialtest.write(sendData);
//    serialtest.close();
    qDebug()<<"close port sucess";
}

void SerialTest::clearnumber()//由按钮出发
{
//    c_sendnumber=0;
//    c_receivenumber=0;
}

