#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QPushButton"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
 //   setFixedSize(800,600);
    setWindowTitle("2100810024权恒毅");

    m_manager = new QNetworkAccessManager(this);

    // //菜单栏创建,菜单栏最多有一个
    // QMenuBar *bar = menuBar();
    // //将菜单栏放入窗口中,空菜单栏不显示
    // setMenuBar(bar);
    // //创建菜单
    // QMenu *fileMenu = bar->addMenu("文件");
    // QMenu *editMenu = bar->addMenu("编辑");
    // //创建菜单项
    // QAction *action_1 = fileMenu->addAction("新建");
    // //添加分隔线
    // fileMenu->addSeparator();
    // QAction *action_2 = fileMenu->addAction("打开");

    // //工具栏创建,工具栏可以有多个
    // QToolBar *toolBar = new QToolBar(this);
    // //将工具栏放入窗口中,调用addToolBar的重载函数,把工具栏默认停靠区域设置为左侧
    // addToolBar(Qt::LeftToolBarArea, toolBar);
    // //设置只允许左右停靠
    // toolBar->setAllowedAreas(Qt::LeftToolBarArea | Qt::RightToolBarArea);
    // //设置不允许浮动
    // //更多设置参见toolBar QtAssaint;
    // toolBar->setFloatable(false);
    // //工具栏中设置内容
    // toolBar->addAction(action_1);
    // toolBar->addSeparator();
    // toolBar->addAction(action_2);
    // //工具栏中新建控件
    // QPushButton *btn = new QPushButton("aa", this);
    // toolBar->addWidget(btn);

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

    createChart();
   // onenet.sendGetDeviceDetail(m_manager, productOneConfig.product_id, productOneConfig.equipmentList[0].equipmentName);
}

void MainWindow::createChart(){
    //创建对象
    m_Chart = new QChart;
    m_chLoadSerise= new QSplineSeries;
    m_chLoadSerise->clear();
    m_axisX = new QDateTimeAxis;
    m_axisY = new QValueAxis;
    //坐标、波形属性设置
    QDateTime timeStart=QDateTime::currentDateTime();
    QDateTime timeEnd=timeStart.addSecs(1800);
    m_Chart->setTitle("温度变化曲线");//坐标系名称
    m_axisX->setTitleText("时间");//横坐标名称
    m_axisX->setTitleBrush(Qt::white);//横坐标名称字体颜色
    m_axisX->setFormat("hh:mm:ss");//横坐标时间格式
    m_axisX->setRange(timeStart, timeEnd);//设置横坐标时间范围
    m_axisX->setTickCount(10);//设置横坐标格数（间隔）
    m_axisY->setTitleText("温度(℃)");//纵坐标名称
    m_axisY->setTitleBrush(Qt::white);//纵坐标名称字体颜色
    m_axisY->setLabelFormat("%.1f");//纵坐标温度小数位数
    m_axisY->setRange(0,25);//纵坐标范围
    m_axisY->setTickCount(10);//设置纵坐标格数（间隔）
    m_chLoadSerise->setName("温度值");//曲线名称
    m_Chart->addSeries(m_chLoadSerise);//曲线加入到坐标
    m_Chart->setAxisX(m_axisX, m_chLoadSerise);//横坐标加入曲线
    m_Chart->setAxisY(m_axisY, m_chLoadSerise);//纵坐标加入曲线
    //m_Chart->setTheme(QChart::ChartThemeDark);//设置坐标背景颜色
    m_Chart->setBackgroundVisible(false);//设置坐标系背景透明透明
    m_Chart->legend()->setVisible(true);//曲线图例显示
    m_Chart->legend()->setAlignment(Qt::AlignBottom);//图例位置
    m_Chart->legend()->setLabelColor(Qt::white);//图例颜色
    m_Chart->setTitleBrush(Qt::white);//坐标系名称颜色
    m_Chart->axisX()->setLabelsColor(Qt::white);//横坐标刻度颜色
    m_Chart->axisY()->setLabelsColor(Qt::white);//纵坐标刻度颜色
    ui->graphicsView->setChart(m_Chart);//画布加入到widget控件中（注：在ui界面需将widget提升控件为QChartView）
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);//防止图形走样
    //曲线中加入坐标值
    m_chLoadSerise->append(timeStart.toMSecsSinceEpoch(),5);
    m_chLoadSerise->append(timeStart.addSecs(200).toMSecsSinceEpoch(),5.5);
    m_chLoadSerise->append(timeStart.addSecs(500).toMSecsSinceEpoch(),5.6);
    m_chLoadSerise->append(timeStart.addSecs(800).toMSecsSinceEpoch(),5.8);
    m_chLoadSerise->append(timeStart.addSecs(1200).toMSecsSinceEpoch(),6);
    m_chLoadSerise->append(timeStart.addSecs(1500).toMSecsSinceEpoch(),7);
    m_chLoadSerise->append(timeStart.addSecs(1700).toMSecsSinceEpoch(),12);
}
