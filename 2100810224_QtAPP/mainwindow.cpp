#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QPushButton"
//类名 首字母大写，单词间首字母大写
//函数名 变量名 首字母小写，单词间首字母大写

//快捷键
//注释 crtl+/
//运行 crtl+r
//编译 ctrl+b
//帮助文档 F1 D:\App_master\QT\5.12.12\mingw73_32\bin\assistant.exe
//同名之间的.h和.cpp切换 F4

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//    resize(800,600);       //设置窗口大小
    setFixedSize(800,600);   //设置固定窗口大小
    setWindowTitle("2100810024权恒毅");    //设置窗口标题

    m_manager = new QNetworkAccessManager(this);

    //param1:信号的返送者 param2:发送的信号（函数指针）param3:信号的接收者 parma4:槽函数
    connect(m_manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(slot_webpageLoaded(QNetworkReply*)));
    connect(ui->pushButton_2, &QPushButton::clicked, this, &QMainWindow::close);
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
