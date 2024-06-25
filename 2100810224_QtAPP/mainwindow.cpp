#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QPushButton"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(800,600);
    setWindowTitle("2100810024权恒毅");

    m_manager = new QNetworkAccessManager(this);

    connect(m_manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(slot_receive_dataStream(QNetworkReply*)));
    connect(ui->pushButton_2, &QPushButton::clicked, this, &QMainWindow::close);
    connect(ui->pushButton_3, &QPushButton::clicked, this, &MainWindow::test);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::test(){
    int index;
    defaultConfig.showEquipments();
    qDebug() <<  defaultConfig.findEquipmentIndex(&index,"","lal");
}
void MainWindow::slot_receive_dataStream(QNetworkReply *reply){
    qDebug()<<"已接收";
    packageParam package1;
    QString qstrReply = reply->readAll();
    ui->textBrowser->setText(qstrReply);

    recerivePackage(qstrReply, &package1);
    qDebug()<< "data_at: "<<package1.time;
    qDebug()<< "data_name: "<<package1.valueName;
    qDebug()<< "data_value: "<<package1.valueFbd;
    qDebug()<< "equipment_name: "<<package1.equipmentName;
    qDebug()<< "equipment_id: "<<package1.equipmentId;
    qDebug()<< "msg: "<<package1.msg;
    qDebug()<< "request_id: "<<package1.requestId;

}
void MainWindow::recerivePackage(QString rcivPage, packageParam *package){
    QJsonParseError err;
    QJsonDocument json_Recv = QJsonDocument::fromJson(rcivPage.toUtf8(),&err);
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


void MainWindow::on_pushButton_clicked(){
    QNetworkRequest req;
    req.setUrl(QString("http://iot-api.heclouds.com/datapoint/current-datapoints?product_id=773E26dPR4&device_name=TEST_1"));
    req.setRawHeader("authorization","version=2018-10-31&res=products%2F773E26dPR4%2Fdevices%2FTEST_1&et=1837255523&method=md5&sign=L1DNKwgx4ns6yyIODi7bTA%3D%3D");
    m_manager->get(req);
    qDebug()<<"已发送";
}
