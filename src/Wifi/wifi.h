#ifndef WIFI_H
#define WIFI_H
#include <QObject>

class Wifi : public QObject
{
    Q_OBJECT

public:
    explicit Wifi(QObject *parent = 0);
    ~Wifi();

private slots:
    void onpushButtonclicked(void);

    void oncomboBoxcurrentIndexChanged(int index);

private:
    QStringList wifi_name;
};
#endif // WIFI_H
