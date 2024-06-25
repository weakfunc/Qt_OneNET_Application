#ifndef DEFAULTCONFIG_H
#define DEFAULTCONFIG_H
#include <QString>
#include <QDebug>

#define MAX_EQUIPMENT_NUM 5        //最大本地设备数量
#define MAX_VALUE_NUM 5             //最大设备参数数量

class equipment{
public:
    QString equipmentId;
    QString equipmentName;
    QString valueName;
    double valueFbd;
    double valueRef;
    int valueNum;
    int index;      //设备本地编号

    equipment(QString id, QString name,int valNum, QString valName);
    equipment();
};

class _defaultConfig
{
public:
    _defaultConfig();
    equipment equipmentList[MAX_EQUIPMENT_NUM];

    void showEquipments();
    void addEquipment();
    void setEquipmentValue(int index, QString valName, double val);
    QString findEquipmentIndex(int* recv, QString id=nullptr, QString name=nullptr);
};

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

extern _defaultConfig defaultConfig;

#endif // DEFAULTCONFIG_H
