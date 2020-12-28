#ifndef NETWORKINTERFACE_H
#define NETWORKINTERFACE_H

#include <QObject>
#include <QIODevice>
#include <QUrl>
#include <QMap>
#include "../global.h"
#include "netobj.h"
#include "json/json.h"

#define SPLIT_SYMBOL ("@")
#define PLASMA_REPLY_CODE_OK QString("000")

// 和朗程网络通信，外发数据管理
struct Donor_t_
{
    QString id;             // 浆员编号
    quint16 pageNumber;     // 当前显示页码
    quint16 pageSize;       // 没页最大记录数量
};

struct Result_t_ {
    quint16 cycleTimes;             // 循环次数
    quint16 onewayWeight;           // 单程采浆量（设置值）
    quint16 weight;                 // 采浆量
    quint16 procbldVol;            // 全血处理量
    quint16 anticoagulantDose;      // 抗凝剂用量
    quint16 sodiumChlorideDose;     // 氯化钠用量
    quint16 collectState;           // 采浆状态: 0:正常, 1:脂浆, 2:红浆, 3:其他异常

    quint16 equipmentSetNum;        // 四件套数量
    quint16 anticoagulantNum;       // 抗凝剂数量
    quint16 sodiumChlorideNum;      // 氯化钠注射液数量

    QString donorNo;                // 献浆员编号
    QString beginDate;              // 开采时间： hhmm(9:12-->0912)
    QString endDate;                // 结束时间
    QString twoNeedle;              // 二针穿刺: Y/N
    QString adverseReaction;        // 不良反应: Y/N
    QString remark;                 // 备注
    QString nurse;                  // 采浆护士编号

    QString equipmentSet;           // 四件套编号
    QString anticoagulantBatch;     // 抗凝剂编号
    QString sodiumChloride;         // 氯化钠注射液编号

    QString equipmentPCH;            //四件套批次号
    QString anticoagulantPCH;        //抗凝剂批次号
    QString sodiumChloridePCH;      //氯化钠注射批次号
};


struct Nurse_t_
{
    QString id;             // 护士编号
    quint16 pageNumber;
    quint16 pageSize;
};

struct DonorPic_t_
{
    QString id;             // 浆员编号
};

struct NursePic_t_
{
    QString id;             // 护士编号
};

struct DpStatus_t_
{
    QString st;             // 采浆机状态 0 :未知   1：空闲  2：已分配浆员（不再使用）  3：忙
};

typedef struct DpAlarm_t_
{
    QString sendType;
    QString donorId;
    QString donorName;
    QString nurseId;
    QString alarmCode;
}  DpAlarm_t;

typedef struct BeginCollectData_t_
{
    QString donorId;
    QString donorName;
    QString nurseId;
    QString time;
}  BeginCollectData_t;

// 服务器返回数据管理
struct InDonor_t_
{
    QString id;             // 浆员编号
    QString name;
    QString sex;            // "M" ：男   "W"：女
    QString bloodType;
    QString creDate;        // 建档日期，15位字符串，如2015-6-8（201506080000000）
    QString idCard;         // 身份证id
    QString processNo;      // 登记
    QString state;          // 浆员状态 "Y":固定 "N"：非固定 "NEW"：新浆员
    QString remark;         // 备注
    QString tip;            // 采浆提示信息
    QString address;        // 地址
    QString phone;          // 电话
    QString age;
    QString lastCollectDate;
    QString timesInYear;  //年内献浆次数
    QString isImM;          //是否免疫
    QString collectAge;    //献浆年龄

};

struct InResult_t_
{
    QString code;
};

struct IdAndName_t_
{
    QString id;             // 编号
    QString name;           // 名称
};

struct InNurse_t_
{
    QString id;             // 登录编号
    QString name;           // 真实姓名
    QString sex;
    QString phone;
    QString deptName;     //部门名称
};

struct InDonorPic_t_
{
    QString id;
    QString pic;            // 照片信息，Base 64 编码
};

struct InNursePic_t_
{
    QString id;
    QString pic;            // 照片信息，Base 64 编码
};

struct InTime_t_
{
    QString time;           // 15位字符串，2015-06-08 09:05表示为 201506080905000
};

typedef struct Donor_t_         Donor_t;            //献浆员信息查询
typedef struct Result_t_        Result_t;           //采浆信息上传
typedef struct Nurse_t_         Nurse_t;            //护士信息查询
typedef struct NursePic_t_     NursePic_t;        //护士照片查询
typedef struct DonorPic_t_      DonorPic_t;         //浆员照片
typedef struct DpStatus_t_      DpStatus_t;         //采浆机状态

typedef struct InDonor_t_       InDonor_t;          // 浆员信息
typedef struct InResult_t_      InResult_t;         // 采集结果返回
typedef struct IdAndName_t_     InDisposable_t;     // 四件套信息
typedef struct IdAndName_t_     InACD_t;            // 抗凝剂信息
typedef struct IdAndName_t_     InNacl_t;           // 氯化钠注射液信息
typedef struct InNurse_t_       InNurse_t;          // 护士信息
typedef struct InNursePic_t_    InNursePic_t;       // 护士信息
typedef struct InDonorPic_t_    InDonorPic_t;       // 浆员照片信息
typedef struct InTime_t_        InTime_t;           // 服务器返回时间信息


enum ID_NET
{
    N_DONOR,
    N_RESULT,
    N_DISPOSABLE,
    N_ACD,
    N_NACL,
    N_NURSE,            // 查询护士信息
    N_DONORPIC,
    N_TIME,             // 获取时间
    N_STATUS,
    N_NURSEPIC,
    N_ALARM,          //提交机器报警信息
    N_BEGININFO,    //提交开始采集的相关信息
    N_ID_MAX
};


const quint16 CONNECT_CODE = 200;
const quint16 DISCONNECT_CODE = 0;

class ProtocolHelper;
class MyUrl;
class UrlLang;
class ProtocolLang;

class NetworkInterface : public QObject
{
    Q_OBJECT
private:
    explicit NetworkInterface(QObject *parent = 0);
    ~NetworkInterface(){}

public:
    static NetworkInterface& getInst();

    NetReply *sendData( ID_NET id, void *data = NULL);
    bool parseNetData(ID_NET id, const QByteArray &in,
                      void *out, QString &errmsg);

    void      setServerAdress( QString adress );
    QString getServerAdress();

    void refreshServerCfg();
private:
    NetReply *serchDonorInfo( const void *p );
    NetReply *sendResult( const void *p );
    NetReply *serchNurseInfo( const void *p );
    NetReply *serchDonorPic( const void *p );

private:
    ProtocolHelper *m_protocolHelper;

    static QString m_errmsg;    
    QString            m_serverAdress;

    MyUrl         *m_pCurUrlMan;

    UrlLang        *m_pUrlLang;
    ProtocolLang   *m_pPrtLang;
};


#endif // NETWORKINTERFACE_H
