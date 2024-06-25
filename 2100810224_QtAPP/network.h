#ifndef NETWORK_H
#define NETWORK_H
#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include "defaultconfig.h"

#define API_NUM 10
#define HEADER_NUM 5
#define PROTOCAL_NUM 1

class packageParam{
public:
    QString time;
    QString equipmentId;
    QString equipmentName;
    QString valueName;
    double valueFbd;
    QString msg;
    QString requestId;
};

//ONENET云平台api索引
enum ONENET_Function{
    getDataStream = 0,
};
//ONENET云平台头固定字段索引
enum ONENET_Header{
    product_id = 0,
    device_name,
    authorization,
};
//ONENET云平台头解包协议索引
enum ONENET_Unpackage{
    fromJson = 0,
};
class network
{

public:
    int apiFunc;
    QByteArray api[API_NUM];            //云平台api接口
    QByteArray header[HEADER_NUM];      //http包中的固定字段

    network();
    void (*unPackage[PROTOCAL_NUM])(packageParam *package, QString rcivBuff);
};

class network_ONENET: public network{
public:
    network_ONENET();
    void sendData(ONENET_Function apiIndex);
    void receiveData(ONENET_Function apiIndex, QString qstrReply);
    QString getURL(ONENET_Function apiIndex, QByteArray product_id, QString device_name);

};

void ONENET_UnPackage_JSON(packageParam *package, QString rcivBuff);

extern network_ONENET onenet;

#endif // NETWORK_H
