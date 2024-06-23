#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE



class MainWindow : public QMainWindow
{
    Q_OBJECT        //宏，允许类中使用信号和槽的机制

public:
    MainWindow(QWidget *parent = nullptr);      //构造函数，默认值为nullptr
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager *m_manager;

private slots:
    void slot_webpageLoaded(QNetworkReply *reply);
    void on_pushButton_clicked();
};
#endif // MAINWINDOW_H
