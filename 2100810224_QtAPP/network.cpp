#include "network.h"

//设置云平台API接口
QByteArray ONENET_API[API_NUM] = {"http://iot-api.heclouds.com/datapoint/current-datapoints?"};

//设置云平台HTTP协议固定字段
QByteArray ONENET_HEADERP[HEADER_NUM] = {"product_id=",
                                         "&device_name=",
                                         "authorization"};

network_ONENET onenet;

network::network() {

}

network_ONENET::network_ONENET(){
    int index;
    apiFunc = -1;
    for(index = 0; index < API_NUM; index++){
        api[index] = ONENET_API[index];
    }
    for(index = 0; index < HEADER_NUM; index++){
        header[index] = ONENET_HEADERP[index];
    }
    unPackage[fromJson] = ONENET_UnPackage_JSON;
}

 //QString("http://iot-api.heclouds.com/datapoint/current-datapoints?product_id=773E26dPR4&device_name=TEST_1")
QString network_ONENET::getURL(ONENET_Function apiIndex, QByteArray id, QString name){
    return QString(api[apiIndex] + header[product_id] + id + header[device_name] + name.toUtf8());
}

void network_ONENET::sendData(ONENET_Function apiIndex){
    apiFunc = apiIndex;

}

void network_ONENET::receiveData(ONENET_Function apiIndex, QString qstrReply){
    packageParam package;
    QString status;
    int index;
    //解包
    unPackage[fromJson](&package, qstrReply);
    qDebug()<<"已接收";

    if(apiIndex == getDataStream){
        qDebug()<< "data_at: "<<package.time;
        qDebug()<< "data_name: "<<package.valueName;
        qDebug()<< "data_value: "<<package.valueFbd;
        qDebug()<< "equipment_name: "<<package.equipmentName;
        qDebug()<< "equipment_id: "<<package.equipmentId;
        qDebug()<< "msg: "<<package.msg;
        qDebug()<< "request_id: "<<package.requestId;

        //存入数据到本地
        status = productOneConfig.findEquipmentIndex(&index, package.equipmentId, package.equipmentName);
        if(status == SUCCESS){
            productOneConfig.setEquipmentValue(index, package.valueName, package.valueFbd);
        }else{
            productOneConfig.errorCheck(status);
        }
    }
}

//JSON解析函数
void ONENET_UnPackage_JSON(packageParam *package, QString rcivBuff){
    QJsonParseError err;
    QJsonDocument json_Recv = QJsonDocument::fromJson(rcivBuff.toUtf8(),&err);
    //测试整体JSON包内容
    //       QString temp1 = json_Recv.toJson(QJsonDocument::Compact);
    //       qDebug()<<temp1;
    if(!json_Recv.isNull()){
        QJsonObject object_All = json_Recv.object();
        if(object_All.contains("data")){
            QJsonObject object_Data = object_All.take("data").toObject();
            //测试“Data”对象中内容
            //               QJsonDocument tempDoc = QJsonDocument(object_Data);
            //               QString temp = tempDoc.toJson(QJsonDocument::Compact);
            //               qDebug()<<temp;
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
                        package->valueName =object_Datastreams.value("id").toString();
                    }
                    if(object_Datastreams.contains("value")) {
                        package->valueFbd = object_Datastreams.value("value").toDouble();
                    }
                }
                if(object_Devices.contains("title")){
                    package->equipmentName = object_Devices.value("title").toString();
                }
                if(object_Devices.contains("id")){
                    package->equipmentId = object_Devices.value("id").toString();
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
            //            double code = object_All.value("code").toDouble();
            //            qDebug()<< "code: " <<code;
        }
    }
}

