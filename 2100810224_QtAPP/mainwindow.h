#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QMainWindow>
#include <QMenuBar>
#include <QToolBar>
#include <QDebug>
#include <QPushButton>
#include <QStatusBar>
#include <QLabel>
#include <QDockWidget>
#include <QTextEdit>
#include "defaultconfig.h"
#include "network.h"
#include <QChartView>
#include <QtCharts>
#include <QChart>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void createChart();
private:
    Ui::MainWindow *ui;
    QNetworkAccessManager *m_manager;

private:
    QChart *m_Chart;//创建画布
    QDateTimeAxis *m_axisX;//横坐标（时间）
    QValueAxis *m_axisY;//纵坐标（温度）
    QSplineSeries *m_chLoadSerise;//温度曲线

private slots:
    void slot_receive_dataStream(QNetworkReply *reply);
    void pushButton_0();
    void pushButton_4();
    void test();
};
#endif // MAINWINDOW_H
