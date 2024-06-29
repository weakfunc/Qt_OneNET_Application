#include "network.h"

//设置云平台API接口
QByteArray ONENET_API[API_NUM] = {"http://iot-api.heclouds.com/datapoint/current-datapoints?",
                                  "https://iot-api.heclouds.com/device/detail?"};

//设置云平台HTTP协议固定字段
QByteArray ONENET_HEADERP[HEADER_NUM] = {"product_id=",
                                         "&device_name=",
                                         "authorization"};

network onenet;

network::network(){
    int index;
    for(index = 0; index < API_NUM; index++){
        api[index] = ONENET_API[index];
    }
    for(index = 0; index < HEADER_NUM; index++){
        header[index] = ONENET_HEADERP[index];
    }
    unPackage[fromJson] = ONENET_UnPackage_JSON;
}

 //QString("http://iot-api.heclouds.com/datapoint/current-datapoints?product_id=773E26dPR4&device_name=TEST_1")
QString network::getURL(function apiindex, QByteArray id, QString name){
    return QString(api[apiindex] + header[product_id] + id + header[device_name] + name.toUtf8());
}

void network::sendGetDataStream(QNetworkAccessManager* manager, QByteArray productid, QString productname){
    apiFuc = getDataStream;

    QNetworkRequest req;
    QString url;
    url = getURL(getDataStream, productid, productname);
    req.setUrl(url);
    req.setRawHeader(onenet.header[authorization],productOneConfig.token);
    manager->get(req);
    qDebug()<<"GetDataStream已发送";
}

void network::sendGetDeviceDetail(QNetworkAccessManager* manager, QByteArray productid, QString productname){
    apiFuc = getDeviceDetail;

    QNetworkRequest req;
    QString url;
    url = getURL(getDeviceDetail, productid, productname);
    req.setUrl(url);
    req.setRawHeader(onenet.header[authorization],productOneConfig.token);
    manager->get(req);
    qDebug()<<"GetDeviceDetail已发送";
}

void network::receiveData(function apiIndex, QString qstrReply, defaultConfig proudct){
    equipment package;
    QString status;
    int index;
    //解包
    unPackage[fromJson](&package, qstrReply);
    qDebug()<<"已接收";
    qDebug()<< "code: " << package.code;
    qDebug()<< "msg: "<<package.msg;

    if(package.code == 0){
        if(apiIndex == getDataStream){
            qDebug()<< "data_at: "<<package.time;
            qDebug()<< "data_name[0]: "<<package.valueName[0];
            qDebug()<< "data_value[0]: "<<package.valueFbd[0];
            qDebug()<< "equipment_name: "<<package.equipmentName;
            qDebug()<< "equipment_id: "<<package.equipmentId;
            qDebug()<< "request_id: "<<package.requestId;

            //存入数据到本地
            status = proudct.findEquipmentIndex(&index, package.equipmentId, package.equipmentName);
            if(status == SUCCESS){
                proudct.equipmentList[index].setEquipmentValue(package.valueName[0], package.valueFbd[0]);
            }else{
                proudct.errorCheck(status);
            }
        }
        if(apiIndex == getDeviceDetail){
            qDebug()<< "enable_status: " <<package.enable_status;
            qDebug()<< "last_time: "<<package.last_time;
            qDebug()<< "status: "<<package.status;

            status = proudct.findEquipmentIndex(&index, package.equipmentId, package.equipmentName);
            if(status == SUCCESS){
                proudct.equipmentList[index].setEquipmentValue(package.valueName[0], package.valueFbd[0]);
            }else{
                proudct.errorCheck(status);
            }
        }
    }
}
//qDebug()<<"here";
//JSON解析函数
void ONENET_UnPackage_JSON(equipment *package, QString rcivBuff){
    QJsonParseError err;
    QJsonDocument json_Recv = QJsonDocument::fromJson(rcivBuff.toUtf8(),&err);
//    测试整体JSON包内容
          QString temp1 = json_Recv.toJson(QJsonDocument::Compact);
          qDebug()<<temp1;
    if(!json_Recv.isNull()){
        QJsonObject object_All = json_Recv.object();
        if(object_All.contains("data")){
            QJsonObject object_Data = object_All.take("data").toObject();
            //测试“Data”对象中内容
            //               QJsonDocument tempDoc = QJsonDocument(object_Data);
            //               QString temp = tempDoc.toJson(QJsonDocument::Compact);
            //               qDebug()<<temp;
            if(object_Data.contains("enable_status")){
                package->enable_status = object_Data.value("enable_status").toBool();
            }
            if(object_Data.contains("last_time")){
                package->last_time = object_Data.value("last_time").toString();
            }
            if(object_Data.contains("devices")){
                QJsonArray array_Devices = object_Data.take("devices").toArray();
                QJsonObject object_Devices = array_Devices.at(0).toObject();
                //测试“object_Devices”对象中内容
                //                   QJsonDocument tempDoc2 = QJsonDocument(object_Devices);
                //                   QString temp2 = tempDoc2.toJson(QJsonDocument::Compact);
                //                   qDebug()<<temp2;
                if(object_Devices.contains("datastreams")){
                    QJsonArray array_Datastreams = object_Devices.take("datastreams").toArray();
                    QJsonObject object_Datastreams = array_Datastreams.at(0).toObject();
                    //测试“object_Datastreams”对象中内容
                    //                        QJsonDocument tempDoc3 = QJsonDocument(object_Datastreams);
                    //                        QString temp3 = tempDoc3.toJson(QJsonDocument::Compact);
                    //                        qDebug()<<temp3;
                    if(object_Datastreams.contains("at")) {
                        package->time = object_Datastreams.value("at").toString();
                    }
                    if(object_Datastreams.contains("id")) {
                        package->valueName[0] =object_Datastreams.value("id").toString();
                    }
                    if(object_Datastreams.contains("value")) {
                        package->valueFbd[0] = object_Datastreams.value("value").toDouble();
                    }
                }
                if(object_Devices.contains("title")){
                    package->equipmentName = object_Devices.value("title").toString();
                }
                if(object_Devices.contains("id")){
                    package->equipmentId = object_Devices.value("id").toString();
                }
                if(object_Devices.contains("status")){
                    package->status = object_Devices.value("status").toInt();
                }
            }
        }
        if(object_All.contains("msg")){
            package->msg = object_All.value("msg").toString();
        }
        if(object_All.contains("request_id")){
            package->requestId = object_All.value("request_id").toString();
        }
        if(object_All.contains("code")){
            package->code = object_All.value("code").toDouble();
        }
    }
}

