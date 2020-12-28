#include "wifi.h"
#include <QLocale>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QInputDialog>
#include <QThread>
#include <QInputDialog>
#include <QComboBox>
#define WIFI_PATH "/home/pi/ssid.txt"

Wifi::Wifi(QObject *parent) :
    QObject(parent)
{

}

Wifi::~Wifi()
{

}

void Wifi::onpushButtonclicked()
{

//    QComboBox *comboBox = new QComboBox;

//    system("rm temp");
//    system("rm ssid.txt");
//    system("wpa_cli -i wlan0 scan ");
//    system("wpa_cli -i wlan0 scan_result > /home/pi/temp");
//    system("awk '{print $5}' /home/pi/temp > /home/pi/ssid.txt");
//    qDebug() << "scan finish";

//    QFile file("/home/pi/ssid.txt");
//    qDebug()<<"!";
//    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
//    {
//        qDebug() << "Open file failed.";
//        return;
//    }
//    QTextStream stream(&file);
//    QString name;
//    while(stream.atEnd() == 0)
//    {
//        name = stream.readLine();
//        wifi_name.append(name);
//    }
//    if(wifi_name.isEmpty()) return;
//    comboBox->clear();

//    int i;
//    for(i=0;i<wifi_name.count();i++)
//        comboBox->addItem(wifi_name[i],i);
//    qDebug() << "add wifi finish";
//    file.close();
}

void Wifi::oncomboBoxcurrentIndexChanged(int index)
{
//    bool ok;
//    QComboBox *comboBox = new QComboBox;
//    static int lastIndex = 0;
//    if(index != lastIndex && index != 0)
//    {
//        qDebug() << "start set name and password";
//        QString UserName =  comboBox->currentText();
//        QString psk = QInputDialog::getText(this, tr("please input password"),
//                                                  tr("%1的安全密钥:").arg(UserName), QLineEdit::Normal,
//                                                  tr("b4f53h6j"),&ok);
//        if(ok)
//        {
//            system("sed -i /psk/d /etc/wpa_supplicant/wpa_supplicant.conf");
//            QThread::msleep(100);
//            system("sed -i /ssid/d /etc/wpa_supplicant/wpa_supplicant.conf");
//            QThread::msleep(100);

//            QString addUser = tr("sed -i 6i\\ssid=\\\"%1\\\" /etc/wpa_supplicant/wpa_supplicant.conf").arg(UserName);
//            QString addPwd = tr("sed -i 7i\\psk=\\\"%1\\\" /etc/wpa_supplicant/wpa_supplicant.conf").arg(psk);

//            qDebug() << addUser.toLatin1();
//            system(addUser.toLatin1());
//            QThread::msleep(100);
//            qDebug() << addPwd;
//            system(addPwd.toLatin1());
//        }
//        else
//        {
//            qDebug() << "input password cancel";
//        }
//    }
//    lastIndex = index;
}
