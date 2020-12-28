#include "urllang.h"

UrlLang::UrlLang(QObject *parent) :
    MyUrl(parent)
{
    httpIdList[N_DONOR]        = QString( "/lcwebservice/bims/donor/findNowCanCollectDonors.json");
    httpIdList[N_RESULT]        = QString( "/lcwebservice/bims/plasmaCollection/save.json" );
    httpIdList[N_DISPOSABLE] = QString( "/lcwebservice/bims/stockInDetail/findEquipments.json" );
    httpIdList[N_ACD]             = QString( "/lcwebservice/bims/stockInDetail/findAnticoagulants.json") ;
    httpIdList[N_NACL]           = QString( "/lcwebservice/bims/stockInDetail/findSodiumChlorides.json" );
    httpIdList[N_NURSE]         = QString( "/lcwebservice/bims/user/findNurse.json" );
    httpIdList[N_DONORPIC]   = QString( "/lcwebservice/bims/donor/findDonorPhoto.json" );
    httpIdList[N_TIME]           = QString( "/lcwebservice/bims/server/findServerTime.json" );
    httpIdList[N_STATUS]        = QString( "/lcwebservice/bims/status.json" );
}

QString UrlLang::getUrl( ID_NET id )
{
    return httpIdList[id];
}
