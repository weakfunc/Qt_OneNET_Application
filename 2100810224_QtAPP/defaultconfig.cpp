#include "defaultconfig.h"
//设置本地设备ID
QByteArray EQUIPMENT_ID[MAX_EQUIPMENT_NUM] = {"2174127353",
                                              "2"};

//设置本地设备名称
QByteArray EQUIPMENT_NAME[MAX_EQUIPMENT_NUM] = {"TEST_1",
                                                "2"};

//设置本地设备参数数量
int EQUIPMENT_VALUE_NUM[MAX_EQUIPMENT_NUM] = {2,2};

//设置本地设备参数名称
QByteArray EQUIPMENT_VALUE_NAME[MAX_EQUIPMENT_NUM][MAX_VALUE_NUM] = {{"parameter_1","name2"},
                                                                     {"name3","name4"}};

defaultConfig productOneConfig;

defaultConfig::defaultConfig(){
    //初始化本地设备
    int index1, index2;
    for(index1 = 0; index1 < MAX_EQUIPMENT_NUM; index1++){
        equipmentList[index1].index = index1;
        equipmentList[index1].equipmentId = EQUIPMENT_ID[index1];
        equipmentList[index1].equipmentName = EQUIPMENT_NAME[index1];
        equipmentList[index1].valueNum = EQUIPMENT_VALUE_NUM[index1];
        for(index2 = 0; index2 < MAX_VALUE_NUM; index2++){
            equipmentList[index1].valueName[index2] = EQUIPMENT_VALUE_NAME[index1][index2];
        }
    }
    token = PRODUCT_ONE_TOKEN;
    product_id  = PRODUCT_ONE_ID;
}

equipment::equipment(){

}

void defaultConfig::showEquipments(){
    int index1, index2;
    qDebug() << "本地设备列表";
    for(index1 = 0; index1 < MAX_EQUIPMENT_NUM; index1++){
        qDebug() << "编号" << equipmentList[index1].index
                 << "\t设备名称：" << equipmentList[index1].equipmentName
                 << "\t设备ID：" << equipmentList[index1].equipmentId
                 << "\t参数个数" << equipmentList[index1].valueNum;
        for(index2 = 0; index2 < equipmentList[index1].valueNum; index2++){
            qDebug() << equipmentList[index1].valueName[index2] << " : " << equipmentList[index1].valueFbd[index2];
        }
    }
}

QString defaultConfig::findEquipmentIndex(int* recv, QString id, QString name){
    QString back;
    int index;
    if(id != nullptr){
        for(index = 0; index < MAX_EQUIPMENT_NUM; index++){
            if(equipmentList[index].equipmentId == id)
            *recv = index;
            back = SUCCESS;
        }
    }else if(name != nullptr){
        for(index = 0; index < MAX_EQUIPMENT_NUM; index++){
            if(equipmentList[index].equipmentName == name)
            *recv = index;
            back = SUCCESS;
        }
    }else back = "E001";
    return back;
}

void defaultConfig::errorCheck(QString err){
    if(err == "E001"){
        qDebug() << "找不到本地设备";
    }
}

void equipment::setEquipmentValue(QString valname, double val){
    int index;
    for(index = 0; index < valueNum; index++){
        if(valueName[index] == valname){
            valueFbd[index] = val;
        }
    }
}
