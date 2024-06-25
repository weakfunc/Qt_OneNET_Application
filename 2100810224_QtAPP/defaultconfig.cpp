#include "defaultconfig.h"

//设置本地设备ID
QString EQUIPMENT_ID[MAX_EQUIPMENT_NUM] = {"2174127353",
                                           "2"};

//设置本地设备名称
QString EQUIPMENT_NAME[MAX_EQUIPMENT_NUM] = {"TEST_1",
                                             "2"};

//设置本地设备变量数量
int EQUIPMENT_VALUE_NUM[MAX_EQUIPMENT_NUM] = {1,3};

//设置本地设备变量名称
QString EQUIPMENT_VALUE_NAME[MAX_EQUIPMENT_NUM] = {"1","2"};


_defaultConfig defaultConfig;

_defaultConfig::_defaultConfig(){
//添加本地设备
    int index;
    for(index = 0; index < MAX_EQUIPMENT_NUM; index++){
        equipmentList[index].index = index;
        equipmentList[index].equipmentId = EQUIPMENT_ID[index];
        equipmentList[index].equipmentName = EQUIPMENT_NAME[index];
    }
    for(index =0; index < MAX_VALUE_NUM; index++){
        equipmentList[index].valueNum = EQUIPMENT_VALUE_NUM[index];
        equipmentList[index].valueName = EQUIPMENT_VALUE_NAME[index];
    }
}

equipment::equipment(QString id, QString name,int valNum, QString valName){
    equipmentId = id;
    equipmentName = name;
    valueName = valName;
    valueNum = valNum;
}
equipment::equipment(){


}

void _defaultConfig::showEquipments(){
    int index;
    qDebug() << "本地设备列表";
    for(index = 0; index < MAX_EQUIPMENT_NUM; index++){
        qDebug() << "编号" << equipmentList[index].index
                 << "\t设备名称：" << equipmentList[index].equipmentName
                 << "\t设备ID：" << equipmentList[index].equipmentId
                 << "\t参数个数" << equipmentList[index].valueNum
                 << "\t参数名" << equipmentList[index].valueName;
    }
}

QString _defaultConfig::findEquipmentIndex(int* recv, QString id, QString name){
    QString back;
    int index;
    if(id != nullptr){
        for(index = 0; index < MAX_EQUIPMENT_NUM; index++){
            if(equipmentList[index].equipmentId == id)
            *recv = index;
            back = "1";
        }
    }else if(name != nullptr){
        for(index = 0; index < MAX_EQUIPMENT_NUM; index++){
            if(equipmentList[index].equipmentName == name)
            *recv = index;
            back = "1";
        }
    }else back = "E001";
    return back;
}

void _defaultConfig::setEquipmentValue(int index, QString valName, double val){

}
