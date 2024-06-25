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
  //  connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::on_pushButton_clicked);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &QMainWindow::close);
    connect(ui->pushButton_3, &QPushButton::clicked, this, &MainWindow::test);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::test(){
    productOneConfig.showEquipments();
}
void MainWindow::slot_receive_dataStream(QNetworkReply *reply){
    QString qstrReply = reply->readAll();
    ui->textBrowser->setText(qstrReply);

    onenet.receiveData(getDataStream, qstrReply);
}


void MainWindow::on_pushButton_clicked(){
    QNetworkRequest req;
    QString url;

    url = onenet.getURL(getDataStream, productOneConfig.product_id, productOneConfig.equipmentList[0].equipmentName);
    req.setUrl(url);
    req.setRawHeader(onenet.header[authorization],productOneConfig.token);
    m_manager->get(req);
    qDebug()<<"已发送";
}
