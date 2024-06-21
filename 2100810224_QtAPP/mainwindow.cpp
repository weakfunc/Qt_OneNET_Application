#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_manager = new QNetworkAccessManager(this);
    connect(m_manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(slot_webpageLoaded(QNetworkReply*)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slot_webpageLoaded(QNetworkReply *reply){
       qDebug()<<"已接收";
       QString qstrReply = reply->readAll();
       ui->textBrowser->setText(qstrReply);
}

void MainWindow::on_pushButton_clicked(){
    QNetworkRequest req;
    req.setUrl(QString("http://iot-api.heclouds.com/datapoint/current-datapoints?product_id=773E26dPR4&device_name=TEST_1"));
    req.setRawHeader("authorization","version=2018-10-31&res=products%2F773E26dPR4%2Fdevices%2FTEST_1&et=1837255523&method=md5&sign=L1DNKwgx4ns6yyIODi7bTA%3D%3D");
    m_manager->get(req);
    qDebug()<<"已发送";
}
