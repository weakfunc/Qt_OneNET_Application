#ifndef DEFAULTCONFIG_H
#define DEFAULTCONFIG_H
#include <QString>
#include <QDebug>

#define SUCCESS "1"
#define MAX_EQUIPMENT_NUM 5        //最大本地设备数量
#define MAX_VALUE_NUM 5             //最大设备参数数量


class equipment{
public:
    QString equipmentId;
    QString equipmentName;
    QString valueName[MAX_VALUE_NUM];
    double valueFbd[MAX_VALUE_NUM];
    double valueRef[MAX_VALUE_NUM];
    int valueNum;
    int index;      //设备本地编号

    equipment(QString id, QString name,int valNum, QString* valName);
    equipment();
};

class defaultConfig
{
public:
    equipment equipmentList[MAX_EQUIPMENT_NUM];
    QByteArray token;
    QByteArray product_id;

    defaultConfig();
    void showEquipments();
    void addEquipment();
    void setEquipmentValue(int index, QString valName, double val);
    void errorCheck(QString err);
    QString findEquipmentIndex(int* recv, QString id=nullptr, QString name=nullptr);
};
extern defaultConfig productOneConfig;

#endif // DEFAULTCONFIG_H
