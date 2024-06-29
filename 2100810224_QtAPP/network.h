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

//ONENET云平台api索引
enum function{
    getDataStream = 0,
    getDeviceDetail,
};
//ONENET云平台头固定字段索引
enum hearder{
    product_id = 0,
    device_name,
    authorization,
};
//ONENET云平台头解包协议索引
enum unpackageMode{
    fromJson = 0,
};
class network
{
public:
    function apiFuc;
    QByteArray api[API_NUM];            //云平台api接口
    QByteArray header[HEADER_NUM];      //http包中的固定字段

    network();
    QString getURL(function apiindex, QByteArray product_id, QString device_name);
    void (*unPackage[PROTOCAL_NUM])(equipment *package, QString rcivBuff);
    void sendGetDataStream(QNetworkAccessManager* manager, QByteArray productid, QString productname);
    void sendGetDeviceDetail(QNetworkAccessManager* manager, QByteArray productid, QString productname);
    void receiveData(function apiIndex, QString qstrReply, defaultConfig proudct = productOneConfig);
};

void ONENET_UnPackage_JSON(equipment *package, QString rcivBuff);

extern network onenet;

#endif // NETWORK_H
