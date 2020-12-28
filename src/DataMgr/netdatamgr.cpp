#include "netdatamgr.h"

const NetAlarmInfo sNetAlarmInfoTable[AlmType_MAX] = {
    //类型                       级别
    {ALM_none,                       "00000"},
    {ALM_ComError,                  "00000"},
};

NetDataMgr::NetDataMgr()
{
    m_setting = new QSettings(NETDATA_FILENAME, QSettings::IniFormat);

    m_donorIsLatest = false;
    m_nurseIsLatest = false;
    m_dListIsLatest = false;
    m_aListIsLatest = false;
    m_nListIsLatest = false;
}

//void NetDataMgr::changeEvent(QEvent *e)
//{
//    QWidget::changeEvent(e);
//    switch (e->type()) {
//    case QEvent::LanguageChange:
//       ui.retranslateUi(this);

//        break;
//    default:
//        break;
//    }
//}

//------------------------------------------------------------------------------
void NetDataMgr::setDonor(const InDonor_t &data)
{
    m_setting->setValue("dnonr/id", QVariant(data.id));
    m_setting->setValue("dnonr/name", QVariant(data.name));
    m_setting->setValue("dnonr/sex", QVariant(data.sex));
    m_setting->setValue("dnonr/bloodType", QVariant(data.bloodType));
    m_setting->setValue("dnonr/creDate", QVariant(data.creDate));
    m_setting->setValue("dnonr/idCard", QVariant(data.idCard));
    m_setting->setValue("dnonr/processNo", QVariant(data.processNo));
    m_setting->setValue("dnonr/state", QVariant(data.state));
    m_setting->setValue("dnonr/tip", QVariant(data.tip));
    m_setting->setValue("dnonr/address", QVariant(data.address));
    m_setting->setValue("dnonr/phone", QVariant(data.phone));

    m_setting->setValue("dnonr/age", QVariant(data.age));
    m_setting->setValue("dnonr/lastCollectDate", QVariant(data.lastCollectDate));
    m_setting->setValue("dnonr/timesInYear", QVariant(data.timesInYear));
    m_setting->setValue("dnonr/isImM", QVariant(data.isImM));
    m_setting->setValue("dnonr/collectAge", QVariant(data.collectAge));

    m_donorIsLatest = false;
}

void NetDataMgr::setNurse(const InNurse_t &data)
{
    m_setting->setValue("nurse/id", QVariant(data.id));
    m_setting->setValue("nurse/name", QVariant(data.name));
    m_setting->setValue("nurse/sex", QVariant(data.sex));
    m_setting->setValue("nurse/phone", QVariant(data.phone));
    m_setting->setValue("nurse/deptName", QVariant(data.deptName));

    m_nurseIsLatest = false;
}

void NetDataMgr::setDisposableList(const InDisposable_t &data)
{
    m_setting->setValue("disposable_list/id", QVariant(data.id));
    m_setting->setValue("disposable_list/name", QVariant(data.name));

    m_dListIsLatest = false;
}

void NetDataMgr::setACDList(const InACD_t &data)
{
    m_setting->setValue("acd_list/id", QVariant(data.id));
    m_setting->setValue("acd_list/name", QVariant(data.name));

    m_aListIsLatest = false;
}

void NetDataMgr::setNaclList(const InNacl_t &data)
{
    m_setting->setValue("nacl_list/id", QVariant(data.id));
    m_setting->setValue("nacl_list/name", QVariant(data.name));

    m_nListIsLatest = false;
}

void NetDataMgr::setCurDisposable(const InDisposable_t &data)
{
    m_setting->setValue("cur_disposable/id", QVariant(data.id));
    m_setting->setValue("cur_disposable/name", QVariant(data.name));
}

void NetDataMgr::setCurACD(const InACD_t &data)
{
    m_setting->setValue("cur_acd/id", QVariant(data.id));
    m_setting->setValue("cur_acd/name", QVariant(data.name));
}

void NetDataMgr::setCurNacl(const InNacl_t &data)
{
    m_setting->setValue("cur_nacl/id", QVariant(data.id));
    m_setting->setValue("cur_nacl/name", QVariant(data.name));
}

void NetDataMgr::setCurDisposableNum(quint16 num)
{
    m_setting->setValue("cur_disposable/num", QVariant(num));
}

void NetDataMgr::setCurACDNum(quint16 num)
{
    m_setting->setValue("cur_acd/num", QVariant(num));
}

void NetDataMgr::setCurNaclNum(quint16 num)
{
    m_setting->setValue("cur_nacl/num", QVariant(num));
}


InDisposable_t NetDataMgr::getCurDisposable()
{
    InDisposable_t data;
    data.id = m_setting->value("cur_disposable/id", QVariant(QString(""))).toString();
    data.name = m_setting->value("cur_disposable/name", QVariant(QString(""))).toString();

    return data;
}

InACD_t NetDataMgr::getCurADC()
{
    InACD_t data;
    data.id = m_setting->value("cur_acd/id", QVariant(QString(""))).toString();
    data.name = m_setting->value("cur_acd/name", QVariant(QString(""))).toString();

    return data;
}

InNacl_t NetDataMgr::getCurNacl()
{
    InNacl_t data;
    data.id = m_setting->value("cur_nacl/id", QVariant(QString(""))).toString();
    data.name = m_setting->value("cur_nacl/name", QVariant(QString(""))).toString();

    return data;
}

quint16 NetDataMgr::getCurDisposableNum()
{
    return m_setting->value("cur_disposable/num", QVariant(0)).toInt();
}

quint16 NetDataMgr::getCurADCNum()
{
    return m_setting->value("cur_acd/num", QVariant(0)).toInt();
}

quint16 NetDataMgr::getCurNaclNum()
{
    return m_setting->value("cur_nacl/num", QVariant(0)).toInt();
}


//------------------------------------------------------------------------------
InDonor_t NetDataMgr::getDonor()
{
    if (!m_donorIsLatest)
    {
        updateDonor();
    }

    return m_donor;
}

InNurse_t NetDataMgr::getNurse()
{
    if (!m_nurseIsLatest)
    {
        updateNurse();
    }

    return m_nurse;
}

QList<InDisposable_t> NetDataMgr::getDisposableList()
{
    if (!m_dListIsLatest)
    {
        updateDList();
    }

    return m_dList;
}

QList<InNacl_t> NetDataMgr::getNaclList()
{
    if (!m_nListIsLatest)
    {
        updateNList();
    }

    return m_nList;
}

QList<InACD_t> NetDataMgr::getACDList()
{
    if (!m_aListIsLatest)
    {
        updateAList();
    }

    return m_aList;
}

//------------------------------------------------------------------------------
void NetDataMgr::updateDonor()
{
    m_donor.id          = m_setting->value("dnonr/id", QVariant(QString(""))).toString();
    m_donor.name        = m_setting->value("dnonr/name", QVariant(QString(""))).toString();
    m_donor.sex         = m_setting->value("dnonr/sex", QVariant(QString(""))).toString();
    m_donor.bloodType   = m_setting->value("dnonr/bloodType", QVariant(QString(""))).toString();
    m_donor.creDate     = m_setting->value("dnonr/creDate", QVariant(QString(""))).toString();
    m_donor.idCard      = m_setting->value("dnonr/idCard", QVariant(QString(""))).toString();
    m_donor.processNo   = m_setting->value("dnonr/processNo", QVariant(QString(""))).toString();
    m_donor.state       = m_setting->value("dnonr/state", QVariant(QString(""))).toString();
    m_donor.tip         = m_setting->value("dnonr/tip", QVariant(QString(""))).toString();
    m_donor.address     = m_setting->value("dnonr/address", QVariant(QString(""))).toString();
    m_donor.phone       = m_setting->value("dnonr/phone", QVariant(QString(""))).toString();

    m_donor.age             = m_setting->value("dnonr/age", QVariant(QString(""))).toString();
    m_donor.lastCollectDate = m_setting->value("dnonr/lastCollectDate", QVariant(QString(""))).toString();
    m_donor.timesInYear     = m_setting->value("dnonr/timesInYear", QVariant(QString(""))).toString();
    m_donor.isImM           = m_setting->value("dnonr/isImM", QVariant(QString(""))).toString();
    m_donor.collectAge      = m_setting->value("dnonr/collectAge", QVariant(QString(""))).toString();

    m_donorIsLatest = true;
}

void NetDataMgr::updateNurse()
{
    m_nurse.id      = m_setting->value("nurse/id", QVariant(QString(""))).toString();
    m_nurse.name    = m_setting->value("nurse/name", QVariant(QString(""))).toString();
    m_nurse.phone   = m_setting->value("nurse/phone", QVariant(QString(""))).toString();
    m_nurse.sex     = m_setting->value("nurse/sex", QVariant(QString(""))).toString();
    m_nurse.deptName = m_setting->value("nurse/deptName", QVariant(QString(""))).toString();

    m_nurseIsLatest = true;
}

void NetDataMgr::updateDList()
{
    InDisposable_t data;

    data.id   = m_setting->value("disposable_list/id",
                                 QVariant(QString(""))).toString();
    data.name = m_setting->value("disposable_list/name",
                                 QVariant(QString(""))).toString();

    QStringList id = data.id.split(SPLIT_SYMBOL);
    QStringList name = data.name.split(SPLIT_SYMBOL);

    quint16 size = id.size();
    if ( size != name.size() )
    {
        return;
    }

    m_dList.clear();

    quint16 i;
    InDisposable_t it;
    for (i = 0; i < size; i++)
    {
        if ( id.at(i).isEmpty() )
        {
            continue;
        }

        it.id = id.at(i);
        it.name = name.at(i);

        m_dList.append(it);
    }

    it.id = QString("");
    it.name = QString( tr("空") );

    m_dList.append(it);

    m_dListIsLatest = true;
}

void NetDataMgr::updateAList()
{
    InACD_t data;

    data.id   = m_setting->value("acd_list/id",
                                 QVariant(QString(""))).toString();
    data.name = m_setting->value("acd_list/name",
                                 QVariant(QString(""))).toString();

    QStringList id = data.id.split(SPLIT_SYMBOL);
    QStringList name = data.name.split(SPLIT_SYMBOL);

    quint16 size = id.size();
    if ( size != name.size() )
    {
        return;
    }

    m_aList.clear();

    quint16 i;
    InACD_t it;
    for (i = 0; i < size; i++)
    {
        if ( id.at(i).isEmpty() )
        {
            continue;
        }

        it.id = id.at(i);
        it.name = name.at(i);

        m_aList.append(it);
    }

    it.id = QString("");
    it.name = QString( tr("空") );

    m_aList.append(it);

    m_aListIsLatest = true;
}

void NetDataMgr::updateNList()
{
    InNacl_t data;

    data.id   = m_setting->value("nacl_list/id",
                                 QVariant(QString(""))).toString();
    data.name = m_setting->value("nacl_list/name",
                                 QVariant(QString(""))).toString();

    QStringList id = data.id.split(SPLIT_SYMBOL);
    QStringList name = data.name.split(SPLIT_SYMBOL);

    quint16 size = id.size();
    if ( size != name.size() )
    {
        return;
    }

    m_nList.clear();

    quint16 i;
    InNacl_t it;

    for (i = 0; i < size; i++)
    {
        if ( id.at(i).isEmpty() )
        {
            continue;
        }

        it.id = id.at(i);
        it.name = name.at(i);

        m_nList.append(it);
    }

    it.id = QString("");
    it.name = QString( tr("空") );
    m_nList.append(it);

    m_nListIsLatest = true;
}

//------------------------------------------------------------------------------
QString NetDataMgr::getDisposableName(QString id)
{
    if (!m_dListIsLatest)
    {
        updateDList();
    }

    quint16 size = m_dList.size();
    quint16 i;

    for (i = 0; i < size; i++)
    {
        if (m_dList.at(i).id == id)
        {
            return m_dList.at(i).name;
        }
    }

    return tr("空");
}

QString NetDataMgr::getAcdName(QString id)
{
    if (!m_aListIsLatest)
    {
        updateAList();
    }

    quint16 size = m_aList.size();
    quint16 i;

    for (i = 0; i < size; i++)
    {
        if (m_aList.at(i).id == id)
        {
            return m_aList.at(i).name;
        }
    }

    return tr("空");
}

QString NetDataMgr::getNaclName(QString id)
{
    if (!m_nListIsLatest)
    {
        updateNList();
    }

    quint16 size = m_nList.size();
    quint16 i;

    for (i = 0; i < size; i++)
    {
        if (m_nList.at(i).id == id)
        {
            return m_nList.at(i).name;
        }
    }

    return tr("空");
}
