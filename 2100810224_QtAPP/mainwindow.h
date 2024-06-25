#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include "defaultconfig.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void recerivePackage(QString rcivPage, packageParam *package);
private:
    Ui::MainWindow *ui;
    QNetworkAccessManager *m_manager;
private slots:
    void slot_receive_dataStream(QNetworkReply *reply);
    void on_pushButton_clicked();
    void test();
};
#endif // MAINWINDOW_H
