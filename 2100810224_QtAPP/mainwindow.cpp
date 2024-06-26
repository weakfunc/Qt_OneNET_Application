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

    //菜单栏创建,菜单栏最多有一个
    QMenuBar *bar = menuBar();
    //将菜单栏放入窗口中,空菜单栏不显示
    setMenuBar(bar);
    //创建菜单
    QMenu *fileMenu = bar->addMenu("文件");
    QMenu *editMenu = bar->addMenu("编辑");
    //创建菜单项
    QAction *action_1 = fileMenu->addAction("新建");
    //添加分隔线
    fileMenu->addSeparator();
    QAction *action_2 = fileMenu->addAction("打开");

    //工具栏创建,工具栏可以有多个
    QToolBar *toolBar = new QToolBar(this);
    //将工具栏放入窗口中,调用addToolBar的重载函数,把工具栏默认停靠区域设置为左侧
    addToolBar(Qt::LeftToolBarArea, toolBar);
    //设置只允许左右停靠
    toolBar->setAllowedAreas(Qt::LeftToolBarArea | Qt::RightToolBarArea);
    //设置不允许浮动
    //更多设置参见toolBar QtAssaint;
    toolBar->setFloatable(false);
    //工具栏中设置内容
    toolBar->addAction(action_1);
    toolBar->addSeparator();
    toolBar->addAction(action_2);
    //工具栏中新建控件
    QPushButton *btn = new QPushButton("aa", this);
    toolBar->addWidget(btn);

    connect(m_manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(slot_receive_dataStream(QNetworkReply*)));
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::pushButton_0);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &QMainWindow::close);
    connect(ui->pushButton_3, &QPushButton::clicked, this, &MainWindow::test);
    connect(ui->pushButton_4, &QPushButton::clicked, this, &MainWindow::pushButton_4);
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

    onenet.receiveData(onenet.apiFuc, qstrReply);
}
void MainWindow::pushButton_0(){
    onenet.sendGetDataStream(m_manager, productOneConfig.product_id, productOneConfig.equipmentList[0].equipmentName);
}
void MainWindow::pushButton_4(){
    onenet.sendGetDeviceDetail(m_manager, productOneConfig.product_id, productOneConfig.equipmentList[0].equipmentName);
}
