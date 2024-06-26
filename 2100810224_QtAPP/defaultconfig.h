#ifndef DEFAULTCONFIG_H
#define DEFAULTCONFIG_H
#include <QString>
#include <QDebug>

#define SUCCESS "1"
#define MAX_EQUIPMENT_NUM 5        //最大本地设备数量
#define MAX_VALUE_NUM 5             //最大设备参数数量
#define PRODUCT_ONE_TOKEN "version=2018-10-31&res=products%2F773E26dPR4%2Fdevices%2FTEST_1&et=1837255523&method=md5&sign=L1DNKwgx4ns6yyIODi7bTA%3D%3D"
#define PRODUCT_ONE_ID "773E26dPR4"

class packageParam{
public:
    QString time;
    QString requestId;
    QString msg;
    double code;

    void checkError(double code);
    void showMsg(QString msg);
};

class equipment:public packageParam{
public:
    QString equipmentId;
    QString equipmentName;
    QString valueName[MAX_VALUE_NUM];
    QString last_time;  //最后一次在线时间
    double valueFbd[MAX_VALUE_NUM];
    double valueRef[MAX_VALUE_NUM];
    int valueNum;
    int index;      //设备本地编号 
    bool enable_status; //设备激活状态
    int status; //在线状态

    equipment(QString id, QString name,int valNum, QString* valName);
    equipment();

    void setEquipmentValue(QString valname, double val);
    void setEquipmentStatus(QString time, bool st);
};

class defaultConfig
{
public:
    equipment equipmentList[MAX_EQUIPMENT_NUM];
    QByteArray token;
    QByteArray product_id;

    defaultConfig();
    void showEquipments();
    void errorCheck(QString err);
    QString addEquipment();
    QString findEquipmentIndex(int* recv, QString id=nullptr, QString name=nullptr);
};
extern defaultConfig productOneConfig;

#endif // DEFAULTCONFIG_H
