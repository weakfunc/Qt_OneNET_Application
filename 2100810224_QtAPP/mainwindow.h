#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include "defaultconfig.h"
#include "network.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    Ui::MainWindow *ui;
    QNetworkAccessManager *m_manager;
private slots:
    void slot_receive_dataStream(QNetworkReply *reply);
    void on_pushButton_clicked();
    void test();
};
#endif // MAINWINDOW_H
