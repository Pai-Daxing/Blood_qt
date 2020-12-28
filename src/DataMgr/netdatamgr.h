#ifndef NETDATAMGR_H
#define NETDATAMGR_H

#include "../Network/networkinterface.h"
#include "../AlarmMgr/alarmmgr.h"
#include <QSettings>

#define NETDATA_FILENAME ("./Datas/netdata.ini")

/*报警信息：定义每个报警所包含的信息结构*/
typedef struct _NetAlarmInfo
{
    AlarmType    type;      //类型
    QString       code;      //网络编码
} NetAlarmInfo ;

extern const NetAlarmInfo sNetAlarmInfoTable[AlmType_MAX];

class NetDataMgr : public QObject
{
    Q_OBJECT

private:
    NetDataMgr();

public:
    static NetDataMgr &getInst(){static NetDataMgr mgr; return mgr;}

    void setDonor(const InDonor_t &data);
    void setNurse(const InNurse_t &data);
    void setDisposableList(const InDisposable_t &data);
    void setACDList(const InACD_t &data);
    void setNaclList(const InNacl_t &data);
    void setCurDisposable(const InDisposable_t &data);
    void setCurACD(const InACD_t &data);
    void setCurNacl(const InNacl_t &data);
    void setCurDisposableNum(quint16 num);
    void setCurACDNum(quint16 num);
    void setCurNaclNum(quint16 num);

    QString getDisposableName(QString id);
    QString getAcdName(QString id);
    QString getNaclName(QString id);

    InDisposable_t getCurDisposable();
    InACD_t getCurADC();
    InNacl_t getCurNacl();
    quint16 getCurDisposableNum();
    quint16 getCurADCNum();
    quint16 getCurNaclNum();

    InDonor_t               getDonor();
    InNurse_t               getNurse();
    QList<InDisposable_t>   getDisposableList();
    QList<InACD_t>          getACDList();
    QList<InNacl_t>         getNaclList();

protected:
//    void changeEvent(QEvent *e);

private:
    void updateDonor();
    void updateNurse();
    void updateDList();
    void updateAList();
    void updateNList();

private:    
//     Ui::NetDataMgr ui;

    QSettings               *m_setting;
    // 当前浆员信息
    InDonor_t               m_donor;
    // 当前登录护士信息
    InNurse_t               m_nurse;

    // 记录当天可用的 四件套、抗凝剂、氯化钠注射液信息
    QList<InDisposable_t>   m_dList;
    QList<InACD_t>          m_aList;
    QList<InNacl_t>         m_nList;

    bool m_donorIsLatest;
    bool m_nurseIsLatest;
    bool m_dListIsLatest;
    bool m_aListIsLatest;
    bool m_nListIsLatest;
};

#endif // NETDATAMGR_H
